`timescale 1ns/1ps

module eth_rx (
    input  logic        clk, // system clock
    input  logic        rst_n, // active-low reset
    input  logic [7:0]  rx_byte, // incoming serial byte from PHY
    input  logic        rx_valid, // indicates rx_byte is valid this cycle
    output logic [7:0]  payload_byte, // stripped payload byte to downstream
    output logic        payload_valid,
    input  logic        payload_ready,
    output logic        crc_ok, // New
    output logic        crc_valid, // New

    // --- debug taps for CRC investigation ---
    output logic [31:0] dbg_crc_calc,
    output logic [31:0] dbg_crc_recv,
    output logic [15:0] dbg_payload_len,
    output logic [15:0] dbg_total_payload,
    output logic [15:0] dbg_payload_cnt_last
);

    typedef enum logic [2:0] {
        IDLE,        // waiting for first 0x55
        PREAMBLE,    // counting 0x55 bytes
        SFD,        // looking for D5 start-frame delimiter
        LOAD_HEADER, // shifting in MAC/dest/type
        LOAD_PAYLD,  // clocking out payload bytes
        CRC_CHECK   // consuming & checking 4-byte FCS
    } state_t;
    state_t state;

    localparam logic [47:0] OUR_MAC       = 48'h00_11_22_33_44_55; // filter unicast
    localparam logic [47:0] MAC_BROADCAST = 48'hFF_FF_FF_FF_FF_FF; // allow broadcast

    //—— CRC helper (LSB-first / reflected IEEE-802.3) ————————————————————
    function automatic logic [31:0] crc32_lsbf(
        input logic [31:0] crc_in,
        input logic [7:0]  data_byte
    );
        logic [31:0] c = crc_in ^ {24'h0, data_byte};
        for (int i = 0; i < 8; i++) begin
            if (c[0]) c = (c >> 1) ^ 32'hEDB88320;
            else       c =  c >> 1;
        end
        return c;
    endfunction

    // internal registers
    logic [2:0]   pre_cnt;         // how many 0x55s seen
    logic [3:0]   crc_cnt;         // count of FCS bytes shifted in
    logic [15:0]  hdr_cnt;         // count within header (MAC+type)
    logic [15:0]  payload_cnt;     // how many payload bytes seen
    logic [15:0]  payload_len;     // extracted ITCH message length
    logic [47:0]  dest_mac_shift;  // shifting in dest MAC for compare
    logic         mac_match;       // did dest MAC == us or broadcast?
    logic [31:0]  crc_reg;         // running CRC accumulator
    logic [31:0]  crc_recv_shift;  // shift-register for incoming FCS
    logic         this_cycle_match; // for debug, did we match this cycle?
    logic [31:0]  next_crc; // for debug, next CRC value
    logic [31:0]  fcs_word; 
    logic [15:0]  total_payload;  // length + 2 length bytes
    logic crc_started;


    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            // Asynchronous reset of all state and counters
            state           <= IDLE;
            pre_cnt         <= 0;
            hdr_cnt         <= 0;
            payload_cnt     <= 0;
            payload_len     <= 0;
            mac_match       <= 0;
            payload_valid   <= 0;
            crc_cnt         <= 0;
            dest_mac_shift  <= 0;
            crc_reg         <= 32'hFFFF_FFFF;
            crc_recv_shift  <= 0;
            crc_ok          <= 0;
            crc_valid       <= 0;
            crc_started     <= 0;
            fcs_word            <= 32'h0;
            total_payload       <= 16'h0;
            dbg_crc_calc        <= 32'h0;
            dbg_crc_recv        <= 32'h0;
            dbg_payload_len     <= 16'h0;
            dbg_total_payload   <= 16'h0;
            dbg_payload_cnt_last<= 16'h0;
        end else begin
            // default: clear payload_valid each cycle,
            // we'll re-assert it only when we really have a byte to send
            payload_valid <= 0;
            crc_valid <= 0;  

            case (state)
                IDLE: begin
                    // Wait for first preamble byte (0x55)
                    if (rx_valid && rx_byte == 8'h55) begin
                        state   <= PREAMBLE;
                        pre_cnt <= 1;
                    end
                end

                PREAMBLE: begin
                    if (rx_valid) begin
                        if (rx_byte == 8'h55) begin
                            // count consecutive 0x55
                            pre_cnt <= pre_cnt + 1;
                            if (pre_cnt == 6) begin
                                // after 7th 0x55, transition to SFD
                                state <= SFD;
                            end
                        end else begin
                            // non-55 breaks preamble
                            state   <= IDLE;
                            pre_cnt <= 0;
                        end
                    end
                end

                SFD: begin
                    if (rx_valid) begin
                        if (rx_byte == 8'hD5) begin
                            // SFD detected → seed CRC (don’t include D5 in the CRC)

                            crc_reg         <= 32'hFFFFFFFF;    // new seed, no folding of 0xD5
                            crc_started     <= 1'b1; // indicate CRC started
                            crc_recv_shift  <= 0;
                            crc_cnt         <= 0;

                            // prepare to read Ethernet header
                            state           <= LOAD_HEADER;
                            hdr_cnt         <= 0;
                            dest_mac_shift  <= 0;
                            mac_match       <= 0;
                        end else begin
                            // bad SFD → restart
                            state <= IDLE;
                        end
                    end
                end

                LOAD_HEADER: begin
                    if (rx_valid) begin
                        // fold this header byte into CRC
                        next_crc = crc32_lsbf(crc_reg, rx_byte);   
                        crc_reg <= next_crc; // update CRC with this byte
     

                        // for first 6 bytes, build the destination MAC
                        if (hdr_cnt < 6) begin
                            logic [47:0] full_dest = {dest_mac_shift[39:0], rx_byte};
                            dest_mac_shift <= full_dest;

                            if (hdr_cnt == 5) begin
                                // once there is 6 bytes, compare to OUR_MAC or broadcast
                                this_cycle_match = (full_dest == OUR_MAC) || (full_dest == MAC_BROADCAST);
                                mac_match <= this_cycle_match;
                            end
                        end

                        hdr_cnt <= hdr_cnt + 1;
                        // after MAC(6)+SRC(6)+TYPE(2) = 14 total header bytes (count 0–13)
                        if (hdr_cnt == 13) begin
                            state       <= LOAD_PAYLD;
                            payload_cnt <= 0;
                        end
                    end
                end

                LOAD_PAYLD: begin
                    if (rx_valid) begin
                        // fold each payload byte into CRC
                        next_crc = crc32_lsbf(crc_reg, rx_byte);
                        crc_reg <= next_crc;

                        // first two payload bytes = ITCH length
                        if      (payload_cnt == 0) begin
                            payload_len[15:8] <= rx_byte;
                        end else if (payload_cnt == 1) begin
                            payload_len[7:0]  <= rx_byte;
                            // total payload bytes inside Ethernet = len (type+body) + 2 (length bytes)
                            total_payload     <= {payload_len[15:8], rx_byte} + 16'd2;
                            dbg_payload_len   <= {payload_len[15:8], rx_byte};
                            dbg_total_payload <= {payload_len[15:8], rx_byte} + 16'd2;
                        end

                        // if we’re supposed to forward payload, do so
                        if (mac_match && payload_ready) begin
                            payload_byte  <= rx_byte;
                            payload_valid <= 1;
                        end

                        // if this was the *last* payload byte, go CRC_CHECK next cycle
                        if (payload_cnt + 16'd1 == total_payload) begin
                            crc_cnt        <= 0;
                            crc_recv_shift <= 0;
                            dbg_payload_cnt_last<= payload_cnt + 16'd1; // bytes actually folded
                            state          <= CRC_CHECK;
                        end

                        payload_cnt <= payload_cnt + 1;
                    end
                end


                CRC_CHECK: begin
                    if (rx_valid) begin
                        unique case (crc_cnt)
                        0: begin crc_recv_shift[ 7: 0] <= rx_byte; crc_cnt <= 1; end
                        1: begin crc_recv_shift[15: 8] <= rx_byte; crc_cnt <= 2; end
                        2: begin crc_recv_shift[23:16] <= rx_byte; crc_cnt <= 3; end
                        3: begin
                            
                            fcs_word = {rx_byte, crc_recv_shift[23:0]};  // [31:24]=last byte seen
                            dbg_crc_calc    <= (crc_reg ^ 32'hFFFF_FFFF);
                            dbg_crc_recv    <= fcs_word;
                            crc_ok    <= ((crc_reg ^ 32'hFFFF_FFFF) == fcs_word);
                            crc_valid <= 1'b1;

                            crc_started <= 1'b0; // CRC finished
                            state     <= IDLE;
                            crc_cnt   <= 0;
                            end
                        endcase
                    end
                end
            
                default: begin
                    state <= IDLE;
                end
            endcase
        end
    end

endmodule
`timescale 1ns/1ps

// Module: eth_rx
//
// Purpose:
//   Receives a raw Ethernet byte stream (1 byte per cycle) containing a full
//   ITCH message frame (including preamble, SFD, Ethernet header, ITCH payload,
//   and 4-byte CRC/FCS). Detects frame start, validates destination MAC, streams
//   payload bytes downstream, and verifies the frame CRC.
//
// Function:
//   • Detect preamble (7 × 0x55) followed by SFD (0xD5) to align to frame start.
//   • Fold all bytes from DA through the end of the payload into an IEEE 802.3
//     CRC-32 (reflected polynomial 0xEDB88320, init 0xFFFFFFFF, xorout 0xFFFFFFFF).
//   • Filter frames by Destination MAC (match OUR_MAC or broadcast).
//   • Output payload bytes only if MAC matches and downstream is ready
//     (lossless backpressure).
//   • Parse the first two payload bytes as ITCH length (big-endian) to determine
//     when payload ends and CRC bytes begin.
//   • Receive 4-byte FCS (LSB-first on the wire) and compare to computed CRC.
//   • Pulse crc_valid when CRC comparison is complete, with crc_ok indicating match.
//
// CRC Notes:
//   - The Start Frame Delimiter (0xD5) is not included in the CRC.
//   - Folding is LSB-first; each incoming byte is XORed into the low 8 bits of
//     the running CRC and shifted right.
//
// FSM States:
//   1. IDLE        : Wait for preamble start (0x55).
//   2. PREAMBLE    : Count 7 × 0x55.
//   3. SFD         : Expect 0xD5; seed CRC.
//   4. LOAD_HEADER : Fold 14-byte Ethernet header into CRC; capture DA for MAC match.
//   5. LOAD_PAYLD  : Fold payload bytes into CRC, stream out, track ITCH length.
//   6. CRC_CHECK   : Receive 4-byte FCS and compare to computed CRC.
//
// Output Behaviour:
//   - payload_valid pulses high for each payload byte sent downstream.
//   - crc_valid pulses high for exactly 1 cycle at CRC completion.

module eth_rx (

    // Clocking / reset
    input  logic        clk,          // system clock
    input  logic        rst_n,        // active-low reset (async in, sync usage)

    // Byte stream from PHY/MAC shim
    input  logic [7:0]  rx_byte,      // incoming serial byte (one per cycle)
    input  logic        rx_valid,     // qualifies rx_byte for this cycle

    // Streamed ITCH payload out
    output logic [7:0]  payload_byte, // payload byte (post-header)
    output logic        payload_valid, // high when payload_byte is valid
    input  logic        payload_ready, // downstream can accept this byte

    // CRC reporting
    output logic        crc_ok,       // 1-cycle pulse: CRC matched
    output logic        crc_valid,    // 1-cycle pulse: CRC result is valid

    // Debug / instrumentation taps (helpful in sim)
    output logic [31:0] dbg_crc_calc,       // computed CRC (reflected, xorout) at end
    output logic [31:0] dbg_crc_recv,       // received FCS as 32-bit word (LSB-first)
    output logic [15:0] dbg_payload_len,    // ITCH message length (extracted)
    output logic [15:0] dbg_total_payload,  // len + 2 bytes of length field
    output logic [15:0] dbg_payload_cnt_last// bytes folded into CRC for this frame
);
    // State machine for receiving Ethernet frames

    typedef enum logic [2:0] {
        IDLE,
        PREAMBLE,
        SFD,
        LOAD_HEADER,
        LOAD_PAYLD,
        CRC_CHECK
    } state_t;
    state_t state;

    // Destination MAC filter
    localparam logic [47:0] OUR_MAC       = 48'h00_11_22_33_44_55; // filter unicast
    localparam logic [47:0] MAC_BROADCAST = 48'hFF_FF_FF_FF_FF_FF; // allow broadcast

    // CRC helper (IEEE 802.3, reflected)
    // LSB-first folding with polynomial 0xEDB88320.
    // c[0] is the current LSB; shift right and conditionally XOR polynomial.
    function automatic logic [31:0] crc32_lsbf(
        input logic [31:0] crc_in,
        input logic [7:0]  data_byte
    );
        logic [31:0] c = crc_in ^ {24'h0, data_byte}; // XOR next byte into LSBs
        for (int i = 0; i < 8; i++) begin
            if (c[0]) c = (c >> 1) ^ 32'hEDB88320;
            else       c =  c >> 1;
        end
        return c;
    endfunction

    // internal registers
    logic [2:0]   pre_cnt;          // number of 0x55 seen in preamble (target 7)
    logic [3:0]   crc_cnt;          // counts 0..3 for FCS byte assembly
    logic [15:0]  hdr_cnt;          // 0..13 across 14B Ethernet header
    logic [15:0]  payload_cnt;      // payload byte index
    logic [15:0]  payload_len;      // ITCH length field (len of type+body)
    logic [47:0]  dest_mac_shift;   // shift register to build Destination address for comparison
    logic         mac_match;        // Destination address (DA) == our MAC or broadcast
    logic [31:0]  crc_reg;          // running reflected CRC accumulator
    logic [31:0]  crc_recv_shift;   // incoming FCS bytes (LSB-first)
    logic         this_cycle_match; // internal compare wire
    logic [31:0]  next_crc;         // next CRC value (for debug clarity)
    logic [31:0]  fcs_word;         // latched final 32-bit FCS (LSB-first)
    logic [15:0]  total_payload;    // ITCH total bytes inside L2: len + 2 length bytes
    logic         crc_started;      // marker that we seeded CRC on SFD
    logic [47:0]  full_dest;         // latched full destination MAC address


    // Main sequential block
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            // ---- Reset all state and counters (bring receiver state machine to a known point)
            state                <= IDLE;
            pre_cnt              <= 0;
            hdr_cnt              <= 0;
            payload_cnt          <= 0;
            payload_len          <= 0;
            mac_match            <= 0;
            payload_valid        <= 0;
            crc_cnt              <= 0;
            dest_mac_shift       <= 0;
            crc_reg              <= 32'hFFFF_FFFF;  // reflected init value
            crc_recv_shift       <= 0;
            crc_ok               <= 0;
            crc_valid            <= 0;
            crc_started          <= 0;
            fcs_word             <= 32'h0;
            total_payload        <= 16'h0;
            dbg_crc_calc         <= 32'h0;
            dbg_crc_recv         <= 32'h0;
            dbg_payload_len      <= 16'h0;
            dbg_total_payload    <= 16'h0;
            dbg_payload_cnt_last <= 16'h0;

        end else begin

            // ---- Per-cycle defaults (avoid accidental pulses)
            payload_valid <= 0; // will assert only when streaming a payload byte
            crc_valid     <= 0; // 1-cycle pulse when CRC result is available

            case (state)
                IDLE: begin
                    // Wait for first preamble byte (0x55)
                    if (rx_valid && rx_byte == 8'h55) begin
                        state   <= PREAMBLE;
                        pre_cnt <= 1;          // first 0x55 observed
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

                // SFD: expect 0xD5. On success, seed CRC and move to header.
                SFD: begin
                    if (rx_valid) begin
                        if (rx_byte == 8'hD5) begin
                            crc_reg         <= 32'hFFFFFFFF;    // Seed reflected CRC here. The SFD (0xD5) is NOT folded per 802.3.
                            crc_started     <= 1'b1;            // indicate CRC started
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

                // LOAD_HEADER: fold 14B (Destination Address/Source Address/Type) into CRC.
                // Also accumulate 6 bytes of DA and compare at the end of DA.
                LOAD_HEADER: begin
                    if (rx_valid) begin

                        // Fold each header byte into the reflected CRC.  LSB-first folding means we
                        // xor the incoming byte into the low bits and shift right in crc32_lsbf().
                        next_crc = crc32_lsbf(crc_reg, rx_byte);
                        crc_reg <= next_crc;

                        // Build destination MAC over first 6 header bytes
                        // We shift left by one byte and drop the oldest byte, so after 6 bytes
                        // dest_mac_shift holds DA[47:0] in natural big-endian order (as on the wire).
                        if (hdr_cnt < 6) begin
                            full_dest = {dest_mac_shift[39:0], rx_byte};
                            dest_mac_shift <= full_dest;

                            if (hdr_cnt == 5) begin
                                // Evaluate DA match once all 6 bytes are present
                                this_cycle_match = (full_dest == OUR_MAC) || (full_dest == MAC_BROADCAST);
                                mac_match <= this_cycle_match; // keep for payload phase
                            end
                        end

                        hdr_cnt <= hdr_cnt + 1;
                        // After DA(6)+SA(6)+Type(2) = 14 bytes, stream payload
                        if (hdr_cnt == 13) begin
                            state       <= LOAD_PAYLD;
                            payload_cnt <= 0;
                        end
                    end
                end

                // LOAD_PAYLD: fold every payload byte into CRC and stream it out
                // if (mac_match && payload_ready). Extract ITCH length from first
                // two bytes to know when payload ends (then go to CRC_CHECK).

                LOAD_PAYLD: begin
                    if (rx_valid) begin
                        // Fold payload byte into running CRC
                        next_crc = crc32_lsbf(crc_reg, rx_byte);
                        crc_reg <= next_crc;

                        // ITCH length is the first two payload bytes (big-endian)
                        if      (payload_cnt == 0) begin
                            payload_len[15:8] <= rx_byte;
                        end else if (payload_cnt == 1) begin
                            payload_len[7:0]  <= rx_byte;
                            
                            // total bytes inside Ethernet payload that belong to ITCH:
                            // len (type+body) + 2 (length field itself)
                            total_payload     <= {payload_len[15:8], rx_byte} + 16'd2;
                            dbg_payload_len   <= {payload_len[15:8], rx_byte};
                            dbg_total_payload <= {payload_len[15:8], rx_byte} + 16'd2;
                        end

                        // Only send payload when both the Destination MAC matched and downstream module is ready.
                        // This enforces backpressure correctly and prevents data loss by pausing output when the receiver can’t keep up.

                        if (mac_match && payload_ready) begin
                            payload_byte  <= rx_byte;
                            payload_valid <= 1;
                        end

                        // Detect last payload byte for this frame then move to CRC parsing
                        if (payload_cnt + 16'd1 == total_payload) begin
                            crc_cnt        <= 0;
                            crc_recv_shift <= 0;
                            dbg_payload_cnt_last<= payload_cnt + 16'd1; // bytes actually folded in this frame
                            state          <= CRC_CHECK;
                        end

                        payload_cnt <= payload_cnt + 1;
                    end
                end

                // CRC_CHECK: receive 4-byte FCS from the wire (LSB-first).
                // Once all 4 bytes are in, compare computed CRC (xorout) to received.
                // Emit crc_valid for 1 cycle; crc_ok indicates match.

                CRC_CHECK: begin
                    if (rx_valid) begin
                        unique case (crc_cnt)
                        0: begin crc_recv_shift[ 7: 0] <= rx_byte; crc_cnt <= 1; end
                        1: begin crc_recv_shift[15: 8] <= rx_byte; crc_cnt <= 2; end
                        2: begin crc_recv_shift[23:16] <= rx_byte; crc_cnt <= 3; end
                        3: begin

                            // Wire carries FCS LSB-first, i.e., we see byte0 (LSB), byte1, byte2, then byte3 (MSB).
                            // We collect them into crc_recv_shift little-endian, and on the final byte assemble
                            // a 32-bit word where [31:24] = last byte received (MSB) and [7:0] = first byte.
                            // This matches how we compare against the reflected crc_reg ^ 0xFFFF_FFFF.
                            logic [31:0] new_fcs;
                            new_fcs = {rx_byte, crc_recv_shift[23:0]}; // [31:24]=byte3, [7:0]=byte0
                            fcs_word     <= new_fcs;                   // Registered copy for debug/wave viewing

                            // Compare computed reflected CRC after xorout versus received FCS.
                            dbg_crc_calc <= (crc_reg ^ 32'hFFFF_FFFF);
                            dbg_crc_recv <= new_fcs;
                            crc_ok       <= ((crc_reg ^ 32'hFFFF_FFFF) == new_fcs);
                            crc_valid    <= 1'b1;

                            crc_started  <= 1'b0; // CRC finished
                            state        <= IDLE; // Wrap up frame, return to IDLE
                            crc_cnt      <= 0;
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
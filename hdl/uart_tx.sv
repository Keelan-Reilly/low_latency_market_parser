// uart_tx
//
// Purpose:
//   Transmit a 32-bit word over UART as 4 consecutive bytes, 8N1 format,
//   LSB-first within each byte, little-endian byte order on the wire.
//   The entire word is latched when accepted, ensuring consistent output
//   even if data_in changes mid-transmission.
//
// Operation:
//   • Ready is high in IDLE; new data is accepted only in this state.
//   • Each byte is sent with a start bit (low), 8 data bits (LSB-first), and a stop bit (high).
//   • Bytes are transmitted in order: [7:0], [15:8], [23:16], [31:24].
//   • Timing is derived from CLK_FREQ_HZ / BAUD_RATE to generate per-bit ticks.
//   • Busy stays high from the first start bit until the final stop bit.

module uart_tx #(
    parameter int CLK_FREQ_HZ = 250_000_000,
    parameter int BAUD_RATE   = 115200
) (
    input  logic        clk,        
    input  logic        rst_n,       
    input  logic [31:0] data_in,     // 32-bit word to send
    input  logic        data_valid,  // pulse high when data_in holds a new word
    output logic        tx_line,     // UART TX output line
    output logic        busy,        // high while any byte is being sent
    output logic        ready        // high when idle and ready to accept data
);

    // Clock ticks per UART bit
    localparam int BAUD_TICKS = CLK_FREQ_HZ / BAUD_RATE;
    logic [$clog2(BAUD_TICKS)-1:0] tick_cnt;               // counts clock cycles per UART bit

    // UART TX FSM states:
    //   IDLE  : Waiting for new data; line held high (idle level).
    //   START : Sending 1 start bit (low) to mark the beginning of a byte.
    //   DATA  : Sending 8 data bits, LSB-first.
    //   STOP  : Sending 1 stop bit (high); then either load the next byte or return to IDLE.
    
    typedef enum logic [1:0] {
        IDLE,
        START,
        DATA,
        STOP
    } st_t;
    st_t st;

    logic [31:0] word_reg;     // latched 32-bit word (held stable during TX)
    logic [1:0]  byte_idx;     // current byte index (0..3)
    logic [2:0]  bit_idx;      // current bit index within byte (0..7)
    logic [7:0]  sh;           // byte shift register for bit output


    // Accept condition: new word only when idle
    wire accept = (st == IDLE) && data_valid;  

    assign ready = (st == IDLE);
    assign busy  = (st != IDLE);

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            st       <= IDLE;
            tx_line  <= 1'b1;
            tick_cnt <= '0;
            byte_idx <= '0;
            bit_idx  <= '0;
            sh       <= '0;
            word_reg <= '0;
        end else begin
            unique case (st)
                // Wait for new data; latch word and prepare first byte
                IDLE: begin
                    tx_line  <= 1'b1;
                    tick_cnt <= '0;
                    bit_idx  <= '0;
                    byte_idx <= '0;
                    if (accept) begin
                        word_reg <= data_in;       // latch entire word
                        sh       <= data_in[7:0];  // first byte (LSB)
                        st       <= START;         // move to start bit
                    end
                end

                START: begin
                    tx_line <= 1'b0; // start bit
                    if (tick_cnt == BAUD_TICKS-1) begin
                        tick_cnt <= '0;
                        bit_idx  <= 3'd0;
                        st       <= DATA;
                    end else begin
                        tick_cnt <= tick_cnt + 1;
                    end
                end

                DATA: begin
                    tx_line <= sh[0];                     // output next bit
                    if (tick_cnt == BAUD_TICKS-1) begin
                        tick_cnt <= '0;
                        sh       <= {1'b0, sh[7:1]};     // shift right to get next bit
                        bit_idx  <= bit_idx + 1;

                        if (bit_idx == 3'd7) begin
                            st <= STOP;                  // after last data bit
                        end
                    end else begin
                        tick_cnt <= tick_cnt + 1;
                    end
                end

                STOP: begin
                    tx_line <= 1'b1; // stop bit
                    if (tick_cnt == BAUD_TICKS-1) begin
                        tick_cnt <= '0;
                        if (byte_idx == 2'd3) begin
                            st <= IDLE; // all 4 bytes sent
                        end else begin
                            byte_idx <= byte_idx + 1;

                            // Load next byte from latched word (little-endian order)
                            unique case (byte_idx)
                                2'd0: sh <= word_reg[15:8];
                                2'd1: sh <= word_reg[23:16];
                                2'd2: sh <= word_reg[31:24];
                                default: sh <= 8'h00;
                            endcase
                            st <= START;    // send next start bit
                        end
                    end else begin
                        tick_cnt <= tick_cnt + 1;
                    end
                end
            endcase
        end
    end
endmodule
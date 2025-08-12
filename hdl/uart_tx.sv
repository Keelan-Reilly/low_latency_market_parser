// uart_tx_bytes.sv — send 4 bytes, each 8N1, LSB-first per byte, little-endian byte order
module uart_tx #(
    parameter int CLK_FREQ_HZ = 100_000_000,
    parameter int BAUD_RATE   = 115200
) (
    input  logic        clk,
    input  logic        rst_n,
    input  logic [31:0] data_in,
    input  logic        data_valid,   // asserted by source when data_in holds a new word
    output logic        tx_line,
    output logic        busy,
    output logic        ready         // high exactly when we can accept (st==IDLE)
);

    localparam int BAUD_TICKS = CLK_FREQ_HZ / BAUD_RATE;
    logic [$clog2(BAUD_TICKS)-1:0] tick_cnt;

    typedef enum logic [1:0] {IDLE, START, DATA, STOP} st_t;
    st_t st;

    logic [31:0] word_reg;     // <— latched copy of the word
    logic [1:0]  byte_idx;
    logic [2:0]  bit_idx;
    logic [7:0]  sh;

    wire accept = (st == IDLE) && data_valid;  // one-cycle accept when idle

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
                IDLE: begin
                    tx_line  <= 1'b1;
                    tick_cnt <= '0;
                    bit_idx  <= '0;
                    byte_idx <= '0;
                    if (accept) begin
                        // Latch the whole word atomically
                        word_reg <= data_in;
                        // Load lowest byte first (little-endian on the wire)
                        sh       <= data_in[7:0];
                        st       <= START;
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
                    tx_line <= sh[0]; // LSB-first
                    if (tick_cnt == BAUD_TICKS-1) begin
                        tick_cnt <= '0;
                        sh       <= {1'b0, sh[7:1]}; // shift right
                        bit_idx  <= bit_idx + 1;
                        if (bit_idx == 3'd7) begin
                            st <= STOP; // after 8th bit
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
                            // Load next byte from latched word_reg (not live data_in!)
                            unique case (byte_idx)
                                2'd0: sh <= word_reg[15:8];
                                2'd1: sh <= word_reg[23:16];
                                2'd2: sh <= word_reg[31:24];
                                default: sh <= 8'h00;
                            endcase
                            st <= START;
                        end
                    end else begin
                        tick_cnt <= tick_cnt + 1;
                    end
                end
            endcase
        end
    end
endmodule
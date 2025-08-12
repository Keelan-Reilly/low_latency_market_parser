`timescale 1ns/1ps
module parser (
    input  logic        clk,
    input  logic        rst_n,
    input  logic [7:0]  in_byte,
    input  logic        in_valid,
    output logic        in_ready,
    output logic [7:0]  msg_type,
    output logic        field_valid,
    output logic [63:0] order_id,
    output logic [31:0] price,
    output logic [31:0] volume,
    output logic msg_start
);
    assign in_ready = 1'b1;

    typedef enum logic [1:0] {WAIT_HEADER, READ_FIELDS, DISPATCH, SKIP} state_t;
    state_t state;

    // header
    logic [15:0] length;
    logic [7:0]  len_hi, len_lo;
    logic [7:0]  type_reg;

    // counters
    logic [15:0] cnt;        // bytes since TYPE (i.e., within message body)
    logic [15:0] body_left;  // (length - 1) bytes remaining after TYPE

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            msg_start <= 1'b0;
            state       <= WAIT_HEADER;
            {len_hi,len_lo} <= '0;
            length      <= '0;
            type_reg    <= '0;
            cnt         <= '0;
            body_left   <= '0;
            field_valid <= 1'b0;
            msg_type    <= '0;
            order_id    <= '0;
            price       <= '0;
            volume      <= '0;
        end else begin
            field_valid <= 1'b0;
            msg_start <= 1'b0; // default

            case (state)
            WAIT_HEADER: begin
                if (in_valid) begin
                    if (cnt == 0) begin
                        msg_start <= 1'b1; 
                        len_hi <= in_byte; 
                        cnt <= 1;
                    end else if (cnt == 1) begin
                        len_lo <= in_byte; cnt <= 2;
                    end else if (cnt == 2) begin
                        type_reg  <= in_byte;                // message type
                        length    <= {len_hi, len_lo};       // total bytes: [type + body]
                        body_left <= {len_hi, len_lo} - 16'd1; // exclude TYPE just read
                        cnt       <= 0;

                        // clear accumulators for this message
                        order_id  <= '0;
                        price     <= '0;
                        volume    <= '0;

                        // Only parse ITCH 'P' (Trade, non-cross). Others → SKIP.
                        state <= (in_byte == 8'h50) ? READ_FIELDS : SKIP;
                    end
                end
            end

            // cnt == 0 is first byte AFTER TYPE
            READ_FIELDS: begin
                if (in_valid) begin
                    // ITCH 5.0 'P' Trade offsets (bytes after TYPE):
                    //  00..01 Stock Locate      (2)    SKIP
                    //  02..03 Tracking Number   (2)    SKIP
                    //  04..09 Timestamp         (6)    SKIP (we ignore)
                    //  10..17 Order Ref Number  (8) -> order_id
                    //  18     Buy/Sell          (1)    SKIP
                    //  19..22 Shares            (4) -> volume
                    //  23..30 Stock             (8)    SKIP
                    //  31..34 Price             (4) -> price  (integer, $/1e4)
                    //  35..42 Match Number      (8)    SKIP

                    if (cnt >= 10 && cnt <= 17) begin
                        order_id <= (order_id << 8) | in_byte;
                    end
                    if (cnt >= 19 && cnt <= 22) begin
                        volume   <= (volume   << 8) | in_byte;
                    end
                    if (cnt >= 31 && cnt <= 34) begin
                        price    <= (price    << 8) | in_byte;
                    end

                    // Done with this message body?
                    if (cnt + 1 == body_left) begin
                        state <= DISPATCH;
                        cnt   <= 0;
                    end else begin
                        cnt <= cnt + 1;
                    end
                end
            end

            DISPATCH: begin
                field_valid <= 1'b1;
                msg_type    <= type_reg;   // should be 8'h50
                state       <= WAIT_HEADER;
            end

            SKIP: begin
                if (in_valid) begin
                    if (cnt + 1 == body_left) begin
                        state <= WAIT_HEADER;
                        cnt   <= 0;
                    end else begin
                        cnt <= cnt + 1;
                    end
                end
            end

            endcase
        end
    end
endmodule
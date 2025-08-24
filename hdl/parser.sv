`timescale 1ns/1ps

// Module: parser
//
// Purpose:
//   Consumes a continuous ITCH 5.0 market data byte stream (1 byte per cycle)
//   and extracts key fields from "P" (Trade, non-cross) messages.
//   Operates as a streaming state machine that never stalls the upstream.
//
// Function:
//   • Detects message boundaries from the 3-byte ITCH header:
//       - Length_hi (MSB of message length)
//       - Length_lo (LSB of message length)
//       - Message type byte
//   • Emits msg_start on the first byte of every message.
//   • For 'P' messages only, accumulates and outputs:
//       - order_id  (8 bytes, big-endian)
//       - volume    (4 bytes, big-endian)
//       - price     (4 bytes, big-endian)
//   • Ignores unsupported message types by skipping their bodies.
//   • Asserts field_valid for exactly one cycle when outputs are valid.
//
// FSM States:
//   1. WAIT_HEADER – Reads header bytes and decides whether to parse or skip.
//   2. READ_FIELDS – Extracts relevant fields for 'P' messages.
//   3. DISPATCH    – Outputs parsed fields and signals validity.
//   4. SKIP        – Discards bytes for unsupported message types.
//
// Notes:
//   - Upstream is always accepted (in_ready = 1).
//   - Outputs are stable only during the one-cycle field_valid pulse.

module parser (
    // Clock / reset
    input  logic        clk,
    input  logic        rst_n,

    // Input byte stream (1 byte / cycle)
    input  logic [7:0]  in_byte,     // Next byte from upstream (ITCH stream, 1 byte/cycle)
    input  logic        in_valid,    // High when in_byte is valid this cycle

    // Handshake back to upstream
    output logic        in_ready,    // High when parser can accept in_byte (always 1 in this design)

    // Decoded message info
    output logic [7:0]  msg_type,    // ITCH message type (only valid when field_valid=1)
    output logic        field_valid, // One-cycle pulse when msg_type/order_id/price/volume outputs are valid

    //  Decoded 'P' Trade fields
    output logic [63:0] order_id,    // 8-byte Order Reference Number (big-endian assembly)
    output logic [31:0] price,       // 4-byte Price (integer, e.g. $/1e4)
    output logic [31:0] volume,      // 4-byte Volume/Shares

    // Message start indicator
    output logic msg_start           // One-cycle pulse on the first byte of each ITCH message (length MSB)
);
     // This parser never back-pressures the upstream (simple model).
    assign in_ready = 1'b1;

    // FSM: controls high-level message parsing flow
    typedef enum logic [1:0] {
        WAIT_HEADER,
        READ_FIELDS,
        SKIP
    } state_t;
    state_t state;

    // Header assembly / bookkeeping
    logic [15:0] length;          // Full 16-bit message length = {len_hi, len_lo}
    logic [7:0]  len_hi;          // First length byte read from header (MSB of message length)
    logic [7:0]  len_lo;          // Second length byte read from header (LSB of message length)
    logic [7:0]  type_reg;        // captured message type

    // Body counters
    logic [15:0] cnt;        // bytes after TYPE (i.e., within message body)
    logic [15:0] body_left;  // number of bytes to consume AFTER TYPE (= length-1)
    

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
            // Default de-assert
            field_valid <= 1'b0;
            msg_start <= 1'b0; 

            case (state)

            // WAIT_HEADER: Read the 3-byte ITCH message header in sequence

            WAIT_HEADER: begin
                if (in_valid) begin
                    if (cnt == 0) begin
                        msg_start <= 1'b1;   // mark first byte of a new message
                        len_hi <= in_byte;   // Store the high byte (MSB) of the 16-bit message length
                        cnt <= 1;
                    end else if (cnt == 1) begin
                        len_lo <= in_byte;   // Store the low byte (LSB) of the 16-bit message length
                        cnt <= 2;
                    end else if (cnt == 2) begin
                        type_reg  <= in_byte;                  // capture message type
                        length    <= {len_hi, len_lo};         // Assemble total message length from MSB + LSB
                        body_left <= {len_hi, len_lo} - 16'd1; // Remaining bytes after TYPE
                        cnt       <= 0;

                        // clear accumulators for the new message
                        order_id  <= '0;
                        price     <= '0;
                        volume    <= '0;

                        // Only parse ITCH 'P' (Trade, non-cross). Others are skipped.
                        state <= (in_byte == 8'h50) ? READ_FIELDS : SKIP;
                    end
                end
            end

            // READ_FIELDS : Process message body bytes after TYPE
            //   ITCH 5.0 'P' (Trade, non-cross) field offsets (relative to first byte after TYPE):
            //     10..17 : order_id   (8 bytes, big-endian)
            //     19..22 : volume     (4 bytes, big-endian)
            //     31..34 : price      (4 bytes, big-endian)
            //   All other byte positions are skipped.
            READ_FIELDS: begin
                if (in_valid) begin
                    // Big-endian accumulate: shift existing value 8 left, OR in new byte.
                    if (cnt >= 10 && cnt <= 17) begin
                        order_id <= (order_id << 8) | in_byte;  // 8 bytes total
                    end
                    if (cnt >= 19 && cnt <= 22) begin
                        volume   <= (volume   << 8) | in_byte;  // 4 bytes total
                    end
                    if (cnt >= 31 && cnt <= 34) begin
                        price    <= (price    << 8) | in_byte;  // 4 bytes total
                    end

                    // EARLY FIRE: when price completes
                    if (cnt == 16'd34) begin
                    field_valid <= 1'b1;
                    msg_type    <= type_reg;    // should be 8'h50 for 'P'
                    end

                    // If done with this message body move to dispatch
                    if (cnt + 1 == body_left) begin
                        state <= WAIT_HEADER;
                        cnt   <= 0;
                    end else begin
                        cnt <= cnt + 1;
                    end
                end
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
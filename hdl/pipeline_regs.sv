`timescale 1ns/1ps

// pipeline_regs
//
// Purpose:
//   Provides single-register pipeline stages between:
//     • Ethernet RX to Parser
//     • Parser to Trading Logic
//     • Trading Logic to TX
//
//   Each stage:
//     • Uses a 1-byte register to break timing paths.
//     • Preserves message ordering.
//     • Supports full backpressure (no data loss).
//
//   Also carries per-message timestamps so we can record exactly when the same
//   message entered, left the parser, reached the logic stage, and produced a decision.
//
// Timing behaviour (1-register buffers):
//   • Upstream asserts *_valid with data.
//   • Data is captured when both upstream_valid and local_ready are high.
//   • The stage holds the data and *_out_valid high until the downstream asserts *_out_ready.
//
// Timestamp behaviour:
//   • msg_start: one-cycle pulse from the parser at the first byte of a message.
//       Latch cycle_cnt into ingress_last at that moment.
//   • When the parser asserts p2l_valid:
//       p2l_timestamp = cycle_cnt   (parser exit time for this message)
//       ingress_s2    = ingress_last (ingress time aligned to this message)
//   • When the Logic to TX stage accepts a decision:
//       Freeze t_ingress, t_parser, t_logic, and t_decision for that decision word.

module pipeline_regs (
    input  logic        clk,
    input  logic        rst_n,

    // Ethernet RX to Parser
    // Input stream from RX to parser (payload byte-stream)
    input  logic [7:0]  rx2p_in,        // data byte from RX
    input  logic        rx2p_valid,     // byte valid from RX
    input  logic        rx2p_out_ready, // Parser-side ready (downstream)
    output logic        rx2p_ready,     // backpressure to RX
    output logic [7:0]  rx2p_out,       // registered byte to Parser
    output logic        rx2p_out_valid, // byte valid to Parser

    // Parser to Trading Logic
    // Parsed message fields, valid when a message completes
    input  logic [7:0]  p2l_type,       // ITCH type
    input  logic        p2l_valid,      // parsed fields valid (1 cycle)
    input  logic [63:0] p2l_order_id,   // parsed order_id
    input  logic [31:0] p2l_price,      // parsed price
    input  logic [31:0] p2l_volume,     // parsed volume
    output logic        p2l_ready,      // backpressure to Parser
    output logic [7:0]  p2l_type_out,   // registered type to Logic
    output logic [63:0] p2l_order_id_out,
    output logic [31:0] p2l_price_out,
    output logic [31:0] p2l_volume_out,
    output logic        p2l_out_valid,  // fields valid to Logic
    input  logic        p2l_out_ready,  // Logic ready

    // Trading Logic to Uart TX
    // Decision word streams into TX
    input  logic [7:0]  l2t_type,       // decision type 
    input  logic        l2t_valid,      // decision valid
    input  logic [31:0] l2t_data,       // decision word (e.g., price)
    output logic        l2t_ready,      // backpressure to Logic
    output logic [7:0]  l2t_type_out,   // registered type to TX
    output logic [31:0] l2t_data_out,   // registered data to TX
    output logic        l2t_out_valid,  // decision valid to TX
    input  logic        l2t_out_ready,  // TX ready

    // Timestamping
    input  logic [31:0] cycle_cnt,      // free-running cycle counter
    input  logic        msg_start,      // 1-cycle pulse at message start (from parser)

    // Aligned timestamps for the SAME message as l2t_* outputs
    output logic [31:0] t_ingress,      // first payload byte time for the message
    output logic [31:0] t_decision,     // time decision was accepted into stage 3
    output logic [31:0] t_parser,       // parser “exit” time for the message
    output logic [31:0] t_logic,        // logic accept time (same as decision)
    output logic [31:0] t_parser_event  // convenience: raw parser event timestamp
);


    // Stage 1: RX to Parser
    //   Buffers a single byte between the Ethernet RX and the parser.
    //   Accepts data when empty or immediately after the parser has accepted the previous byte.
    //   Holds the byte until the parser is ready to take it.

    logic [7:0] rx2p_data;
    logic       rx2p_data_valid;

    // Ready if buffer empty (no held data) OR downstream is ready to take it now.
    assign rx2p_ready = !rx2p_data_valid || rx2p_out_ready;

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            rx2p_data_valid <= 1'b0;
            rx2p_data       <= '0;
        end else begin
            if (rx2p_ready && rx2p_valid) begin
                // Capture incoming byte when we can accept
                rx2p_data       <= rx2p_in;
                rx2p_data_valid <= 1'b1;
            end else if (rx2p_out_ready) begin
                // Downstream consumed the buffered byte
                rx2p_data_valid <= 1'b0;
            end
        end
    end

    assign rx2p_out       = rx2p_data;
    assign rx2p_out_valid = rx2p_data_valid;

    // Stage 2: Parser to Logic
    //   Buffers an entire parsed message between the parser and the trading logic.
    //   Carries message fields plus timestamps so that ingress time and parser completion time can be tracked for each message.

    logic [7:0]  p2l_type_reg;
    logic [63:0] p2l_order_id_reg;
    logic [31:0] p2l_price_reg;
    logic [31:0] p2l_volume_reg;
    logic        p2l_data_valid;

    // Per-message timestamps
    logic [31:0] ingress_last;   // updated exactly at msg_start
    logic [31:0] ingress_s2;     // carried with the parsed fields to stage 3
    logic [31:0] p2l_timestamp;  // parser “exit” time for this message

    // Latch ingress time when a new message starts (1-cycle pulse from parser)
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            ingress_last <= '0;
        end else if (msg_start) begin
            ingress_last <= cycle_cnt;
        end
    end

    // Standard ready rule for 1-deep buffer
    assign p2l_ready = !p2l_data_valid || p2l_out_ready;

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            p2l_data_valid   <= 1'b0;
            p2l_type_reg     <= '0;
            p2l_order_id_reg <= '0;
            p2l_price_reg    <= '0;
            p2l_volume_reg   <= '0;
            p2l_timestamp    <= '0;
            ingress_s2       <= '0;
        end else begin
            if (p2l_ready && p2l_valid) begin
                // Capture parsed fields & align timestamps to THIS message
                p2l_type_reg     <= p2l_type;
                p2l_order_id_reg <= p2l_order_id;
                p2l_price_reg    <= p2l_price;
                p2l_volume_reg   <= p2l_volume;
                p2l_data_valid   <= 1'b1;

                p2l_timestamp    <= cycle_cnt;    // time when parser produced this event
                ingress_s2       <= ingress_last; // ingress captured at msg_start
            end else if (p2l_out_ready) begin
                // Downstream consumed
                p2l_data_valid <= 1'b0;
            end
        end
    end

    assign p2l_type_out       = p2l_type_reg;
    assign p2l_order_id_out   = p2l_order_id_reg;
    assign p2l_price_out      = p2l_price_reg;
    assign p2l_volume_out     = p2l_volume_reg;
    assign p2l_out_valid      = p2l_data_valid;


    // Stage 3: Trading Logic to TX
    //   Buffers the trading decision before it is sent to TX.
    //   Captures and freezes all relevant timestamps for the same message when a decision is accepted.

    logic [7:0]  l2t_type_reg;
    logic [31:0] l2t_data_reg;
    logic        l2t_data_valid;

    // Captured timestamps for the SAME decision/word
    logic [31:0] t_ingress_cap, t_parser_cap, t_logic_cap, t_decision_cap;

    // Standard ready rule for 1-deep buffer
    assign l2t_ready = !l2t_data_valid || l2t_out_ready;

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            l2t_data_valid <= 1'b0;
            l2t_type_reg   <= '0;
            l2t_data_reg   <= '0;

            t_ingress_cap  <= '0;
            t_parser_cap   <= '0;
            t_logic_cap    <= '0;
            t_decision_cap <= '0;
        end else begin
            // Downstream consumed this decision
            if (l2t_out_ready && l2t_data_valid)
                l2t_data_valid <= 1'b0;

            // Accept a new decision when buffer empty (or just consumed)
            if ((!l2t_data_valid || l2t_out_ready) && l2t_valid) begin
                l2t_type_reg   <= l2t_type;
                l2t_data_reg   <= l2t_data;
                l2t_data_valid <= 1'b1;

                // Freeze aligned timestamps for THIS decision
                t_logic_cap    <= cycle_cnt;     // logic accept time
                t_decision_cap <= cycle_cnt;     // decision time (same as logic accept)
                t_parser_cap   <= p2l_timestamp; // parser exit time for this message
                t_ingress_cap  <= ingress_s2;    // ingress aligned to this message
            end
        end
    end

    assign l2t_type_out  = l2t_type_reg;
    assign l2t_data_out  = l2t_data_reg;
    assign l2t_out_valid = l2t_data_valid;


    // Timestamp outputs (registered, message-aligned)

    assign t_ingress      = t_ingress_cap;
    assign t_parser       = t_parser_cap;
    assign t_logic        = t_logic_cap;
    assign t_decision     = t_decision_cap;
    assign t_parser_event = p2l_timestamp; // handy for logs (parser-side timing)

    // Assertions (optional, enabled with +define+ASSERT_ON)
    // Ensure data stays stable when downstream is stalled

`ifdef ASSERT_ON
    // Stage 1: RX→Parser
    assert property (@(posedge clk) disable iff(!rst_n)
        rx2p_out_valid && !rx2p_out_ready |-> $stable(rx2p_out));

    // Stage 2: Parser→Logic
    assert property (@(posedge clk) disable iff(!rst_n)
        p2l_out_valid && !p2l_out_ready
        |-> $stable({p2l_type_out, p2l_order_id_out, p2l_price_out, p2l_volume_out}));

    // Stage 3: Logic→TX
    assert property (@(posedge clk) disable iff(!rst_n)
        l2t_out_valid && !l2t_out_ready |-> $stable({l2t_type_out, l2t_data_out}));
`endif

endmodule

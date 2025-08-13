`timescale 1ns/1ps

// Module: trading_logic
//
// Purpose:
//   Consume parsed ITCH fields and issue a simple trading decision.
//   Current rule: for 'P' (Trade, non-cross) messages, BUY when price < THRESHOLD.

module trading_logic #(
    parameter int THRESHOLD = 2_000_000  // Adjusted threshold above example trade price 10000
) (
    input  logic        clk,
    input  logic        rst_n,
    input  logic        field_valid,
    input  logic [7:0]  msg_type,
    input  logic [63:0] order_id,
    input  logic [31:0] price,
    input  logic [31:0] volume,
    output logic        decision_valid,
    output logic [7:0]  decision_type,
    output logic [63:0] d_order_id,
    output logic [31:0] d_price,
    output logic [31:0] d_volume,
    output logic        in_ready
);

assign in_ready = 1'b1;

// Decision rule: Buy if trade message and price below threshold
always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
        decision_valid <= 1'b0;
        decision_type  <= 8'd0;
        d_order_id     <= 64'd0;
        d_price        <= 32'd0;
        d_volume       <= 32'd0;
    end else begin
        if (field_valid && msg_type == 8'h50 && price < THRESHOLD) begin
            decision_valid <= 1'b1;
            decision_type  <= msg_type;
            d_order_id     <= order_id;
            d_price        <= price;
            d_volume       <= volume;
        end else begin
            decision_valid <= 1'b0;
        end
    end
end

endmodule
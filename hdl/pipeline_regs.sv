`timescale 1ns/1ps

// ──────────────────────────────────────────────────────────────────────────────
// Reusable 1-deep skid buffer (fall-through when downstream is ready)
// ──────────────────────────────────────────────────────────────────────────────
module skid_buffer #(
    parameter int W = 8
)(
    input  logic         clk,
    input  logic         rst_n,
    // upstream
    input  logic [W-1:0] in_data,
    input  logic         in_valid,
    output logic         in_ready,
    // downstream
    output logic [W-1:0] out_data,
    output logic         out_valid,
    input  logic         out_ready
);
    logic         saved_valid;
    logic [W-1:0] saved_data;

    // fall-through when not holding saved data
    assign out_valid = saved_valid | in_valid;
    assign out_data  = saved_valid ? saved_data : in_data;
    assign in_ready  = ~saved_valid | out_ready;

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            saved_valid <= 1'b0;
            saved_data  <= '0;
        end else begin
            if (out_ready) saved_valid <= 1'b0;
            if (in_valid && ~out_ready && ~saved_valid) begin
                saved_valid <= 1'b1;
                saved_data  <= in_data;
            end
        end
    end
endmodule


// ──────────────────────────────────────────────────────────────────────────────
module pipeline_regs (
    input  logic        clk,
    input  logic        rst_n,

    // Ethernet RX → Parser (bytes)
    input  logic [7:0]  rx2p_in,
    input  logic        rx2p_valid,
    input  logic        rx2p_out_ready,
    output logic        rx2p_ready,
    output logic [7:0]  rx2p_out,
    output logic        rx2p_out_valid,

    // Parser → Trading Logic (parsed fields)
    input  logic [7:0]  p2l_type,
    input  logic        p2l_valid,
    input  logic [63:0] p2l_order_id,
    input  logic [31:0] p2l_price,
    input  logic [31:0] p2l_volume,
    output logic        p2l_ready,
    output logic [7:0]  p2l_type_out,
    output logic [63:0] p2l_order_id_out,
    output logic [31:0] p2l_price_out,
    output logic [31:0] p2l_volume_out,
    output logic        p2l_out_valid,
    input  logic        p2l_out_ready,

    // Trading Logic → TX (decision word)
    input  logic [7:0]  l2t_type,
    input  logic        l2t_valid,
    input  logic [31:0] l2t_data,
    output logic        l2t_ready,
    output logic [7:0]  l2t_type_out,
    output logic [31:0] l2t_data_out,
    output logic        l2t_out_valid,
    input  logic        l2t_out_ready,

    // Timestamps
    input  logic [31:0] cycle_cnt,
    input  logic        msg_start,

    // Timestamps aligned to the SAME message as l2t_* outputs
    output logic [31:0] t_ingress,
    output logic [31:0] t_decision,
    output logic [31:0] t_parser,
    output logic [31:0] t_logic,
    output logic [31:0] t_parser_event
);
    // ── Stage 1: RX → Parser (byte lane, fall-through) ────────────────────────
    skid_buffer #(.W(8)) s1 (
        .clk       (clk),
        .rst_n     (rst_n),
        .in_data   (rx2p_in),
        .in_valid  (rx2p_valid),
        .in_ready  (rx2p_ready),
        .out_data  (rx2p_out),
        .out_valid (rx2p_out_valid),
        .out_ready (rx2p_out_ready)
    );

    // ── Ingress timestamp (per message, captured at msg_start) ────────────────
    logic [31:0] ingress_last;
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n)           ingress_last <= '0;
        else if (msg_start)   ingress_last <= cycle_cnt;
    end

    // ── Stage 2: Parser → Logic (bundle + fall-through) ──────────────────────
    typedef struct packed {
        logic [7:0]  typ;
        logic [63:0] oid;
        logic [31:0] prc;
        logic [31:0] vol;
        logic [31:0] t_ing;   // ingress aligned to this message
        logic [31:0] t_par;   // parser “exit” (field_valid cycle)
    } p2l_bus_t;

    p2l_bus_t p2l_bus_in, p2l_bus_out;

    // Build the input bundle (timestamps are evaluated on the handshake cycle)
    assign p2l_bus_in.typ  = p2l_type;
    assign p2l_bus_in.oid  = p2l_order_id;
    assign p2l_bus_in.prc  = p2l_price;
    assign p2l_bus_in.vol  = p2l_volume;
    assign p2l_bus_in.t_ing= ingress_last;
    assign p2l_bus_in.t_par= cycle_cnt;

    // Skid buffer for the whole message bundle
    wire p2l_sf_in_ready;
    skid_buffer #(.W($bits(p2l_bus_t))) s2 (
        .clk       (clk),
        .rst_n     (rst_n),
        .in_data   (p2l_bus_in),
        .in_valid  (p2l_valid),
        .in_ready  (p2l_sf_in_ready),
        .out_data  (p2l_bus_out),
        .out_valid (p2l_out_valid),
        .out_ready (p2l_out_ready)
    );
    assign p2l_ready          = p2l_sf_in_ready;
    assign p2l_type_out       = p2l_bus_out.typ;
    assign p2l_order_id_out   = p2l_bus_out.oid;
    assign p2l_price_out      = p2l_bus_out.prc;
    assign p2l_volume_out     = p2l_bus_out.vol;

    // convenient raw parser event time (same message as p2l_*_out signals)
    assign t_parser_event = p2l_bus_out.t_par;

    // ── Stage 3: Logic → TX (decision bundle + fall-through) ─────────────────
    typedef struct packed {
        logic [7:0]  typ;
        logic [31:0] dat;
        logic [31:0] t_ing;
        logic [31:0] t_par;
        logic [31:0] t_log;
        logic [31:0] t_dec;
    } l2t_bus_t;

    l2t_bus_t l2t_bus_in, l2t_bus_out;

    // Build decision bundle (t_log/t_dec captured at accept into this stage)
    assign l2t_bus_in.typ   = l2t_type;
    assign l2t_bus_in.dat   = l2t_data;
    assign l2t_bus_in.t_ing = p2l_bus_out.t_ing;
    assign l2t_bus_in.t_par = p2l_bus_out.t_par;
    assign l2t_bus_in.t_log = cycle_cnt;
    assign l2t_bus_in.t_dec = cycle_cnt;

    skid_buffer #(.W($bits(l2t_bus_t))) s3 (
        .clk       (clk),
        .rst_n     (rst_n),
        .in_data   (l2t_bus_in),
        .in_valid  (l2t_valid),
        .in_ready  (l2t_ready),
        .out_data  (l2t_bus_out),
        .out_valid (l2t_out_valid),
        .out_ready (l2t_out_ready)
    );

    assign l2t_type_out = l2t_bus_out.typ;
    assign l2t_data_out = l2t_bus_out.dat;

    // Final, message-aligned timestamps (carried with the decision)
    assign t_ingress  = l2t_bus_out.t_ing;
    assign t_parser   = l2t_bus_out.t_par;
    assign t_logic    = l2t_bus_out.t_log;
    assign t_decision = l2t_bus_out.t_dec;

`ifdef ASSERT_ON
    // Stage 1: RX→Parser stability when stalled
    assert property (@(posedge clk) disable iff(!rst_n)
        rx2p_out_valid && !rx2p_out_ready |-> $stable(rx2p_out));

    // Stage 2: Parser→Logic bundle stable when stalled
    assert property (@(posedge clk) disable iff(!rst_n)
        p2l_out_valid && !p2l_out_ready
        |-> $stable({p2l_type_out, p2l_order_id_out, p2l_price_out, p2l_volume_out}));

    // Stage 3: Logic→TX bundle stable when stalled
    assert property (@(posedge clk) disable iff(!rst_n)
        l2t_out_valid && !l2t_out_ready |-> $stable({l2t_type_out, l2t_data_out}));
`endif
endmodule
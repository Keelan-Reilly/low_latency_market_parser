`timescale 1ns/1ps
// Minimal, implementable top with pipeline_regs.
// Only real I/O are clk, rst_n, rx_byte, rx_valid, uart_tx.
// All debug/timestamps stay internal (no I/O bloat).

module fpga_top (
  input  logic        clk,
  input  logic        rst_n,

  // In a real board build, these would come from a MAC/PHY shim or test feeder
  input  logic [7:0]  rx_byte,      // incoming byte (1 per cycle)
  input  logic        rx_valid,     // qualifies rx_byte

  // UART output pin
  output logic        uart_tx
);
  // -----------------------------
  // Stage 0: Ethernet RX outputs
  // -----------------------------
  logic [7:0]  payload_byte;
  logic        payload_valid;
  logic        payload_ready;

  // -----------------------------
  // pipeline_regs (Stage 1/2/3)
  // -----------------------------
  // ETH → Parser (Stage 1 buffer)
  logic [7:0]  rx2p_out;
  logic        rx2p_out_valid;

  // Parser → Logic (Stage 2 buffer)
  logic        p2l_out_valid;
  logic [7:0]  p2l_type_out;
  logic [63:0] p2l_order_id_out;
  logic [31:0] p2l_price_out, p2l_volume_out;

  // Logic → TX (Stage 3 buffer)
  logic        l2t_out_valid;
  logic [7:0]  l2t_type_out;
  logic [31:0] l2t_data_out;

  // -----------------------------
  // Parser outputs (pre-stage2)
  // -----------------------------
  logic        field_valid;
  logic [7:0]  msg_type;
  logic [63:0] order_id;
  logic [31:0] price, volume;

  // -----------------------------
  // Trading logic & UART wires
  // -----------------------------
  logic        decision_valid;
  logic [7:0]  decision_type;
  logic [31:0] decision_data;

  logic        logic_ready;          // backpressure to parser via stage-2
  logic        uart_ready, uart_busy;
  wire         uart_ready_masked = uart_ready; // no external stalling in FPGA top

  // Timestamping (internal only, not exported)
  logic [31:0] cycle_cnt;
  logic        parser_msg_start;
  logic [31:0] t_ingress, t_parser, t_parser_event, t_logic, t_decision;

  // Free-running cycle counter (helps timing correlation if you ever probe with ILA)
  always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) cycle_cnt <= 32'd0;
    else        cycle_cnt <= cycle_cnt + 1;
  end

  // ========= Ethernet RX =========
  eth_rx u_rx (
    .clk           (clk),
    .rst_n         (rst_n),
    .rx_byte       (rx_byte),
    .rx_valid      (rx_valid),

    .payload_byte  (payload_byte),
    .payload_valid (payload_valid),
    .payload_ready (payload_ready),

    // CRC/debug left unconnected in FPGA top
    .crc_ok        (),
    .crc_valid     (),
    .dbg_crc_calc        (),
    .dbg_crc_recv        (),
    .dbg_payload_len     (),
    .dbg_total_payload   (),
    .dbg_payload_cnt_last()
  );

  // ========= Pipeline registers (stage boundaries + timestamps) =========
  pipeline_regs u_prg (
    .clk       (clk),
    .rst_n     (rst_n),

    // Stage 1: ETH → Parser
    .rx2p_in         (payload_byte),
    .rx2p_valid      (payload_valid),
    .rx2p_ready      (payload_ready),
    .rx2p_out        (rx2p_out),
    .rx2p_out_valid  (rx2p_out_valid),
    .rx2p_out_ready  (1'b1),

    // Stage 2: Parser → Logic
    .p2l_type        (msg_type),
    .p2l_valid       (field_valid),
    .p2l_order_id    (order_id),
    .p2l_price       (price),
    .p2l_volume      (volume),
    .p2l_ready       (), // not used (stage is 1-deep and push-driven by pulses)
    .p2l_type_out    (p2l_type_out),
    .p2l_order_id_out(p2l_order_id_out),
    .p2l_price_out   (p2l_price_out),
    .p2l_volume_out  (p2l_volume_out),
    .p2l_out_valid   (p2l_out_valid),
    .p2l_out_ready   (logic_ready),

    // Stage 3: Logic → TX
    .l2t_type        (decision_type),
    .l2t_valid       (decision_valid),
    .l2t_data        (decision_data),
    .l2t_ready       (), // not used
    .l2t_type_out    (l2t_type_out),
    .l2t_data_out    (l2t_data_out),
    .l2t_out_valid   (l2t_out_valid),
    .l2t_out_ready   (uart_ready_masked),

    // Timestamps (kept internal)
    .cycle_cnt       (cycle_cnt),
    .t_ingress       (t_ingress),
    .t_parser        (t_parser),
    .t_parser_event  (t_parser_event),
    .t_logic         (t_logic),
    .t_decision      (t_decision),
    .msg_start       (parser_msg_start)
  );

  // ========= Parser =========
  parser u_pr (
    .clk        (clk),
    .rst_n      (rst_n),
    .in_byte    (rx2p_out),
    .in_valid   (rx2p_out_valid),
    .in_ready   (),          // parser accepts always (your design does in_ready=1)
    .msg_type   (msg_type),
    .field_valid(field_valid),
    .order_id   (order_id),
    .price      (price),
    .volume     (volume),
    .msg_start  (parser_msg_start)
  );

  // ========= Trading logic =========
  trading_logic u_tl (
    .clk            (clk),
    .rst_n          (rst_n),
    .field_valid    (p2l_out_valid),
    .msg_type       (p2l_type_out),
    .order_id       (p2l_order_id_out),
    .price          (p2l_price_out),
    .volume         (p2l_volume_out),
    .decision_valid (decision_valid),
    .decision_type  (decision_type),
    .d_order_id     (),
    .d_price        (decision_data),
    .d_volume       (),
    .in_ready       (logic_ready)
  );

  // ========= UART TX =========
  uart_tx u_uart (
    .clk        (clk),
    .rst_n      (rst_n),
    .data_in    (l2t_data_out),
    .data_valid (l2t_out_valid),
    .tx_line    (uart_tx),
    .busy       (uart_busy),
    .ready      (uart_ready)
  );

endmodule

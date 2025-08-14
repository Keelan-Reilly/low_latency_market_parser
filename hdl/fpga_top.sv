`timescale 1ns/1ps
// Minimal synthesizable top-level for FPGA deployment with Ethernet RX,
// parser, trading logic, and UART TX stages connected through pipeline_regs.
// Only real I/O: clk, rst_n, rx_byte, rx_valid, uart_tx.
// All debug/timestamp signals remain internal to avoid I/O bloat.
// Suitable for actual FPGA builds; no testbench hooks.

module fpga_top (
  input  logic        clk,       // System clock
  input  logic        rst_n,     // Active-low asynchronous reset

  // Ethernet RX interface (e.g., from MAC/PHY or test feeder)
  input  logic [7:0]  rx_byte,   // Incoming byte (1 per cycle)
  input  logic        rx_valid,  // Byte valid qualifier

  // UART serial TX output pin
  output logic        uart_tx
);

  logic [7:0]  payload_byte;     // Parsed payload byte from eth_rx
  logic        payload_valid;    // Payload byte valid
  logic        payload_ready;    // Backpressure to eth_rx

  // Stage 1: ETH → Parser
  logic [7:0]  rx2p_out;         // Byte to parser
  logic        rx2p_out_valid;   // Byte valid for parser

  // Stage 2: Parser → Logic
  logic        p2l_out_valid;    // Parsed field valid for trading logic
  logic [7:0]  p2l_type_out;     // Parsed message type
  logic [63:0] p2l_order_id_out; // Parsed order ID
  logic [31:0] p2l_price_out;    // Parsed price
  logic [31:0] p2l_volume_out;   // Parsed volume

  // Stage 3: Logic → TX
  logic        l2t_out_valid;    // Valid TX word to UART
  logic [7:0]  l2t_type_out;     // Message type to TX
  logic [31:0] l2t_data_out;     // TX payload data

  // Parser direct outputs (pre-stage 2 buffering)
  logic        field_valid;      // Field pulse valid
  logic [7:0]  msg_type;         // Message type code
  logic [63:0] order_id;         // Order ID
  logic [31:0] price;            // Price
  logic [31:0] volume;           // Volume

  // Trading logic & UART wires
  logic        decision_valid;   // Valid decision pulse from logic
  logic [7:0]  decision_type;    // Decision type code
  logic [31:0] decision_data;    // Decision data (price/ID/etc.)

  logic        logic_ready;      // Backpressure from logic to parser
  logic        uart_ready;       // UART ready to accept word
  logic        uart_busy;        // UART busy transmitting
  wire         uart_ready_masked = uart_ready; // No external stall in FPGA

  // Internal timestamps (for optional on-chip debugging / ILA correlation)
  logic [31:0] cycle_cnt;        // Free-running cycle counter
  logic        parser_msg_start; // Pulse marking start of new parsed message
  logic [31:0] t_ingress;        // Timestamp at ETH ingress
  logic [31:0] t_parser;         // Timestamp at parser stage
  logic [31:0] t_parser_event;   // Timestamp at parser event (msg_start)
  logic [31:0] t_logic;          // Timestamp at trading logic
  logic [31:0] t_decision;       // Timestamp at decision output

  always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) cycle_cnt <= 32'd0;
    else        cycle_cnt <= cycle_cnt + 1;
  end

  eth_rx u_rx (
    .clk           (clk),
    .rst_n         (rst_n),
    .rx_byte       (rx_byte),
    .rx_valid      (rx_valid),

    .payload_byte  (payload_byte),
    .payload_valid (payload_valid),
    .payload_ready (payload_ready),

    .crc_ok        (),
    .crc_valid     (),
    .dbg_crc_calc        (),
    .dbg_crc_recv        (),
    .dbg_payload_len     (),
    .dbg_total_payload   (),
    .dbg_payload_cnt_last()
  );

  pipeline_regs u_prg (
    .clk       (clk),
    .rst_n     (rst_n),

    // Stage 1: ETH → Parser
    .rx2p_in         (payload_byte),
    .rx2p_valid      (payload_valid),
    .rx2p_ready      (payload_ready),
    .rx2p_out        (rx2p_out),
    .rx2p_out_valid  (rx2p_out_valid),
    .rx2p_out_ready  (1'b1), // parser always ready in this design

    // Stage 2: Parser → Logic
    .p2l_type        (msg_type),
    .p2l_valid       (field_valid),
    .p2l_order_id    (order_id),
    .p2l_price       (price),
    .p2l_volume      (volume),
    .p2l_ready       (), // unused
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
    .l2t_ready       (), // unused
    .l2t_type_out    (l2t_type_out),
    .l2t_data_out    (l2t_data_out),
    .l2t_out_valid   (l2t_out_valid),
    .l2t_out_ready   (uart_ready_masked),

    // Timestamp tagging
    .cycle_cnt       (cycle_cnt),
    .t_ingress       (t_ingress),
    .t_parser        (t_parser),
    .t_parser_event  (t_parser_event),
    .t_logic         (t_logic),
    .t_decision      (t_decision),
    .msg_start       (parser_msg_start)
  );

  parser u_pr (
    .clk        (clk),
    .rst_n      (rst_n),
    .in_byte    (rx2p_out),
    .in_valid   (rx2p_out_valid),
    .in_ready   (), // always ready in this design
    .msg_type   (msg_type),
    .field_valid(field_valid),
    .order_id   (order_id),
    .price      (price),
    .volume     (volume),
    .msg_start  (parser_msg_start)
  );

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
    .d_order_id     (), // unused
    .d_price        (decision_data),
    .d_volume       (), // unused
    .in_ready       (logic_ready)
  );

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

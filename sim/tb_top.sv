`timescale 1ns/1ps

// Top-level testbench harness
// - Acts as a Verilator sim top with all I/O routed to the C++ driver
// - Provides hooks for pipeline stage observation, CRC debug, and stall metrics

module tb_top (

  // Inputs driven by C++ harness
  input  logic        clk,         // System clock
  input  logic        rst_n,       // Active-low reset
  input  logic [7:0]  rx_byte,     // Incoming byte from Ethernet PHY
  input  logic        rx_valid,    // Byte valid strobe
  input  logic        sink_allow,  // Controls UART acceptance (0 = stall sink)

  // Outputs observed by C++ harness
  output logic        uart_tx,        // UART TX line
  output logic        payload_valid,  // ETH RX → Parser byte valid
  output logic [7:0]  payload_byte,   // ETH RX → Parser byte data
  output logic        field_valid,    // Parser emits a valid ITCH field
  output logic [7:0]  msg_type,       // Parsed ITCH message type
  output logic        decision_valid, // Trading logic emits decision
  output logic [63:0] order_id,       // Parsed order ID
  output logic [31:0] price,          // Parsed price
  output logic [31:0] volume,         // Parsed volume
  output logic        eth_crc_ok,     // Ethernet CRC pass
  output logic        eth_crc_valid,  // Ethernet CRC result valid

  // Timestamp markers (cycle counts) for latency profiling
  output logic [31:0] t_ingress,
  output logic [31:0] t_parser,
  output logic [31:0] t_parser_event,
  output logic [31:0] t_logic,
  output logic [31:0] t_decision,
  output logic [31:0] cycle_cnt,

  // CRC debug taps
  output logic [31:0] dbg_crc_calc,
  output logic [31:0] dbg_crc_recv,
  output logic [15:0] dbg_payload_len,
  output logic [15:0] dbg_total_payload,
  output logic [15:0] dbg_payload_cnt_last,

  // Registered parser outputs (for clean C++ logging)
  output logic        parsed_valid_reg,
  output logic [7:0]  parsed_type_reg,
  output logic [31:0] parsed_price_reg,
  output logic [31:0] parsed_volume_reg,

  // Logic to TX observability & stall metrics
  output logic        tx_word_valid,
  output logic [31:0] tx_word_data,
  output logic        l2t_stall,         // TX stage has data but sink not ready
  output logic [31:0] l2t_stall_cycles   // Cumulative stall cycles
);

  // Internal back-pressure signal

  logic payload_ready;        // ETH RX ready
  logic parser_ready;         // Parser ready
  logic logic_ready;          // Trading logic ready
  logic uart_ready;           // UART TX ready
  logic uart_ready_masked;    // UART ready gated by sink_allow

  logic dummy_p2l_ready;
  logic unused_parser_ready;
  logic [31:0] t_ingress_unused;

  // Intermediate wires between stages
  wire [7:0]  decision_type;
  wire [31:0] decision_data;
  wire        uart_busy;
  wire        parser_msg_start;

  // Global cycle counter (used for latency stamps)

  always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) cycle_cnt <= 0;
    else        cycle_cnt <= cycle_cnt + 1;
  end

  // Pipeline stage handoff wires
  // Ethernet RX to Parser
  logic [7:0]  rx2p_out;
  logic        rx2p_out_valid;
  logic        rx2p_out_ready;

  // Parser to Trading Logic
  logic [7:0]  p2l_type_out;
  logic [63:0] p2l_order_id_out;
  logic [31:0] p2l_price_out;
  logic [31:0] p2l_volume_out;
  logic        p2l_out_valid;

  // Trading Logic to UART
  logic [7:0]  l2t_type_out;
  logic [31:0] l2t_data_out;
  logic        l2t_out_valid;

  // Pipeline register block (timestamps + ready/valid bridges)
  pipeline_regs u_prg (
    .clk             (clk),
    .rst_n           (rst_n),

    // Ethernet RX to Parser
    .rx2p_in         (payload_byte),
    .rx2p_valid      (payload_valid),
    .rx2p_ready      (payload_ready),
    .rx2p_out        (rx2p_out),
    .rx2p_out_valid  (rx2p_out_valid),
    .rx2p_out_ready  (1'b1),

    // Parser to Trading Logic
    .p2l_type        (msg_type),
    .p2l_valid       (field_valid),
    .p2l_order_id    (order_id),
    .p2l_price       (price),
    .p2l_volume      (volume),
    .p2l_ready       (),
    .p2l_type_out    (p2l_type_out),
    .p2l_order_id_out(p2l_order_id_out),
    .p2l_price_out   (p2l_price_out),
    .p2l_volume_out  (p2l_volume_out),
    .p2l_out_valid   (p2l_out_valid),
    .p2l_out_ready   (logic_ready),

    // Trading Logic to UART
    .l2t_type        (decision_type),
    .l2t_valid       (decision_valid),
    .l2t_data        (decision_data),
    .l2t_ready       (),
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

  // Register parser outputs for clean external logging
  assign parsed_valid_reg  = p2l_out_valid;
  assign parsed_type_reg   = p2l_type_out;
  assign parsed_price_reg  = p2l_price_out;
  assign parsed_volume_reg = p2l_volume_out;

  // Stall + TX word tracking
  assign uart_ready_masked = uart_ready & sink_allow;
  assign l2t_stall = l2t_out_valid & ~uart_ready_masked;
  assign tx_word_valid = l2t_out_valid & uart_ready_masked;
  assign tx_word_data  = l2t_data_out;

  always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) l2t_stall_cycles <= 32'd0;
    else if (l2t_stall) l2t_stall_cycles <= l2t_stall_cycles + 1;
  end

  // Stage 1: Ethernet RX (MAC + CRC)

  eth_rx u_eth (
    .clk           (clk),
    .rst_n         (rst_n),
    .rx_byte       (rx_byte),
    .rx_valid      (rx_valid),
    .payload_byte  (payload_byte),
    .payload_valid (payload_valid),
    .payload_ready (payload_ready),
    .crc_ok        (eth_crc_ok),
    .crc_valid     (eth_crc_valid),

    // Debug taps
    .dbg_crc_calc        (dbg_crc_calc),
    .dbg_crc_recv        (dbg_crc_recv),
    .dbg_payload_len     (dbg_payload_len),
    .dbg_total_payload   (dbg_total_payload),
    .dbg_payload_cnt_last(dbg_payload_cnt_last)
  );

  // Stage 2: ITCH Parser
  parser u_pr (
    .clk       (clk),
    .rst_n     (rst_n),
    .in_byte   (rx2p_out),
    .in_valid  (rx2p_out_valid),
    .in_ready  (),
    .msg_type  (msg_type),
    .field_valid(field_valid),
    .order_id  (order_id),
    .price     (price),
    .volume    (volume),
    .msg_start (parser_msg_start)  
  );

  // Stage 3: Trading Logic
  trading_logic u_tl (
    .clk           (clk),
    .rst_n         (rst_n),
    .field_valid   (p2l_out_valid),
    .msg_type      (p2l_type_out),
    .order_id      (p2l_order_id_out),
    .price         (p2l_price_out),
    .volume        (p2l_volume_out),
    .decision_valid(decision_valid),
    .decision_type (decision_type),
    .d_order_id    (),
    .d_price       (decision_data),
    .d_volume      (),
    .in_ready      (logic_ready)
  );

  // Stage 4: UART TX
  uart_tx u_ut (
    .clk       (clk),
    .rst_n     (rst_n),
    .data_in   (l2t_data_out),
    .data_valid(l2t_out_valid),
    .ready     (uart_ready),
    .tx_line   (uart_tx),
    .busy      (uart_busy)
  );

endmodule

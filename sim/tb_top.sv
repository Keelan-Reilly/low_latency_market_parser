`timescale 1ns/1ps

module tb_top (
  // Driven by C++ harness
  input  logic        clk,
  input  logic        rst_n,
  input  logic [7:0]  rx_byte,
  input  logic        rx_valid,
  input  logic        sink_allow,  // 1=allow UART accept, 0=stall

  // Observed by C++ harness
  output logic        uart_tx,
  output logic        payload_valid,
  output logic [7:0]  payload_byte,
  output logic        field_valid,
  output logic [7:0]  msg_type,
  output logic        decision_valid,
  output logic [63:0] order_id,
  output logic [31:0] price,
  output logic [31:0] volume,
  output logic        eth_crc_ok, // New
  output logic        eth_crc_valid, // New
  // Timestamp outputs
  output logic [31:0] t_ingress,
  output logic [31:0] t_parser,   // New
  output logic [31:0] t_parser_event, // New
  output logic [31:0] t_logic,    // New
  output logic [31:0] t_decision,
  output logic [31:0] cycle_cnt,

  output logic [31:0] dbg_crc_calc,  //debug
  output logic [31:0] dbg_crc_recv,
  output logic [15:0] dbg_payload_len,
  output logic [15:0] dbg_total_payload,
  output logic [15:0] dbg_payload_cnt_last,

  // NEW: registered parser outputs (for C++ logging)
  output logic        parsed_valid_reg,
  output logic [7:0]  parsed_type_reg,
  output logic [31:0] parsed_price_reg,
  output logic [31:0] parsed_volume_reg,
  // Add these outputs in the port list
  output logic        tx_word_valid,
  output logic [31:0] tx_word_data,
  output logic        l2t_stall,          // NEW: stage-3 has data but sink not ready
  output logic [31:0] l2t_stall_cycles     // NEW: total stall cycles seen at stage-3
);

  

  // Back-pressure (always ready)
  logic payload_ready;
  logic parser_ready;
  logic logic_ready;
  logic uart_ready;
  logic uart_ready_masked; 

  logic dummy_p2l_ready;
  logic unused_parser_ready; // parser's output
  logic [31:0] t_ingress_unused;


  // Intermediate wires
  wire [7:0]  decision_type;
  wire [31:0] decision_data;
  wire        uart_busy;
  wire        parser_msg_start;

  // Cycle counter for timestamps

  always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) cycle_cnt <= 0;
    else        cycle_cnt <= cycle_cnt + 1;
  end

  // ----------------------------------------------------------------
  // 1) ETH → PARSER pipeline stage
  logic [7:0]  rx2p_out;
  logic        rx2p_out_valid;
  logic        rx2p_out_ready;

  // 2) PARSER → LOGIC pipeline stage

  logic [7:0]  p2l_type_out;
  logic [63:0] p2l_order_id_out;
  logic [31:0] p2l_price_out;
  logic [31:0] p2l_volume_out;
  logic        p2l_out_valid;


  // 3) LOGIC → UART pipeline stage
  logic [7:0]  l2t_type_out;
  logic [31:0] l2t_data_out;
  logic        l2t_out_valid;

  // ----------------------------------------------------------------
  // 4) Instantiate the pipeline_regs block
  pipeline_regs u_prg (
    .clk             (clk),
    .rst_n           (rst_n),

    // ETH → Parser
    .rx2p_in         (payload_byte),
    .rx2p_valid      (payload_valid),
    .rx2p_ready      (payload_ready),
    .rx2p_out        (rx2p_out),
    .rx2p_out_valid  (rx2p_out_valid),
    .rx2p_out_ready  (1'b1),

    // Parser → Logic
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

    // Logic → TX
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
    .t_parser_event  (t_parser_event), // New
    .t_logic         (t_logic),
    .t_decision      (t_decision),
    .msg_start       (parser_msg_start)
  );

  assign parsed_valid_reg  = p2l_out_valid;
  assign parsed_type_reg   = p2l_type_out;
  assign parsed_price_reg  = p2l_price_out;
  assign parsed_volume_reg = p2l_volume_out;

  assign uart_ready_masked = uart_ready & sink_allow;
  assign l2t_stall = l2t_out_valid & ~uart_ready_masked;
  assign tx_word_valid = l2t_out_valid & uart_ready_masked;
  assign tx_word_data  = l2t_data_out;

  
  always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) l2t_stall_cycles <= 32'd0;
    else if (l2t_stall) l2t_stall_cycles <= l2t_stall_cycles + 1;
  end

  // ----------------------------------------------------------------
  // 5) Instantiate each stage, now wired through pipeline_regs

  // Ethernet RX
  eth_rx u_eth (
    .clk           (clk),
    .rst_n         (rst_n),
    .rx_byte       (rx_byte),
    .rx_valid      (rx_valid),
    .payload_byte  (payload_byte),
    .payload_valid (payload_valid),
    .payload_ready (payload_ready),
    .crc_ok        (eth_crc_ok), // New
    .crc_valid     (eth_crc_valid), // New

    // debug
    .dbg_crc_calc        (dbg_crc_calc),
    .dbg_crc_recv        (dbg_crc_recv),
    .dbg_payload_len     (dbg_payload_len),
    .dbg_total_payload   (dbg_total_payload),
    .dbg_payload_cnt_last(dbg_payload_cnt_last)
  );

  // Parser gets its inputs from the first pipeline stage
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

  // Trading logic gets its inputs from the second pipeline stage
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
    .in_ready      (logic_ready)           // To pipeline_regs
  );

  // UART TX gets its inputs from the third pipeline stage
  uart_tx u_ut (
    .clk       (clk),
    .rst_n     (rst_n),
    .data_in   (l2t_data_out),
    .data_valid(l2t_out_valid),
    .ready(uart_ready),              // To pipeline_regs
    .tx_line   (uart_tx),
    .busy      (uart_busy)
  );

endmodule
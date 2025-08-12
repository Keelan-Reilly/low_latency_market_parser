`timescale 1ns/1ps

module pipeline_regs (
    input  logic        clk,
    input  logic        rst_n,

    // RX → Parser stage
    input  logic [7:0]  rx2p_in,
    input  logic        rx2p_valid,
    input  logic        rx2p_out_ready,
    output logic        rx2p_ready,
    output logic [7:0]  rx2p_out,
    output logic        rx2p_out_valid,

    // Parser → Logic stage
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


    // Logic → TX stage
    input  logic [7:0]  l2t_type,
    input  logic        l2t_valid,
    input  logic [31:0] l2t_data,
    output logic        l2t_ready,
    output logic [7:0]  l2t_type_out,
    output logic [31:0] l2t_data_out,
    output logic        l2t_out_valid,
    input  logic        l2t_out_ready,

    // Timestamp tagging
    input  logic [31:0] cycle_cnt,
    output logic [31:0] t_ingress,
    output logic [31:0] t_decision,
    output logic [31:0] t_parser,    // Additional timestamp point
    output logic [31:0] t_logic      // Additional timestamp point
);

    // Stage 1 registers: RX → Parser
    logic [7:0]  rx2p_data;
    logic        rx2p_data_valid;
    logic [31:0] rx2p_timestamp; // Timestamp for ingress time

    assign rx2p_ready = !rx2p_data_valid || rx2p_out_ready;

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            rx2p_data_valid <= 0;
            t_ingress <=0;
        end else begin
            if (rx2p_ready && rx2p_valid) begin
                rx2p_data <= rx2p_in;

                if (!rx2p_data_valid) begin
                    rx2p_timestamp <= cycle_cnt;
                    t_ingress      <= cycle_cnt;
                end
                rx2p_data_valid <= 1'b1;
            end else if (rx2p_out_ready) begin
                rx2p_data_valid <= 1'b0;
            end
        end
    end

    assign rx2p_out        = rx2p_data;
    assign rx2p_out_valid  = rx2p_data_valid;

    // Stage 2 registers: Parser → Logic
    logic [7:0]  p2l_type_reg;
    logic [63:0] p2l_order_id_reg;
    logic [31:0] p2l_price_reg;
    logic [31:0] p2l_volume_reg;
    logic        p2l_data_valid;
    logic [31:0] p2l_timestamp; // Timestamp for parser processing

    assign p2l_ready = !p2l_data_valid || p2l_out_ready;

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            p2l_data_valid <= 0;
            t_parser <= 0;
        end else begin
            if (p2l_ready && p2l_valid) begin
                p2l_type_reg      <= p2l_type;
                p2l_order_id_reg  <= p2l_order_id;
                p2l_price_reg     <= p2l_price;
                p2l_volume_reg    <= p2l_volume;
                p2l_data_valid     <= 1'b1;
                p2l_timestamp <= cycle_cnt;  // Capture parser exit time
                t_parser <= cycle_cnt;        // Output parser completion time
            end else if (p2l_out_ready) begin
                p2l_data_valid <= 1'b0;
            end
        end
    end

    assign p2l_type_out       = p2l_type_reg;
    assign p2l_order_id_out   = p2l_order_id_reg;
    assign p2l_price_out      = p2l_price_reg;
    assign p2l_volume_out     = p2l_volume_reg;
    assign p2l_out_valid      = p2l_data_valid;

    // Stage 3 registers: Logic → TX
    logic [7:0]  l2t_type_reg;
    logic [31:0] l2t_data_reg;
    logic        l2t_data_valid;

    assign l2t_ready = !l2t_data_valid || l2t_out_ready;

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            l2t_data_valid <= 1'b0;
            t_logic   <= '0;
            t_decision<= '0;
        end else begin
            // consume when UART accepts it
            if (l2t_out_ready && l2t_data_valid) begin
            l2t_data_valid <= 1'b0;
            end

            // capture a new decision when buffer is free (or just consumed)
            if ((!l2t_data_valid || l2t_out_ready) && l2t_valid) begin
            l2t_type_reg   <= l2t_type;
            l2t_data_reg   <= l2t_data;
            l2t_data_valid <= 1'b1;
            t_logic        <= cycle_cnt;
            t_decision     <= cycle_cnt;
            end
        end
    end

    assign l2t_type_out     = l2t_type_reg;
    assign l2t_data_out     = l2t_data_reg;
    assign l2t_out_valid    = l2t_data_valid;

endmodule
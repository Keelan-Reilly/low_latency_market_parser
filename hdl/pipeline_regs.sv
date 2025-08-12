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
    // New: start-of-message pulse from parser (aligns ingress to this message)
    input  logic        msg_start,

    // Aligned timestamps for the SAME message that produced l2t_* outputs
    output logic [31:0] t_ingress,
    output logic [31:0] t_decision,
    output logic [31:0] t_parser,
    output logic [31:0] t_logic,
    output logic [31:0] t_parser_event
);

    // ------------------------------------------------------------
    // Stage 1: RX → Parser
    // ------------------------------------------------------------
    logic [7:0] rx2p_data;
    logic       rx2p_data_valid;

    assign rx2p_ready = !rx2p_data_valid || rx2p_out_ready;

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            rx2p_data_valid <= 1'b0;
            rx2p_data       <= '0;
        end else begin
            if (rx2p_ready && rx2p_valid) begin
                rx2p_data       <= rx2p_in;
                rx2p_data_valid <= 1'b1;
            end else if (rx2p_out_ready) begin
                rx2p_data_valid <= 1'b0;
            end
        end
    end

    assign rx2p_out       = rx2p_data;
    assign rx2p_out_valid = rx2p_data_valid;

    // ------------------------------------------------------------
    // Stage 2: Parser → Logic
    // Carry ingress timestamp of the CURRENT message alongside
    // ------------------------------------------------------------
    logic [7:0]  p2l_type_reg;
    logic [63:0] p2l_order_id_reg;
    logic [31:0] p2l_price_reg;
    logic [31:0] p2l_volume_reg;
    logic        p2l_data_valid;

    // per-message timestamps
    logic [31:0] ingress_last;  // updated on msg_start
    logic [31:0] ingress_s2;    // latched with this message
    logic [31:0] p2l_timestamp; // parser exit time for this message

    // Update the "last seen" ingress time on start-of-message pulse
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            ingress_last <= '0;
        end else if (msg_start) begin
            ingress_last <= cycle_cnt;
        end
    end

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
                p2l_type_reg     <= p2l_type;
                p2l_order_id_reg <= p2l_order_id;
                p2l_price_reg    <= p2l_price;
                p2l_volume_reg   <= p2l_volume;
                p2l_data_valid   <= 1'b1;

                // timestamps aligned to THIS message
                p2l_timestamp    <= cycle_cnt;   // parser completion for this message
                ingress_s2       <= ingress_last; // ingress captured at msg_start
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

    // ------------------------------------------------------------
    // Stage 3: Logic → TX
    // Freeze aligned timestamps at decision accept
    // ------------------------------------------------------------
    logic [7:0]  l2t_type_reg;
    logic [31:0] l2t_data_reg;
    logic        l2t_data_valid;

    // Captured timestamps that correspond to the SAME decision/word
    logic [31:0] t_ingress_cap, t_parser_cap, t_logic_cap, t_decision_cap;

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
            // consume when downstream accepts
            if (l2t_out_ready && l2t_data_valid)
                l2t_data_valid <= 1'b0;

            // accept new decision when buffer free (or just consumed)
            if ((!l2t_data_valid || l2t_out_ready) && l2t_valid) begin
                l2t_type_reg   <= l2t_type;
                l2t_data_reg   <= l2t_data;
                l2t_data_valid <= 1'b1;

                // freeze aligned timestamps for THIS decision
                t_logic_cap    <= cycle_cnt;
                t_decision_cap <= cycle_cnt;
                t_parser_cap   <= p2l_timestamp;
                t_ingress_cap  <= ingress_s2;
            end
        end
    end

    assign l2t_type_out  = l2t_type_reg;
    assign l2t_data_out  = l2t_data_reg;
    assign l2t_out_valid = l2t_data_valid;

    // ------------------------------------------------------------
    // Timestamp outputs (registered, aligned)
    // ------------------------------------------------------------
    assign t_ingress  = t_ingress_cap;
    assign t_parser   = t_parser_cap;
    assign t_logic    = t_logic_cap;
    assign t_decision = t_decision_cap;
    assign t_parser_event = p2l_timestamp;

endmodule

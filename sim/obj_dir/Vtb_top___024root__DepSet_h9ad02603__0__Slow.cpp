// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_top.h for the primary calling header

#include "Vtb_top__pch.h"
#include "Vtb_top___024root.h"

VL_ATTR_COLD void Vtb_top___024root___eval_static(Vtb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___eval_static\n"); );
}

VL_ATTR_COLD void Vtb_top___024root___eval_initial(Vtb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___eval_initial\n"); );
    // Body
    vlSelf->__Vtrigprevexpr___TOP__clk__0 = vlSelf->clk;
    vlSelf->__Vtrigprevexpr___TOP__rst_n__0 = vlSelf->rst_n;
}

VL_ATTR_COLD void Vtb_top___024root___eval_final(Vtb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___eval_final\n"); );
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_top___024root___dump_triggers__stl(Vtb_top___024root* vlSelf);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vtb_top___024root___eval_phase__stl(Vtb_top___024root* vlSelf);

VL_ATTR_COLD void Vtb_top___024root___eval_settle(Vtb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___eval_settle\n"); );
    // Init
    IData/*31:0*/ __VstlIterCount;
    CData/*0:0*/ __VstlContinue;
    // Body
    __VstlIterCount = 0U;
    vlSelf->__VstlFirstIteration = 1U;
    __VstlContinue = 1U;
    while (__VstlContinue) {
        if (VL_UNLIKELY((0x64U < __VstlIterCount))) {
#ifdef VL_DEBUG
            Vtb_top___024root___dump_triggers__stl(vlSelf);
#endif
            VL_FATAL_MT("tb_top.sv", 3, "", "Settle region did not converge.");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
        __VstlContinue = 0U;
        if (Vtb_top___024root___eval_phase__stl(vlSelf)) {
            __VstlContinue = 1U;
        }
        vlSelf->__VstlFirstIteration = 0U;
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_top___024root___dump_triggers__stl(Vtb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VstlTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelf->__VstlTriggered.word(0U))) {
        VL_DBG_MSGF("         'stl' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vtb_top___024root___stl_sequent__TOP__0(Vtb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___stl_sequent__TOP__0\n"); );
    // Body
    vlSelf->t_ingress = vlSelf->tb_top__DOT__u_prg__DOT__t_ingress_cap;
    vlSelf->t_parser = vlSelf->tb_top__DOT__u_prg__DOT__t_parser_cap;
    vlSelf->t_parser_event = vlSelf->tb_top__DOT__u_prg__DOT__p2l_timestamp;
    vlSelf->t_logic = vlSelf->tb_top__DOT__u_prg__DOT__t_logic_cap;
    vlSelf->t_decision = vlSelf->tb_top__DOT__u_prg__DOT__t_decision_cap;
    vlSelf->parsed_valid_reg = vlSelf->tb_top__DOT__u_prg__DOT__p2l_data_valid;
    vlSelf->parsed_type_reg = vlSelf->tb_top__DOT__u_prg__DOT__p2l_type_reg;
    vlSelf->parsed_price_reg = vlSelf->tb_top__DOT__u_prg__DOT__p2l_price_reg;
    vlSelf->parsed_volume_reg = vlSelf->tb_top__DOT__u_prg__DOT__p2l_volume_reg;
    vlSelf->tx_word_data = vlSelf->tb_top__DOT__u_prg__DOT__l2t_data_reg;
    vlSelf->tx_word_valid = ((IData)(vlSelf->tb_top__DOT__u_prg__DOT__l2t_data_valid) 
                             & (0U == (IData)(vlSelf->tb_top__DOT__u_ut__DOT__st)));
    vlSelf->tb_top__DOT__u_ut__DOT__accept = ((0U == (IData)(vlSelf->tb_top__DOT__u_ut__DOT__st)) 
                                              & (IData)(vlSelf->tb_top__DOT__u_prg__DOT__l2t_data_valid));
}

VL_ATTR_COLD void Vtb_top___024root___eval_stl(Vtb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___eval_stl\n"); );
    // Body
    if ((1ULL & vlSelf->__VstlTriggered.word(0U))) {
        Vtb_top___024root___stl_sequent__TOP__0(vlSelf);
    }
}

VL_ATTR_COLD void Vtb_top___024root___eval_triggers__stl(Vtb_top___024root* vlSelf);

VL_ATTR_COLD bool Vtb_top___024root___eval_phase__stl(Vtb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___eval_phase__stl\n"); );
    // Init
    CData/*0:0*/ __VstlExecute;
    // Body
    Vtb_top___024root___eval_triggers__stl(vlSelf);
    __VstlExecute = vlSelf->__VstlTriggered.any();
    if (__VstlExecute) {
        Vtb_top___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_top___024root___dump_triggers__act(Vtb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VactTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelf->__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 0 is active: @(posedge clk or negedge rst_n)\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_top___024root___dump_triggers__nba(Vtb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___dump_triggers__nba\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VnbaTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelf->__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 0 is active: @(posedge clk or negedge rst_n)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vtb_top___024root___ctor_var_reset(Vtb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___ctor_var_reset\n"); );
    // Body
    vlSelf->clk = VL_RAND_RESET_I(1);
    vlSelf->rst_n = VL_RAND_RESET_I(1);
    vlSelf->rx_byte = VL_RAND_RESET_I(8);
    vlSelf->rx_valid = VL_RAND_RESET_I(1);
    vlSelf->uart_tx = VL_RAND_RESET_I(1);
    vlSelf->payload_valid = VL_RAND_RESET_I(1);
    vlSelf->payload_byte = VL_RAND_RESET_I(8);
    vlSelf->field_valid = VL_RAND_RESET_I(1);
    vlSelf->msg_type = VL_RAND_RESET_I(8);
    vlSelf->decision_valid = VL_RAND_RESET_I(1);
    vlSelf->order_id = VL_RAND_RESET_Q(64);
    vlSelf->price = VL_RAND_RESET_I(32);
    vlSelf->volume = VL_RAND_RESET_I(32);
    vlSelf->eth_crc_ok = VL_RAND_RESET_I(1);
    vlSelf->eth_crc_valid = VL_RAND_RESET_I(1);
    vlSelf->t_ingress = VL_RAND_RESET_I(32);
    vlSelf->t_parser = VL_RAND_RESET_I(32);
    vlSelf->t_parser_event = VL_RAND_RESET_I(32);
    vlSelf->t_logic = VL_RAND_RESET_I(32);
    vlSelf->t_decision = VL_RAND_RESET_I(32);
    vlSelf->cycle_cnt = VL_RAND_RESET_I(32);
    vlSelf->dbg_crc_calc = VL_RAND_RESET_I(32);
    vlSelf->dbg_crc_recv = VL_RAND_RESET_I(32);
    vlSelf->dbg_payload_len = VL_RAND_RESET_I(16);
    vlSelf->dbg_total_payload = VL_RAND_RESET_I(16);
    vlSelf->dbg_payload_cnt_last = VL_RAND_RESET_I(16);
    vlSelf->parsed_valid_reg = VL_RAND_RESET_I(1);
    vlSelf->parsed_type_reg = VL_RAND_RESET_I(8);
    vlSelf->parsed_price_reg = VL_RAND_RESET_I(32);
    vlSelf->parsed_volume_reg = VL_RAND_RESET_I(32);
    vlSelf->tx_word_valid = VL_RAND_RESET_I(1);
    vlSelf->tx_word_data = VL_RAND_RESET_I(32);
    vlSelf->tb_top__DOT__parser_ready = VL_RAND_RESET_I(1);
    vlSelf->tb_top__DOT__t_ingress_unused = VL_RAND_RESET_I(32);
    vlSelf->tb_top__DOT__decision_type = VL_RAND_RESET_I(8);
    vlSelf->tb_top__DOT__decision_data = VL_RAND_RESET_I(32);
    vlSelf->tb_top__DOT__parser_msg_start = VL_RAND_RESET_I(1);
    vlSelf->tb_top__DOT__rx2p_out_ready = VL_RAND_RESET_I(1);
    vlSelf->tb_top__DOT__p2l_ready = VL_RAND_RESET_I(1);
    vlSelf->tb_top__DOT__u_prg__DOT__rx2p_data = VL_RAND_RESET_I(8);
    vlSelf->tb_top__DOT__u_prg__DOT__rx2p_data_valid = VL_RAND_RESET_I(1);
    vlSelf->tb_top__DOT__u_prg__DOT__p2l_type_reg = VL_RAND_RESET_I(8);
    vlSelf->tb_top__DOT__u_prg__DOT__p2l_order_id_reg = VL_RAND_RESET_Q(64);
    vlSelf->tb_top__DOT__u_prg__DOT__p2l_price_reg = VL_RAND_RESET_I(32);
    vlSelf->tb_top__DOT__u_prg__DOT__p2l_volume_reg = VL_RAND_RESET_I(32);
    vlSelf->tb_top__DOT__u_prg__DOT__p2l_data_valid = VL_RAND_RESET_I(1);
    vlSelf->tb_top__DOT__u_prg__DOT__ingress_last = VL_RAND_RESET_I(32);
    vlSelf->tb_top__DOT__u_prg__DOT__ingress_s2 = VL_RAND_RESET_I(32);
    vlSelf->tb_top__DOT__u_prg__DOT__p2l_timestamp = VL_RAND_RESET_I(32);
    vlSelf->tb_top__DOT__u_prg__DOT__l2t_type_reg = VL_RAND_RESET_I(8);
    vlSelf->tb_top__DOT__u_prg__DOT__l2t_data_reg = VL_RAND_RESET_I(32);
    vlSelf->tb_top__DOT__u_prg__DOT__l2t_data_valid = VL_RAND_RESET_I(1);
    vlSelf->tb_top__DOT__u_prg__DOT__t_ingress_cap = VL_RAND_RESET_I(32);
    vlSelf->tb_top__DOT__u_prg__DOT__t_parser_cap = VL_RAND_RESET_I(32);
    vlSelf->tb_top__DOT__u_prg__DOT__t_logic_cap = VL_RAND_RESET_I(32);
    vlSelf->tb_top__DOT__u_prg__DOT__t_decision_cap = VL_RAND_RESET_I(32);
    vlSelf->tb_top__DOT__u_eth__DOT__state = VL_RAND_RESET_I(3);
    vlSelf->tb_top__DOT__u_eth__DOT__pre_cnt = VL_RAND_RESET_I(3);
    vlSelf->tb_top__DOT__u_eth__DOT__crc_cnt = VL_RAND_RESET_I(4);
    vlSelf->tb_top__DOT__u_eth__DOT__hdr_cnt = VL_RAND_RESET_I(16);
    vlSelf->tb_top__DOT__u_eth__DOT__payload_cnt = VL_RAND_RESET_I(16);
    vlSelf->tb_top__DOT__u_eth__DOT__payload_len = VL_RAND_RESET_I(16);
    vlSelf->tb_top__DOT__u_eth__DOT__dest_mac_shift = VL_RAND_RESET_Q(48);
    vlSelf->tb_top__DOT__u_eth__DOT__mac_match = VL_RAND_RESET_I(1);
    vlSelf->tb_top__DOT__u_eth__DOT__crc_reg = VL_RAND_RESET_I(32);
    vlSelf->tb_top__DOT__u_eth__DOT__crc_recv_shift = VL_RAND_RESET_I(32);
    vlSelf->tb_top__DOT__u_eth__DOT__this_cycle_match = VL_RAND_RESET_I(1);
    vlSelf->tb_top__DOT__u_eth__DOT__next_crc = VL_RAND_RESET_I(32);
    vlSelf->tb_top__DOT__u_eth__DOT__fcs_word = VL_RAND_RESET_I(32);
    vlSelf->tb_top__DOT__u_eth__DOT__total_payload = VL_RAND_RESET_I(16);
    vlSelf->tb_top__DOT__u_eth__DOT__crc_started = VL_RAND_RESET_I(1);
    vlSelf->tb_top__DOT__u_eth__DOT__unnamedblk2__DOT__full_dest = VL_RAND_RESET_Q(48);
    vlSelf->tb_top__DOT__u_eth__DOT__unnamedblk3__DOT__new_fcs = VL_RAND_RESET_I(32);
    vlSelf->tb_top__DOT__u_pr__DOT__state = VL_RAND_RESET_I(2);
    vlSelf->tb_top__DOT__u_pr__DOT__length = VL_RAND_RESET_I(16);
    vlSelf->tb_top__DOT__u_pr__DOT__len_hi = VL_RAND_RESET_I(8);
    vlSelf->tb_top__DOT__u_pr__DOT__len_lo = VL_RAND_RESET_I(8);
    vlSelf->tb_top__DOT__u_pr__DOT__type_reg = VL_RAND_RESET_I(8);
    vlSelf->tb_top__DOT__u_pr__DOT__cnt = VL_RAND_RESET_I(16);
    vlSelf->tb_top__DOT__u_pr__DOT__body_left = VL_RAND_RESET_I(16);
    vlSelf->tb_top__DOT__u_tl__DOT__d_order_id = VL_RAND_RESET_Q(64);
    vlSelf->tb_top__DOT__u_tl__DOT__d_volume = VL_RAND_RESET_I(32);
    vlSelf->tb_top__DOT__u_ut__DOT__tick_cnt = VL_RAND_RESET_I(10);
    vlSelf->tb_top__DOT__u_ut__DOT__st = VL_RAND_RESET_I(2);
    vlSelf->tb_top__DOT__u_ut__DOT__word_reg = VL_RAND_RESET_I(32);
    vlSelf->tb_top__DOT__u_ut__DOT__byte_idx = VL_RAND_RESET_I(2);
    vlSelf->tb_top__DOT__u_ut__DOT__bit_idx = VL_RAND_RESET_I(3);
    vlSelf->tb_top__DOT__u_ut__DOT__sh = VL_RAND_RESET_I(8);
    vlSelf->tb_top__DOT__u_ut__DOT__accept = VL_RAND_RESET_I(1);
    vlSelf->__Vtrigprevexpr___TOP__clk__0 = VL_RAND_RESET_I(1);
    vlSelf->__Vtrigprevexpr___TOP__rst_n__0 = VL_RAND_RESET_I(1);
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->__Vm_traceActivity[__Vi0] = 0;
    }
}

// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_top.h for the primary calling header

#include "Vtb_top__pch.h"
#include "Vtb_top___024root.h"

VL_ATTR_COLD void Vtb_top___024root___eval_static(Vtb_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___eval_static\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vtrigprevexpr___TOP__clk__0 = vlSelfRef.clk;
    vlSelfRef.__Vtrigprevexpr___TOP__rst_n__0 = vlSelfRef.rst_n;
}

VL_ATTR_COLD void Vtb_top___024root___eval_initial(Vtb_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___eval_initial\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vtb_top___024root___eval_final(Vtb_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___eval_final\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_top___024root___dump_triggers__stl(Vtb_top___024root* vlSelf);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vtb_top___024root___eval_phase__stl(Vtb_top___024root* vlSelf);

VL_ATTR_COLD void Vtb_top___024root___eval_settle(Vtb_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___eval_settle\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __VstlIterCount;
    CData/*0:0*/ __VstlContinue;
    // Body
    __VstlIterCount = 0U;
    vlSelfRef.__VstlFirstIteration = 1U;
    __VstlContinue = 1U;
    while (__VstlContinue) {
        if (VL_UNLIKELY(((0x64U < __VstlIterCount)))) {
#ifdef VL_DEBUG
            Vtb_top___024root___dump_triggers__stl(vlSelf);
#endif
            VL_FATAL_MT("/Users/keelanreilly/Desktop/low_latency_market_parser/hdl/tb_top.sv", 7, "", "Settle region did not converge.");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
        __VstlContinue = 0U;
        if (Vtb_top___024root___eval_phase__stl(vlSelf)) {
            __VstlContinue = 1U;
        }
        vlSelfRef.__VstlFirstIteration = 0U;
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_top___024root___dump_triggers__stl(Vtb_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___dump_triggers__stl\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VstlTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VstlTriggered.word(0U))) {
        VL_DBG_MSGF("         'stl' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vtb_top___024root___stl_sequent__TOP__0(Vtb_top___024root* vlSelf);
VL_ATTR_COLD void Vtb_top___024root____Vm_traceActivitySetAll(Vtb_top___024root* vlSelf);

VL_ATTR_COLD void Vtb_top___024root___eval_stl(Vtb_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___eval_stl\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VstlTriggered.word(0U))) {
        Vtb_top___024root___stl_sequent__TOP__0(vlSelf);
        Vtb_top___024root____Vm_traceActivitySetAll(vlSelf);
    }
}

VL_ATTR_COLD void Vtb_top___024root___stl_sequent__TOP__0(Vtb_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___stl_sequent__TOP__0\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.parsed_valid_reg = ((IData)(vlSelfRef.field_valid) 
                                  | (IData)(vlSelfRef.tb_top__DOT__u_prg__DOT__s2__DOT__saved_valid));
    vlSelfRef.tb_top__DOT__rx2p_out_valid = ((IData)(vlSelfRef.payload_valid) 
                                             | (IData)(vlSelfRef.tb_top__DOT__u_prg__DOT__s1__DOT__saved_valid));
    vlSelfRef.tb_top__DOT__rx2p_out = ((IData)(vlSelfRef.tb_top__DOT__u_prg__DOT__s1__DOT__saved_valid)
                                        ? (IData)(vlSelfRef.tb_top__DOT__u_prg__DOT__s1__DOT__saved_data)
                                        : (IData)(vlSelfRef.payload_byte));
    vlSelfRef.tb_top__DOT__uart_ready_masked = ((IData)(vlSelfRef.sink_allow) 
                                                & (0U 
                                                   == (IData)(vlSelfRef.tb_top__DOT__u_ut__DOT__st)));
    vlSelfRef.tb_top__DOT__l2t_out_valid = ((IData)(vlSelfRef.decision_valid) 
                                            | (IData)(vlSelfRef.tb_top__DOT__u_prg__DOT__s3__DOT__saved_valid));
    vlSelfRef.tb_top__DOT__u_prg__DOT__p2l_bus_in[0U] 
        = vlSelfRef.cycle_cnt;
    vlSelfRef.tb_top__DOT__u_prg__DOT__p2l_bus_in[1U] 
        = vlSelfRef.tb_top__DOT__u_prg__DOT__ingress_last;
    vlSelfRef.tb_top__DOT__u_prg__DOT__p2l_bus_in[2U] 
        = (IData)((((QData)((IData)(vlSelfRef.price)) 
                    << 0x20U) | (QData)((IData)(vlSelfRef.volume))));
    vlSelfRef.tb_top__DOT__u_prg__DOT__p2l_bus_in[3U] 
        = (IData)(((((QData)((IData)(vlSelfRef.price)) 
                     << 0x20U) | (QData)((IData)(vlSelfRef.volume))) 
                   >> 0x20U));
    vlSelfRef.tb_top__DOT__u_prg__DOT__p2l_bus_in[4U] 
        = (IData)(vlSelfRef.order_id);
    vlSelfRef.tb_top__DOT__u_prg__DOT__p2l_bus_in[5U] 
        = (IData)((vlSelfRef.order_id >> 0x20U));
    vlSelfRef.tb_top__DOT__u_prg__DOT__p2l_bus_in[6U] 
        = (0xffU & (IData)(vlSelfRef.msg_type));
    vlSelfRef.tx_word_valid = ((IData)(vlSelfRef.tb_top__DOT__l2t_out_valid) 
                               & (IData)(vlSelfRef.tb_top__DOT__uart_ready_masked));
    vlSelfRef.l2t_stall = ((~ (IData)(vlSelfRef.tb_top__DOT__uart_ready_masked)) 
                           & (IData)(vlSelfRef.tb_top__DOT__l2t_out_valid));
    vlSelfRef.tb_top__DOT__u_ut__DOT__accept = ((0U 
                                                 == (IData)(vlSelfRef.tb_top__DOT__u_ut__DOT__st)) 
                                                & (IData)(vlSelfRef.tb_top__DOT__l2t_out_valid));
    if (vlSelfRef.tb_top__DOT__u_prg__DOT__s2__DOT__saved_valid) {
        vlSelfRef.tb_top__DOT__u_prg__DOT__p2l_bus_out[0U] 
            = vlSelfRef.tb_top__DOT__u_prg__DOT__s2__DOT__saved_data[0U];
        vlSelfRef.tb_top__DOT__u_prg__DOT__p2l_bus_out[1U] 
            = vlSelfRef.tb_top__DOT__u_prg__DOT__s2__DOT__saved_data[1U];
        vlSelfRef.tb_top__DOT__u_prg__DOT__p2l_bus_out[2U] 
            = vlSelfRef.tb_top__DOT__u_prg__DOT__s2__DOT__saved_data[2U];
        vlSelfRef.tb_top__DOT__u_prg__DOT__p2l_bus_out[3U] 
            = vlSelfRef.tb_top__DOT__u_prg__DOT__s2__DOT__saved_data[3U];
        vlSelfRef.tb_top__DOT__u_prg__DOT__p2l_bus_out[4U] 
            = vlSelfRef.tb_top__DOT__u_prg__DOT__s2__DOT__saved_data[4U];
        vlSelfRef.tb_top__DOT__u_prg__DOT__p2l_bus_out[5U] 
            = vlSelfRef.tb_top__DOT__u_prg__DOT__s2__DOT__saved_data[5U];
        vlSelfRef.tb_top__DOT__u_prg__DOT__p2l_bus_out[6U] 
            = vlSelfRef.tb_top__DOT__u_prg__DOT__s2__DOT__saved_data[6U];
    } else {
        vlSelfRef.tb_top__DOT__u_prg__DOT__p2l_bus_out[0U] 
            = vlSelfRef.tb_top__DOT__u_prg__DOT__p2l_bus_in[0U];
        vlSelfRef.tb_top__DOT__u_prg__DOT__p2l_bus_out[1U] 
            = vlSelfRef.tb_top__DOT__u_prg__DOT__p2l_bus_in[1U];
        vlSelfRef.tb_top__DOT__u_prg__DOT__p2l_bus_out[2U] 
            = vlSelfRef.tb_top__DOT__u_prg__DOT__p2l_bus_in[2U];
        vlSelfRef.tb_top__DOT__u_prg__DOT__p2l_bus_out[3U] 
            = vlSelfRef.tb_top__DOT__u_prg__DOT__p2l_bus_in[3U];
        vlSelfRef.tb_top__DOT__u_prg__DOT__p2l_bus_out[4U] 
            = vlSelfRef.tb_top__DOT__u_prg__DOT__p2l_bus_in[4U];
        vlSelfRef.tb_top__DOT__u_prg__DOT__p2l_bus_out[5U] 
            = vlSelfRef.tb_top__DOT__u_prg__DOT__p2l_bus_in[5U];
        vlSelfRef.tb_top__DOT__u_prg__DOT__p2l_bus_out[6U] 
            = vlSelfRef.tb_top__DOT__u_prg__DOT__p2l_bus_in[6U];
    }
    vlSelfRef.t_parser_event = vlSelfRef.tb_top__DOT__u_prg__DOT__p2l_bus_out[0U];
    vlSelfRef.parsed_type_reg = (0xffU & vlSelfRef.tb_top__DOT__u_prg__DOT__p2l_bus_out[6U]);
    vlSelfRef.parsed_price_reg = vlSelfRef.tb_top__DOT__u_prg__DOT__p2l_bus_out[3U];
    vlSelfRef.parsed_volume_reg = vlSelfRef.tb_top__DOT__u_prg__DOT__p2l_bus_out[2U];
    vlSelfRef.tb_top__DOT__u_prg__DOT__l2t_bus_in[0U] 
        = (IData)((((QData)((IData)(vlSelfRef.cycle_cnt)) 
                    << 0x20U) | (QData)((IData)(vlSelfRef.cycle_cnt))));
    vlSelfRef.tb_top__DOT__u_prg__DOT__l2t_bus_in[1U] 
        = (IData)(((((QData)((IData)(vlSelfRef.cycle_cnt)) 
                     << 0x20U) | (QData)((IData)(vlSelfRef.cycle_cnt))) 
                   >> 0x20U));
    vlSelfRef.tb_top__DOT__u_prg__DOT__l2t_bus_in[2U] 
        = (IData)((((QData)((IData)(vlSelfRef.tb_top__DOT__u_prg__DOT__p2l_bus_out[1U])) 
                    << 0x20U) | (QData)((IData)(vlSelfRef.tb_top__DOT__u_prg__DOT__p2l_bus_out[0U]))));
    vlSelfRef.tb_top__DOT__u_prg__DOT__l2t_bus_in[3U] 
        = (IData)(((((QData)((IData)(vlSelfRef.tb_top__DOT__u_prg__DOT__p2l_bus_out[1U])) 
                     << 0x20U) | (QData)((IData)(vlSelfRef.tb_top__DOT__u_prg__DOT__p2l_bus_out[0U]))) 
                   >> 0x20U));
    vlSelfRef.tb_top__DOT__u_prg__DOT__l2t_bus_in[4U] 
        = vlSelfRef.tb_top__DOT__decision_data;
    vlSelfRef.tb_top__DOT__u_prg__DOT__l2t_bus_in[5U] 
        = (0xffU & (IData)(vlSelfRef.tb_top__DOT__decision_type));
    if (vlSelfRef.tb_top__DOT__u_prg__DOT__s3__DOT__saved_valid) {
        vlSelfRef.tb_top__DOT__u_prg__DOT__l2t_bus_out[0U] 
            = vlSelfRef.tb_top__DOT__u_prg__DOT__s3__DOT__saved_data[0U];
        vlSelfRef.tb_top__DOT__u_prg__DOT__l2t_bus_out[1U] 
            = vlSelfRef.tb_top__DOT__u_prg__DOT__s3__DOT__saved_data[1U];
        vlSelfRef.tb_top__DOT__u_prg__DOT__l2t_bus_out[2U] 
            = vlSelfRef.tb_top__DOT__u_prg__DOT__s3__DOT__saved_data[2U];
        vlSelfRef.tb_top__DOT__u_prg__DOT__l2t_bus_out[3U] 
            = vlSelfRef.tb_top__DOT__u_prg__DOT__s3__DOT__saved_data[3U];
        vlSelfRef.tb_top__DOT__u_prg__DOT__l2t_bus_out[4U] 
            = vlSelfRef.tb_top__DOT__u_prg__DOT__s3__DOT__saved_data[4U];
        vlSelfRef.tb_top__DOT__u_prg__DOT__l2t_bus_out[5U] 
            = vlSelfRef.tb_top__DOT__u_prg__DOT__s3__DOT__saved_data[5U];
    } else {
        vlSelfRef.tb_top__DOT__u_prg__DOT__l2t_bus_out[0U] 
            = vlSelfRef.tb_top__DOT__u_prg__DOT__l2t_bus_in[0U];
        vlSelfRef.tb_top__DOT__u_prg__DOT__l2t_bus_out[1U] 
            = vlSelfRef.tb_top__DOT__u_prg__DOT__l2t_bus_in[1U];
        vlSelfRef.tb_top__DOT__u_prg__DOT__l2t_bus_out[2U] 
            = vlSelfRef.tb_top__DOT__u_prg__DOT__l2t_bus_in[2U];
        vlSelfRef.tb_top__DOT__u_prg__DOT__l2t_bus_out[3U] 
            = vlSelfRef.tb_top__DOT__u_prg__DOT__l2t_bus_in[3U];
        vlSelfRef.tb_top__DOT__u_prg__DOT__l2t_bus_out[4U] 
            = vlSelfRef.tb_top__DOT__u_prg__DOT__l2t_bus_in[4U];
        vlSelfRef.tb_top__DOT__u_prg__DOT__l2t_bus_out[5U] 
            = vlSelfRef.tb_top__DOT__u_prg__DOT__l2t_bus_in[5U];
    }
    vlSelfRef.t_ingress = vlSelfRef.tb_top__DOT__u_prg__DOT__l2t_bus_out[3U];
    vlSelfRef.t_parser = vlSelfRef.tb_top__DOT__u_prg__DOT__l2t_bus_out[2U];
    vlSelfRef.t_logic = vlSelfRef.tb_top__DOT__u_prg__DOT__l2t_bus_out[1U];
    vlSelfRef.t_decision = vlSelfRef.tb_top__DOT__u_prg__DOT__l2t_bus_out[0U];
    vlSelfRef.tx_word_data = vlSelfRef.tb_top__DOT__u_prg__DOT__l2t_bus_out[4U];
}

VL_ATTR_COLD void Vtb_top___024root___eval_triggers__stl(Vtb_top___024root* vlSelf);

VL_ATTR_COLD bool Vtb_top___024root___eval_phase__stl(Vtb_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___eval_phase__stl\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VstlExecute;
    // Body
    Vtb_top___024root___eval_triggers__stl(vlSelf);
    __VstlExecute = vlSelfRef.__VstlTriggered.any();
    if (__VstlExecute) {
        Vtb_top___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_top___024root___dump_triggers__ico(Vtb_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___dump_triggers__ico\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VicoTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VicoTriggered.word(0U))) {
        VL_DBG_MSGF("         'ico' region trigger index 0 is active: Internal 'ico' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_top___024root___dump_triggers__act(Vtb_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___dump_triggers__act\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VactTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 0 is active: @(posedge clk)\n");
    }
    if ((2ULL & vlSelfRef.__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 1 is active: @(negedge rst_n)\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_top___024root___dump_triggers__nba(Vtb_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___dump_triggers__nba\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VnbaTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 0 is active: @(posedge clk)\n");
    }
    if ((2ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 1 is active: @(negedge rst_n)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vtb_top___024root____Vm_traceActivitySetAll(Vtb_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root____Vm_traceActivitySetAll\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vm_traceActivity[0U] = 1U;
    vlSelfRef.__Vm_traceActivity[1U] = 1U;
}

VL_ATTR_COLD void Vtb_top___024root___ctor_var_reset(Vtb_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___ctor_var_reset\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->name());
    vlSelf->clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16707436170211756652ull);
    vlSelf->rst_n = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1638864771569018232ull);
    vlSelf->rx_byte = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 5165233808670255665ull);
    vlSelf->rx_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13133491208690242300ull);
    vlSelf->sink_allow = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9998494698588397817ull);
    vlSelf->uart_tx = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1761512799854230840ull);
    vlSelf->payload_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2176467603763705949ull);
    vlSelf->payload_byte = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 13164836401285759525ull);
    vlSelf->field_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12259774853700995060ull);
    vlSelf->msg_type = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 11446285417486708179ull);
    vlSelf->decision_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8756974317132670490ull);
    vlSelf->order_id = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 299721438818937156ull);
    vlSelf->price = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2643329332563602126ull);
    vlSelf->volume = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7699327401757349171ull);
    vlSelf->eth_crc_ok = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10225951674388990403ull);
    vlSelf->eth_crc_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3608356971777531846ull);
    vlSelf->t_ingress = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7867020519261017246ull);
    vlSelf->t_parser = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 14560516640335043805ull);
    vlSelf->t_parser_event = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11504386448264464238ull);
    vlSelf->t_logic = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1554844325716119321ull);
    vlSelf->t_decision = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4298710004797622715ull);
    vlSelf->cycle_cnt = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10774249576030602819ull);
    vlSelf->dbg_crc_calc = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 8041493395789599572ull);
    vlSelf->dbg_crc_recv = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 5780538106531750777ull);
    vlSelf->dbg_payload_len = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 1737885489205097613ull);
    vlSelf->dbg_total_payload = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 18047124944374900440ull);
    vlSelf->dbg_payload_cnt_last = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 9438866872026947377ull);
    vlSelf->parsed_valid_reg = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11533163178365844335ull);
    vlSelf->parsed_type_reg = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 7149838051805587994ull);
    vlSelf->parsed_price_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6550521586016409668ull);
    vlSelf->parsed_volume_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10071661693047959437ull);
    vlSelf->tx_word_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12436886417055612707ull);
    vlSelf->tx_word_data = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9766596343311898977ull);
    vlSelf->l2t_stall = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7336273295950053220ull);
    vlSelf->l2t_stall_cycles = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11312381516529249147ull);
    vlSelf->tb_top__DOT__parser_ready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10303587105747038956ull);
    vlSelf->tb_top__DOT__uart_ready_masked = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10138046237501403558ull);
    vlSelf->tb_top__DOT__dummy_p2l_ready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2654900408641101392ull);
    vlSelf->tb_top__DOT__unused_parser_ready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8834002038031519666ull);
    vlSelf->tb_top__DOT__t_ingress_unused = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12083129715064087685ull);
    vlSelf->tb_top__DOT__decision_type = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 8875514887218472019ull);
    vlSelf->tb_top__DOT__decision_data = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9942249076898778352ull);
    vlSelf->tb_top__DOT__parser_msg_start = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13029511560481990094ull);
    vlSelf->tb_top__DOT__rx2p_out = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 10710090566259256128ull);
    vlSelf->tb_top__DOT__rx2p_out_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11292896220969202287ull);
    vlSelf->tb_top__DOT__rx2p_out_ready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10079274216306005860ull);
    vlSelf->tb_top__DOT__l2t_out_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14493813353879318001ull);
    vlSelf->tb_top__DOT__u_prg__DOT__ingress_last = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16085363116659617494ull);
    VL_SCOPED_RAND_RESET_W(200, vlSelf->tb_top__DOT__u_prg__DOT__p2l_bus_in, __VscopeHash, 674142595447563362ull);
    VL_SCOPED_RAND_RESET_W(200, vlSelf->tb_top__DOT__u_prg__DOT__p2l_bus_out, __VscopeHash, 4069471370026325263ull);
    VL_SCOPED_RAND_RESET_W(168, vlSelf->tb_top__DOT__u_prg__DOT__l2t_bus_in, __VscopeHash, 8708231060148159920ull);
    VL_SCOPED_RAND_RESET_W(168, vlSelf->tb_top__DOT__u_prg__DOT__l2t_bus_out, __VscopeHash, 15018549982876221637ull);
    vlSelf->tb_top__DOT__u_prg__DOT__s1__DOT__saved_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2092564057210595129ull);
    vlSelf->tb_top__DOT__u_prg__DOT__s1__DOT__saved_data = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 16898522548269603577ull);
    vlSelf->tb_top__DOT__u_prg__DOT__s2__DOT__saved_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17117702994933606472ull);
    VL_SCOPED_RAND_RESET_W(200, vlSelf->tb_top__DOT__u_prg__DOT__s2__DOT__saved_data, __VscopeHash, 5360894943126891350ull);
    vlSelf->tb_top__DOT__u_prg__DOT__s3__DOT__saved_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11676846927424697333ull);
    VL_SCOPED_RAND_RESET_W(168, vlSelf->tb_top__DOT__u_prg__DOT__s3__DOT__saved_data, __VscopeHash, 15458336500202590503ull);
    vlSelf->tb_top__DOT__u_eth__DOT__state = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 15029872069736386114ull);
    vlSelf->tb_top__DOT__u_eth__DOT__pre_cnt = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 9677294354185211448ull);
    vlSelf->tb_top__DOT__u_eth__DOT__crc_cnt = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 3471571338738608581ull);
    vlSelf->tb_top__DOT__u_eth__DOT__hdr_cnt = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 11811636319214650912ull);
    vlSelf->tb_top__DOT__u_eth__DOT__payload_cnt = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 12352227462054457809ull);
    vlSelf->tb_top__DOT__u_eth__DOT__payload_len = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 13022119508406076304ull);
    vlSelf->tb_top__DOT__u_eth__DOT__dest_mac_shift = VL_SCOPED_RAND_RESET_Q(48, __VscopeHash, 213407336598968690ull);
    vlSelf->tb_top__DOT__u_eth__DOT__mac_match = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11046987912423589886ull);
    vlSelf->tb_top__DOT__u_eth__DOT__crc_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3562341431141590154ull);
    vlSelf->tb_top__DOT__u_eth__DOT__crc_recv_shift = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11610044735412980045ull);
    vlSelf->tb_top__DOT__u_eth__DOT__this_cycle_match = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5626602405495148210ull);
    vlSelf->tb_top__DOT__u_eth__DOT__next_crc = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 14928573563319372091ull);
    vlSelf->tb_top__DOT__u_eth__DOT__fcs_word = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 14791033466557293967ull);
    vlSelf->tb_top__DOT__u_eth__DOT__total_payload = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 2556467463832949533ull);
    vlSelf->tb_top__DOT__u_eth__DOT__crc_started = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16407555855979063334ull);
    vlSelf->tb_top__DOT__u_eth__DOT__full_dest = VL_SCOPED_RAND_RESET_Q(48, __VscopeHash, 8332638615536131861ull);
    vlSelf->tb_top__DOT__u_eth__DOT__unnamedblk2__DOT__new_fcs = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12130801243963279632ull);
    vlSelf->tb_top__DOT__u_pr__DOT__state = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 17398361975033380899ull);
    vlSelf->tb_top__DOT__u_pr__DOT__length = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 12712719073720236990ull);
    vlSelf->tb_top__DOT__u_pr__DOT__len_hi = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 14816641791114838859ull);
    vlSelf->tb_top__DOT__u_pr__DOT__len_lo = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 15253744090986000762ull);
    vlSelf->tb_top__DOT__u_pr__DOT__type_reg = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 3465334659838072642ull);
    vlSelf->tb_top__DOT__u_pr__DOT__cnt = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 7211336559187267301ull);
    vlSelf->tb_top__DOT__u_pr__DOT__body_left = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 18203584287647989496ull);
    vlSelf->tb_top__DOT__u_tl__DOT__d_order_id = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 16616912790732735570ull);
    vlSelf->tb_top__DOT__u_tl__DOT__d_volume = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7599899646127362346ull);
    vlSelf->tb_top__DOT__u_ut__DOT__tick_cnt = VL_SCOPED_RAND_RESET_I(12, __VscopeHash, 4913081159965478533ull);
    vlSelf->tb_top__DOT__u_ut__DOT__st = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 1575616375790777837ull);
    vlSelf->tb_top__DOT__u_ut__DOT__word_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1814915368630008814ull);
    vlSelf->tb_top__DOT__u_ut__DOT__byte_idx = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 9136730615934734333ull);
    vlSelf->tb_top__DOT__u_ut__DOT__bit_idx = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 12455796044401177234ull);
    vlSelf->tb_top__DOT__u_ut__DOT__sh = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 1061769760503653749ull);
    vlSelf->tb_top__DOT__u_ut__DOT__accept = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1682057685189876284ull);
    vlSelf->__Vtrigprevexpr___TOP__clk__0 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9526919608049418986ull);
    vlSelf->__Vtrigprevexpr___TOP__rst_n__0 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14803524876191471008ull);
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->__Vm_traceActivity[__Vi0] = 0;
    }
}

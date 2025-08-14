// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_top.h for the primary calling header

#include "Vtb_top__pch.h"
#include "Vtb_top___024root.h"

VL_INLINE_OPT void Vtb_top___024root___ico_sequent__TOP__0(Vtb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___ico_sequent__TOP__0\n"); );
    // Body
    vlSelf->tb_top__DOT__uart_ready_masked = ((IData)(vlSelf->sink_allow) 
                                              & (0U 
                                                 == (IData)(vlSelf->tb_top__DOT__u_ut__DOT__st)));
    vlSelf->tx_word_valid = ((IData)(vlSelf->tb_top__DOT__u_prg__DOT__l2t_data_valid) 
                             & (IData)(vlSelf->tb_top__DOT__uart_ready_masked));
    vlSelf->l2t_stall = ((~ (IData)(vlSelf->tb_top__DOT__uart_ready_masked)) 
                         & (IData)(vlSelf->tb_top__DOT__u_prg__DOT__l2t_data_valid));
}

void Vtb_top___024root___eval_ico(Vtb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___eval_ico\n"); );
    // Body
    if ((1ULL & vlSelf->__VicoTriggered.word(0U))) {
        Vtb_top___024root___ico_sequent__TOP__0(vlSelf);
    }
}

void Vtb_top___024root___eval_triggers__ico(Vtb_top___024root* vlSelf);

bool Vtb_top___024root___eval_phase__ico(Vtb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___eval_phase__ico\n"); );
    // Init
    CData/*0:0*/ __VicoExecute;
    // Body
    Vtb_top___024root___eval_triggers__ico(vlSelf);
    __VicoExecute = vlSelf->__VicoTriggered.any();
    if (__VicoExecute) {
        Vtb_top___024root___eval_ico(vlSelf);
    }
    return (__VicoExecute);
}

void Vtb_top___024root___eval_act(Vtb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___eval_act\n"); );
}

VL_INLINE_OPT void Vtb_top___024root___nba_sequent__TOP__0(Vtb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___nba_sequent__TOP__0\n"); );
    // Init
    IData/*31:0*/ __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__0__Vfuncout;
    __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__0__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__0__crc_in;
    __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__0__crc_in = 0;
    CData/*7:0*/ __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__0__data_byte;
    __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__0__data_byte = 0;
    IData/*31:0*/ __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__0__c;
    __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__0__c = 0;
    IData/*31:0*/ __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__1__Vfuncout;
    __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__1__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__1__crc_in;
    __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__1__crc_in = 0;
    CData/*7:0*/ __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__1__data_byte;
    __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__1__data_byte = 0;
    IData/*31:0*/ __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__1__c;
    __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__1__c = 0;
    IData/*31:0*/ __Vdly__cycle_cnt;
    __Vdly__cycle_cnt = 0;
    CData/*0:0*/ __Vdly__tb_top__DOT__u_prg__DOT__l2t_data_valid;
    __Vdly__tb_top__DOT__u_prg__DOT__l2t_data_valid = 0;
    CData/*2:0*/ __Vdly__tb_top__DOT__u_eth__DOT__state;
    __Vdly__tb_top__DOT__u_eth__DOT__state = 0;
    IData/*31:0*/ __Vdly__tb_top__DOT__u_eth__DOT__crc_recv_shift;
    __Vdly__tb_top__DOT__u_eth__DOT__crc_recv_shift = 0;
    CData/*3:0*/ __Vdly__tb_top__DOT__u_eth__DOT__crc_cnt;
    __Vdly__tb_top__DOT__u_eth__DOT__crc_cnt = 0;
    SData/*15:0*/ __Vdly__tb_top__DOT__u_eth__DOT__payload_len;
    __Vdly__tb_top__DOT__u_eth__DOT__payload_len = 0;
    SData/*15:0*/ __Vdly__tb_top__DOT__u_eth__DOT__total_payload;
    __Vdly__tb_top__DOT__u_eth__DOT__total_payload = 0;
    IData/*31:0*/ __Vdly__tb_top__DOT__u_eth__DOT__crc_reg;
    __Vdly__tb_top__DOT__u_eth__DOT__crc_reg = 0;
    SData/*15:0*/ __Vdly__tb_top__DOT__u_eth__DOT__hdr_cnt;
    __Vdly__tb_top__DOT__u_eth__DOT__hdr_cnt = 0;
    CData/*2:0*/ __Vdly__tb_top__DOT__u_eth__DOT__pre_cnt;
    __Vdly__tb_top__DOT__u_eth__DOT__pre_cnt = 0;
    CData/*1:0*/ __Vdly__tb_top__DOT__u_pr__DOT__state;
    __Vdly__tb_top__DOT__u_pr__DOT__state = 0;
    SData/*15:0*/ __Vdly__tb_top__DOT__u_pr__DOT__cnt;
    __Vdly__tb_top__DOT__u_pr__DOT__cnt = 0;
    CData/*7:0*/ __Vdly__tb_top__DOT__u_pr__DOT__len_hi;
    __Vdly__tb_top__DOT__u_pr__DOT__len_hi = 0;
    CData/*7:0*/ __Vdly__tb_top__DOT__u_pr__DOT__len_lo;
    __Vdly__tb_top__DOT__u_pr__DOT__len_lo = 0;
    SData/*11:0*/ __Vdly__tb_top__DOT__u_ut__DOT__tick_cnt;
    __Vdly__tb_top__DOT__u_ut__DOT__tick_cnt = 0;
    CData/*1:0*/ __Vdly__tb_top__DOT__u_ut__DOT__st;
    __Vdly__tb_top__DOT__u_ut__DOT__st = 0;
    CData/*1:0*/ __Vdly__tb_top__DOT__u_ut__DOT__byte_idx;
    __Vdly__tb_top__DOT__u_ut__DOT__byte_idx = 0;
    CData/*7:0*/ __Vdly__tb_top__DOT__u_ut__DOT__sh;
    __Vdly__tb_top__DOT__u_ut__DOT__sh = 0;
    CData/*2:0*/ __Vdly__tb_top__DOT__u_ut__DOT__bit_idx;
    __Vdly__tb_top__DOT__u_ut__DOT__bit_idx = 0;
    // Body
    __Vdly__cycle_cnt = vlSelf->cycle_cnt;
    __Vdly__tb_top__DOT__u_ut__DOT__bit_idx = vlSelf->tb_top__DOT__u_ut__DOT__bit_idx;
    __Vdly__tb_top__DOT__u_ut__DOT__sh = vlSelf->tb_top__DOT__u_ut__DOT__sh;
    __Vdly__tb_top__DOT__u_ut__DOT__byte_idx = vlSelf->tb_top__DOT__u_ut__DOT__byte_idx;
    __Vdly__tb_top__DOT__u_ut__DOT__tick_cnt = vlSelf->tb_top__DOT__u_ut__DOT__tick_cnt;
    __Vdly__tb_top__DOT__u_ut__DOT__st = vlSelf->tb_top__DOT__u_ut__DOT__st;
    __Vdly__tb_top__DOT__u_eth__DOT__pre_cnt = vlSelf->tb_top__DOT__u_eth__DOT__pre_cnt;
    __Vdly__tb_top__DOT__u_eth__DOT__hdr_cnt = vlSelf->tb_top__DOT__u_eth__DOT__hdr_cnt;
    __Vdly__tb_top__DOT__u_eth__DOT__crc_reg = vlSelf->tb_top__DOT__u_eth__DOT__crc_reg;
    __Vdly__tb_top__DOT__u_eth__DOT__total_payload 
        = vlSelf->tb_top__DOT__u_eth__DOT__total_payload;
    __Vdly__tb_top__DOT__u_eth__DOT__payload_len = vlSelf->tb_top__DOT__u_eth__DOT__payload_len;
    __Vdly__tb_top__DOT__u_eth__DOT__crc_cnt = vlSelf->tb_top__DOT__u_eth__DOT__crc_cnt;
    __Vdly__tb_top__DOT__u_eth__DOT__crc_recv_shift 
        = vlSelf->tb_top__DOT__u_eth__DOT__crc_recv_shift;
    __Vdly__tb_top__DOT__u_eth__DOT__state = vlSelf->tb_top__DOT__u_eth__DOT__state;
    __Vdly__tb_top__DOT__u_pr__DOT__len_lo = vlSelf->tb_top__DOT__u_pr__DOT__len_lo;
    __Vdly__tb_top__DOT__u_pr__DOT__len_hi = vlSelf->tb_top__DOT__u_pr__DOT__len_hi;
    __Vdly__tb_top__DOT__u_pr__DOT__cnt = vlSelf->tb_top__DOT__u_pr__DOT__cnt;
    __Vdly__tb_top__DOT__u_pr__DOT__state = vlSelf->tb_top__DOT__u_pr__DOT__state;
    __Vdly__tb_top__DOT__u_prg__DOT__l2t_data_valid 
        = vlSelf->tb_top__DOT__u_prg__DOT__l2t_data_valid;
    vlSelf->tb_top__DOT__u_prg__DOT__p2l_data_valid 
        = ((IData)(vlSelf->rst_n) && (IData)(vlSelf->field_valid));
    if (vlSelf->rst_n) {
        if (vlSelf->l2t_stall) {
            vlSelf->l2t_stall_cycles = ((IData)(1U) 
                                        + vlSelf->l2t_stall_cycles);
        }
        __Vdly__cycle_cnt = ((IData)(1U) + vlSelf->cycle_cnt);
        if ((((IData)(vlSelf->parsed_valid_reg) & (0x50U 
                                                   == (IData)(vlSelf->parsed_type_reg))) 
             & (0x1e8480U > vlSelf->parsed_price_reg))) {
            vlSelf->tb_top__DOT__u_tl__DOT__d_volume 
                = vlSelf->parsed_volume_reg;
            vlSelf->tb_top__DOT__u_tl__DOT__d_order_id 
                = vlSelf->tb_top__DOT__u_prg__DOT__p2l_order_id_reg;
        }
        if ((2U & (IData)(vlSelf->tb_top__DOT__u_ut__DOT__st))) {
            if ((1U & (IData)(vlSelf->tb_top__DOT__u_ut__DOT__st))) {
                vlSelf->uart_tx = 1U;
                if ((0x879U == (IData)(vlSelf->tb_top__DOT__u_ut__DOT__tick_cnt))) {
                    __Vdly__tb_top__DOT__u_ut__DOT__tick_cnt = 0U;
                    if ((3U == (IData)(vlSelf->tb_top__DOT__u_ut__DOT__byte_idx))) {
                        __Vdly__tb_top__DOT__u_ut__DOT__st = 0U;
                    } else {
                        __Vdly__tb_top__DOT__u_ut__DOT__byte_idx 
                            = (3U & ((IData)(1U) + (IData)(vlSelf->tb_top__DOT__u_ut__DOT__byte_idx)));
                        __Vdly__tb_top__DOT__u_ut__DOT__sh 
                            = (0xffU & ((0U == (IData)(vlSelf->tb_top__DOT__u_ut__DOT__byte_idx))
                                         ? (vlSelf->tb_top__DOT__u_ut__DOT__word_reg 
                                            >> 8U) : 
                                        ((1U == (IData)(vlSelf->tb_top__DOT__u_ut__DOT__byte_idx))
                                          ? (vlSelf->tb_top__DOT__u_ut__DOT__word_reg 
                                             >> 0x10U)
                                          : ((2U == (IData)(vlSelf->tb_top__DOT__u_ut__DOT__byte_idx))
                                              ? (vlSelf->tb_top__DOT__u_ut__DOT__word_reg 
                                                 >> 0x18U)
                                              : 0U))));
                        __Vdly__tb_top__DOT__u_ut__DOT__st = 1U;
                    }
                } else {
                    __Vdly__tb_top__DOT__u_ut__DOT__tick_cnt 
                        = (0xfffU & ((IData)(1U) + (IData)(vlSelf->tb_top__DOT__u_ut__DOT__tick_cnt)));
                }
            } else {
                vlSelf->uart_tx = (1U & (IData)(vlSelf->tb_top__DOT__u_ut__DOT__sh));
                if ((0x879U == (IData)(vlSelf->tb_top__DOT__u_ut__DOT__tick_cnt))) {
                    __Vdly__tb_top__DOT__u_ut__DOT__sh 
                        = (0x7fU & ((IData)(vlSelf->tb_top__DOT__u_ut__DOT__sh) 
                                    >> 1U));
                    __Vdly__tb_top__DOT__u_ut__DOT__bit_idx 
                        = (7U & ((IData)(1U) + (IData)(vlSelf->tb_top__DOT__u_ut__DOT__bit_idx)));
                    __Vdly__tb_top__DOT__u_ut__DOT__tick_cnt = 0U;
                    if ((7U == (IData)(vlSelf->tb_top__DOT__u_ut__DOT__bit_idx))) {
                        __Vdly__tb_top__DOT__u_ut__DOT__st = 3U;
                    }
                } else {
                    __Vdly__tb_top__DOT__u_ut__DOT__tick_cnt 
                        = (0xfffU & ((IData)(1U) + (IData)(vlSelf->tb_top__DOT__u_ut__DOT__tick_cnt)));
                }
            }
        } else if ((1U & (IData)(vlSelf->tb_top__DOT__u_ut__DOT__st))) {
            vlSelf->uart_tx = 0U;
            if ((0x879U == (IData)(vlSelf->tb_top__DOT__u_ut__DOT__tick_cnt))) {
                __Vdly__tb_top__DOT__u_ut__DOT__tick_cnt = 0U;
                __Vdly__tb_top__DOT__u_ut__DOT__bit_idx = 0U;
                __Vdly__tb_top__DOT__u_ut__DOT__st = 2U;
            } else {
                __Vdly__tb_top__DOT__u_ut__DOT__tick_cnt 
                    = (0xfffU & ((IData)(1U) + (IData)(vlSelf->tb_top__DOT__u_ut__DOT__tick_cnt)));
            }
        } else {
            __Vdly__tb_top__DOT__u_ut__DOT__tick_cnt = 0U;
            __Vdly__tb_top__DOT__u_ut__DOT__byte_idx = 0U;
            vlSelf->uart_tx = 1U;
            __Vdly__tb_top__DOT__u_ut__DOT__bit_idx = 0U;
            if (vlSelf->tb_top__DOT__u_ut__DOT__accept) {
                vlSelf->tb_top__DOT__u_ut__DOT__word_reg 
                    = vlSelf->tx_word_data;
                __Vdly__tb_top__DOT__u_ut__DOT__sh 
                    = (0xffU & vlSelf->tx_word_data);
                __Vdly__tb_top__DOT__u_ut__DOT__st = 1U;
            }
        }
        vlSelf->tb_top__DOT__u_ut__DOT__tick_cnt = __Vdly__tb_top__DOT__u_ut__DOT__tick_cnt;
        vlSelf->tb_top__DOT__u_ut__DOT__byte_idx = __Vdly__tb_top__DOT__u_ut__DOT__byte_idx;
        vlSelf->tb_top__DOT__u_ut__DOT__sh = __Vdly__tb_top__DOT__u_ut__DOT__sh;
        vlSelf->tb_top__DOT__u_ut__DOT__bit_idx = __Vdly__tb_top__DOT__u_ut__DOT__bit_idx;
        vlSelf->tb_top__DOT__u_ut__DOT__st = __Vdly__tb_top__DOT__u_ut__DOT__st;
        if (vlSelf->field_valid) {
            vlSelf->tb_top__DOT__u_prg__DOT__p2l_volume_reg 
                = vlSelf->volume;
            vlSelf->tb_top__DOT__u_prg__DOT__p2l_price_reg 
                = vlSelf->price;
            vlSelf->tb_top__DOT__u_prg__DOT__p2l_type_reg 
                = vlSelf->msg_type;
        }
        if (((IData)(vlSelf->tb_top__DOT__uart_ready_masked) 
             & (IData)(vlSelf->tb_top__DOT__u_prg__DOT__l2t_data_valid))) {
            __Vdly__tb_top__DOT__u_prg__DOT__l2t_data_valid = 0U;
        }
        if ((((~ (IData)(vlSelf->tb_top__DOT__u_prg__DOT__l2t_data_valid)) 
              | (IData)(vlSelf->tb_top__DOT__uart_ready_masked)) 
             & (IData)(vlSelf->decision_valid))) {
            vlSelf->tb_top__DOT__u_prg__DOT__l2t_type_reg 
                = vlSelf->tb_top__DOT__decision_type;
            vlSelf->tb_top__DOT__u_prg__DOT__l2t_data_reg 
                = vlSelf->tb_top__DOT__decision_data;
            __Vdly__tb_top__DOT__u_prg__DOT__l2t_data_valid = 1U;
            vlSelf->tb_top__DOT__u_prg__DOT__t_logic_cap 
                = vlSelf->cycle_cnt;
            vlSelf->tb_top__DOT__u_prg__DOT__t_decision_cap 
                = vlSelf->cycle_cnt;
            vlSelf->tb_top__DOT__u_prg__DOT__t_parser_cap 
                = vlSelf->tb_top__DOT__u_prg__DOT__p2l_timestamp;
            vlSelf->tb_top__DOT__u_prg__DOT__t_ingress_cap 
                = vlSelf->tb_top__DOT__u_prg__DOT__ingress_s2;
        }
    } else {
        vlSelf->l2t_stall_cycles = 0U;
        __Vdly__cycle_cnt = 0U;
        vlSelf->tb_top__DOT__u_tl__DOT__d_volume = 0U;
        __Vdly__tb_top__DOT__u_ut__DOT__tick_cnt = 0U;
        __Vdly__tb_top__DOT__u_ut__DOT__byte_idx = 0U;
        __Vdly__tb_top__DOT__u_ut__DOT__st = 0U;
        vlSelf->uart_tx = 1U;
        __Vdly__tb_top__DOT__u_ut__DOT__bit_idx = 0U;
        __Vdly__tb_top__DOT__u_ut__DOT__sh = 0U;
        vlSelf->tb_top__DOT__u_ut__DOT__word_reg = 0U;
        vlSelf->tb_top__DOT__u_ut__DOT__tick_cnt = __Vdly__tb_top__DOT__u_ut__DOT__tick_cnt;
        vlSelf->tb_top__DOT__u_ut__DOT__byte_idx = __Vdly__tb_top__DOT__u_ut__DOT__byte_idx;
        vlSelf->tb_top__DOT__u_ut__DOT__sh = __Vdly__tb_top__DOT__u_ut__DOT__sh;
        vlSelf->tb_top__DOT__u_ut__DOT__bit_idx = __Vdly__tb_top__DOT__u_ut__DOT__bit_idx;
        vlSelf->tb_top__DOT__u_ut__DOT__st = __Vdly__tb_top__DOT__u_ut__DOT__st;
        vlSelf->tb_top__DOT__u_prg__DOT__p2l_volume_reg = 0U;
        vlSelf->tb_top__DOT__u_prg__DOT__p2l_price_reg = 0U;
        vlSelf->tb_top__DOT__u_tl__DOT__d_order_id = 0ULL;
        vlSelf->tb_top__DOT__u_prg__DOT__p2l_type_reg = 0U;
        __Vdly__tb_top__DOT__u_prg__DOT__l2t_data_valid = 0U;
        vlSelf->tb_top__DOT__u_prg__DOT__l2t_type_reg = 0U;
        vlSelf->tb_top__DOT__u_prg__DOT__l2t_data_reg = 0U;
        vlSelf->tb_top__DOT__u_prg__DOT__t_ingress_cap = 0U;
        vlSelf->tb_top__DOT__u_prg__DOT__t_parser_cap = 0U;
        vlSelf->tb_top__DOT__u_prg__DOT__t_logic_cap = 0U;
        vlSelf->tb_top__DOT__u_prg__DOT__t_decision_cap = 0U;
    }
    vlSelf->tb_top__DOT__u_prg__DOT__l2t_data_valid 
        = __Vdly__tb_top__DOT__u_prg__DOT__l2t_data_valid;
    vlSelf->tb_top__DOT__uart_ready_masked = ((IData)(vlSelf->sink_allow) 
                                              & (0U 
                                                 == (IData)(vlSelf->tb_top__DOT__u_ut__DOT__st)));
    vlSelf->parsed_volume_reg = vlSelf->tb_top__DOT__u_prg__DOT__p2l_volume_reg;
    vlSelf->tx_word_data = vlSelf->tb_top__DOT__u_prg__DOT__l2t_data_reg;
    vlSelf->t_logic = vlSelf->tb_top__DOT__u_prg__DOT__t_logic_cap;
    vlSelf->t_decision = vlSelf->tb_top__DOT__u_prg__DOT__t_decision_cap;
    vlSelf->t_parser = vlSelf->tb_top__DOT__u_prg__DOT__t_parser_cap;
    vlSelf->t_ingress = vlSelf->tb_top__DOT__u_prg__DOT__t_ingress_cap;
    vlSelf->tb_top__DOT__u_ut__DOT__accept = ((0U == (IData)(vlSelf->tb_top__DOT__u_ut__DOT__st)) 
                                              & (IData)(vlSelf->tb_top__DOT__u_prg__DOT__l2t_data_valid));
    vlSelf->decision_valid = ((IData)(vlSelf->rst_n) 
                              && (((IData)(vlSelf->parsed_valid_reg) 
                                   & (0x50U == (IData)(vlSelf->parsed_type_reg))) 
                                  & (0x1e8480U > vlSelf->parsed_price_reg)));
    vlSelf->tx_word_valid = ((IData)(vlSelf->tb_top__DOT__u_prg__DOT__l2t_data_valid) 
                             & (IData)(vlSelf->tb_top__DOT__uart_ready_masked));
    vlSelf->l2t_stall = ((~ (IData)(vlSelf->tb_top__DOT__uart_ready_masked)) 
                         & (IData)(vlSelf->tb_top__DOT__u_prg__DOT__l2t_data_valid));
    if (vlSelf->rst_n) {
        if (vlSelf->field_valid) {
            vlSelf->tb_top__DOT__u_prg__DOT__p2l_order_id_reg 
                = vlSelf->order_id;
            vlSelf->tb_top__DOT__u_prg__DOT__p2l_timestamp 
                = vlSelf->cycle_cnt;
            vlSelf->tb_top__DOT__u_prg__DOT__ingress_s2 
                = vlSelf->tb_top__DOT__u_prg__DOT__ingress_last;
        }
        if ((((IData)(vlSelf->parsed_valid_reg) & (0x50U 
                                                   == (IData)(vlSelf->parsed_type_reg))) 
             & (0x1e8480U > vlSelf->parsed_price_reg))) {
            vlSelf->tb_top__DOT__decision_type = vlSelf->parsed_type_reg;
            vlSelf->tb_top__DOT__decision_data = vlSelf->parsed_price_reg;
        }
        vlSelf->parsed_valid_reg = vlSelf->tb_top__DOT__u_prg__DOT__p2l_data_valid;
        vlSelf->parsed_type_reg = vlSelf->tb_top__DOT__u_prg__DOT__p2l_type_reg;
        vlSelf->parsed_price_reg = vlSelf->tb_top__DOT__u_prg__DOT__p2l_price_reg;
        vlSelf->t_parser_event = vlSelf->tb_top__DOT__u_prg__DOT__p2l_timestamp;
        if (vlSelf->tb_top__DOT__parser_msg_start) {
            vlSelf->tb_top__DOT__u_prg__DOT__ingress_last 
                = vlSelf->cycle_cnt;
        }
        vlSelf->cycle_cnt = __Vdly__cycle_cnt;
        vlSelf->field_valid = 0U;
        vlSelf->tb_top__DOT__parser_msg_start = 0U;
        if ((2U & (IData)(vlSelf->tb_top__DOT__u_pr__DOT__state))) {
            if ((1U & (IData)(vlSelf->tb_top__DOT__u_pr__DOT__state))) {
                if (vlSelf->tb_top__DOT__u_prg__DOT__rx2p_data_valid) {
                    if ((((IData)(1U) + (IData)(vlSelf->tb_top__DOT__u_pr__DOT__cnt)) 
                         == (IData)(vlSelf->tb_top__DOT__u_pr__DOT__body_left))) {
                        __Vdly__tb_top__DOT__u_pr__DOT__state = 0U;
                        __Vdly__tb_top__DOT__u_pr__DOT__cnt = 0U;
                    } else {
                        __Vdly__tb_top__DOT__u_pr__DOT__cnt 
                            = (0xffffU & ((IData)(1U) 
                                          + (IData)(vlSelf->tb_top__DOT__u_pr__DOT__cnt)));
                    }
                }
            } else {
                vlSelf->field_valid = 1U;
                vlSelf->msg_type = vlSelf->tb_top__DOT__u_pr__DOT__type_reg;
                __Vdly__tb_top__DOT__u_pr__DOT__state = 0U;
            }
        } else if ((1U & (IData)(vlSelf->tb_top__DOT__u_pr__DOT__state))) {
            if (vlSelf->tb_top__DOT__u_prg__DOT__rx2p_data_valid) {
                if (((0xaU <= (IData)(vlSelf->tb_top__DOT__u_pr__DOT__cnt)) 
                     & (0x11U >= (IData)(vlSelf->tb_top__DOT__u_pr__DOT__cnt)))) {
                    vlSelf->order_id = (VL_SHIFTL_QQI(64,64,32, vlSelf->order_id, 8U) 
                                        | (QData)((IData)(vlSelf->tb_top__DOT__u_prg__DOT__rx2p_data)));
                }
                if (((0x13U <= (IData)(vlSelf->tb_top__DOT__u_pr__DOT__cnt)) 
                     & (0x16U >= (IData)(vlSelf->tb_top__DOT__u_pr__DOT__cnt)))) {
                    vlSelf->volume = (VL_SHIFTL_III(32,32,32, vlSelf->volume, 8U) 
                                      | (IData)(vlSelf->tb_top__DOT__u_prg__DOT__rx2p_data));
                }
                if (((0x1fU <= (IData)(vlSelf->tb_top__DOT__u_pr__DOT__cnt)) 
                     & (0x22U >= (IData)(vlSelf->tb_top__DOT__u_pr__DOT__cnt)))) {
                    vlSelf->price = (VL_SHIFTL_III(32,32,32, vlSelf->price, 8U) 
                                     | (IData)(vlSelf->tb_top__DOT__u_prg__DOT__rx2p_data));
                }
                if ((((IData)(1U) + (IData)(vlSelf->tb_top__DOT__u_pr__DOT__cnt)) 
                     == (IData)(vlSelf->tb_top__DOT__u_pr__DOT__body_left))) {
                    __Vdly__tb_top__DOT__u_pr__DOT__state = 2U;
                    __Vdly__tb_top__DOT__u_pr__DOT__cnt = 0U;
                } else {
                    __Vdly__tb_top__DOT__u_pr__DOT__cnt 
                        = (0xffffU & ((IData)(1U) + (IData)(vlSelf->tb_top__DOT__u_pr__DOT__cnt)));
                }
            }
        } else if (vlSelf->tb_top__DOT__u_prg__DOT__rx2p_data_valid) {
            if ((0U == (IData)(vlSelf->tb_top__DOT__u_pr__DOT__cnt))) {
                vlSelf->tb_top__DOT__parser_msg_start = 1U;
                __Vdly__tb_top__DOT__u_pr__DOT__len_hi 
                    = vlSelf->tb_top__DOT__u_prg__DOT__rx2p_data;
                __Vdly__tb_top__DOT__u_pr__DOT__cnt = 1U;
            } else if ((1U == (IData)(vlSelf->tb_top__DOT__u_pr__DOT__cnt))) {
                __Vdly__tb_top__DOT__u_pr__DOT__len_lo 
                    = vlSelf->tb_top__DOT__u_prg__DOT__rx2p_data;
                __Vdly__tb_top__DOT__u_pr__DOT__cnt = 2U;
            } else if ((2U == (IData)(vlSelf->tb_top__DOT__u_pr__DOT__cnt))) {
                vlSelf->tb_top__DOT__u_pr__DOT__type_reg 
                    = vlSelf->tb_top__DOT__u_prg__DOT__rx2p_data;
                vlSelf->tb_top__DOT__u_pr__DOT__length 
                    = (((IData)(vlSelf->tb_top__DOT__u_pr__DOT__len_hi) 
                        << 8U) | (IData)(vlSelf->tb_top__DOT__u_pr__DOT__len_lo));
                __Vdly__tb_top__DOT__u_pr__DOT__cnt = 0U;
                vlSelf->order_id = 0ULL;
                vlSelf->price = 0U;
                vlSelf->volume = 0U;
                __Vdly__tb_top__DOT__u_pr__DOT__state 
                    = ((0x50U == (IData)(vlSelf->tb_top__DOT__u_prg__DOT__rx2p_data))
                        ? 1U : 3U);
                vlSelf->tb_top__DOT__u_pr__DOT__body_left 
                    = (0xffffU & ((((IData)(vlSelf->tb_top__DOT__u_pr__DOT__len_hi) 
                                    << 8U) | (IData)(vlSelf->tb_top__DOT__u_pr__DOT__len_lo)) 
                                  - (IData)(1U)));
            }
        }
    } else {
        vlSelf->tb_top__DOT__u_prg__DOT__p2l_order_id_reg = 0ULL;
        vlSelf->tb_top__DOT__decision_type = 0U;
        vlSelf->tb_top__DOT__decision_data = 0U;
        vlSelf->parsed_valid_reg = vlSelf->tb_top__DOT__u_prg__DOT__p2l_data_valid;
        vlSelf->parsed_type_reg = vlSelf->tb_top__DOT__u_prg__DOT__p2l_type_reg;
        vlSelf->parsed_price_reg = vlSelf->tb_top__DOT__u_prg__DOT__p2l_price_reg;
        vlSelf->tb_top__DOT__u_prg__DOT__p2l_timestamp = 0U;
        vlSelf->t_parser_event = vlSelf->tb_top__DOT__u_prg__DOT__p2l_timestamp;
        vlSelf->tb_top__DOT__u_prg__DOT__ingress_s2 = 0U;
        vlSelf->tb_top__DOT__u_prg__DOT__ingress_last = 0U;
        vlSelf->cycle_cnt = __Vdly__cycle_cnt;
        vlSelf->tb_top__DOT__parser_msg_start = 0U;
        __Vdly__tb_top__DOT__u_pr__DOT__state = 0U;
        __Vdly__tb_top__DOT__u_pr__DOT__len_hi = 0U;
        __Vdly__tb_top__DOT__u_pr__DOT__len_lo = 0U;
        vlSelf->tb_top__DOT__u_pr__DOT__length = 0U;
        vlSelf->tb_top__DOT__u_pr__DOT__type_reg = 0U;
        __Vdly__tb_top__DOT__u_pr__DOT__cnt = 0U;
        vlSelf->tb_top__DOT__u_pr__DOT__body_left = 0U;
        vlSelf->field_valid = 0U;
        vlSelf->msg_type = 0U;
        vlSelf->order_id = 0ULL;
        vlSelf->price = 0U;
        vlSelf->volume = 0U;
    }
    vlSelf->tb_top__DOT__u_pr__DOT__state = __Vdly__tb_top__DOT__u_pr__DOT__state;
    vlSelf->tb_top__DOT__u_pr__DOT__cnt = __Vdly__tb_top__DOT__u_pr__DOT__cnt;
    vlSelf->tb_top__DOT__u_pr__DOT__len_hi = __Vdly__tb_top__DOT__u_pr__DOT__len_hi;
    vlSelf->tb_top__DOT__u_pr__DOT__len_lo = __Vdly__tb_top__DOT__u_pr__DOT__len_lo;
    vlSelf->tb_top__DOT__u_prg__DOT__rx2p_data_valid 
        = ((IData)(vlSelf->rst_n) && (IData)(vlSelf->payload_valid));
    if (vlSelf->rst_n) {
        if (vlSelf->payload_valid) {
            vlSelf->tb_top__DOT__u_prg__DOT__rx2p_data 
                = vlSelf->payload_byte;
        }
        vlSelf->payload_valid = 0U;
        vlSelf->eth_crc_valid = 0U;
        if ((4U & (IData)(vlSelf->tb_top__DOT__u_eth__DOT__state))) {
            if ((2U & (IData)(vlSelf->tb_top__DOT__u_eth__DOT__state))) {
                __Vdly__tb_top__DOT__u_eth__DOT__state = 0U;
            } else if ((1U & (IData)(vlSelf->tb_top__DOT__u_eth__DOT__state))) {
                if (vlSelf->rx_valid) {
                    if ((0U == (IData)(vlSelf->tb_top__DOT__u_eth__DOT__crc_cnt))) {
                        __Vdly__tb_top__DOT__u_eth__DOT__crc_recv_shift 
                            = ((0xffffff00U & __Vdly__tb_top__DOT__u_eth__DOT__crc_recv_shift) 
                               | (IData)(vlSelf->rx_byte));
                        __Vdly__tb_top__DOT__u_eth__DOT__crc_cnt = 1U;
                    } else if ((1U == (IData)(vlSelf->tb_top__DOT__u_eth__DOT__crc_cnt))) {
                        __Vdly__tb_top__DOT__u_eth__DOT__crc_recv_shift 
                            = ((0xffff00ffU & __Vdly__tb_top__DOT__u_eth__DOT__crc_recv_shift) 
                               | ((IData)(vlSelf->rx_byte) 
                                  << 8U));
                        __Vdly__tb_top__DOT__u_eth__DOT__crc_cnt = 2U;
                    } else if ((2U == (IData)(vlSelf->tb_top__DOT__u_eth__DOT__crc_cnt))) {
                        __Vdly__tb_top__DOT__u_eth__DOT__crc_recv_shift 
                            = ((0xff00ffffU & __Vdly__tb_top__DOT__u_eth__DOT__crc_recv_shift) 
                               | ((IData)(vlSelf->rx_byte) 
                                  << 0x10U));
                        __Vdly__tb_top__DOT__u_eth__DOT__crc_cnt = 3U;
                    } else if ((3U == (IData)(vlSelf->tb_top__DOT__u_eth__DOT__crc_cnt))) {
                        vlSelf->tb_top__DOT__u_eth__DOT__unnamedblk2__DOT__new_fcs 
                            = (((IData)(vlSelf->rx_byte) 
                                << 0x18U) | (0xffffffU 
                                             & vlSelf->tb_top__DOT__u_eth__DOT__crc_recv_shift));
                        vlSelf->tb_top__DOT__u_eth__DOT__fcs_word 
                            = vlSelf->tb_top__DOT__u_eth__DOT__unnamedblk2__DOT__new_fcs;
                        vlSelf->dbg_crc_calc = (~ vlSelf->tb_top__DOT__u_eth__DOT__crc_reg);
                        vlSelf->eth_crc_valid = 1U;
                        vlSelf->tb_top__DOT__u_eth__DOT__crc_started = 0U;
                        __Vdly__tb_top__DOT__u_eth__DOT__state = 0U;
                        __Vdly__tb_top__DOT__u_eth__DOT__crc_cnt = 0U;
                        vlSelf->dbg_crc_recv = vlSelf->tb_top__DOT__u_eth__DOT__unnamedblk2__DOT__new_fcs;
                        vlSelf->eth_crc_ok = ((~ vlSelf->tb_top__DOT__u_eth__DOT__crc_reg) 
                                              == vlSelf->tb_top__DOT__u_eth__DOT__unnamedblk2__DOT__new_fcs);
                    }
                }
            } else if (vlSelf->rx_valid) {
                __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__0__data_byte 
                    = vlSelf->rx_byte;
                __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__0__crc_in 
                    = vlSelf->tb_top__DOT__u_eth__DOT__crc_reg;
                __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__0__c 
                    = (__Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__0__crc_in 
                       ^ (IData)(__Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__0__data_byte));
                if ((0U == (IData)(vlSelf->tb_top__DOT__u_eth__DOT__payload_cnt))) {
                    __Vdly__tb_top__DOT__u_eth__DOT__payload_len 
                        = ((0xffU & (IData)(__Vdly__tb_top__DOT__u_eth__DOT__payload_len)) 
                           | ((IData)(vlSelf->rx_byte) 
                              << 8U));
                } else if ((1U == (IData)(vlSelf->tb_top__DOT__u_eth__DOT__payload_cnt))) {
                    __Vdly__tb_top__DOT__u_eth__DOT__total_payload 
                        = (0xffffU & ((IData)(2U) + 
                                      ((0xff00U & (IData)(vlSelf->tb_top__DOT__u_eth__DOT__payload_len)) 
                                       | (IData)(vlSelf->rx_byte))));
                    vlSelf->dbg_payload_len = ((0xff00U 
                                                & (IData)(vlSelf->tb_top__DOT__u_eth__DOT__payload_len)) 
                                               | (IData)(vlSelf->rx_byte));
                    vlSelf->dbg_total_payload = (0xffffU 
                                                 & ((IData)(2U) 
                                                    + 
                                                    ((0xff00U 
                                                      & (IData)(vlSelf->tb_top__DOT__u_eth__DOT__payload_len)) 
                                                     | (IData)(vlSelf->rx_byte))));
                    __Vdly__tb_top__DOT__u_eth__DOT__payload_len 
                        = ((0xff00U & (IData)(__Vdly__tb_top__DOT__u_eth__DOT__payload_len)) 
                           | (IData)(vlSelf->rx_byte));
                }
                if (vlSelf->tb_top__DOT__u_eth__DOT__mac_match) {
                    vlSelf->payload_byte = vlSelf->rx_byte;
                    vlSelf->payload_valid = 1U;
                }
                __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__0__c 
                    = ((1U & __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__0__c)
                        ? (0xedb88320U ^ VL_SHIFTR_III(32,32,32, __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__0__c, 1U))
                        : VL_SHIFTR_III(32,32,32, __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__0__c, 1U));
                __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__0__c 
                    = ((1U & __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__0__c)
                        ? (0xedb88320U ^ VL_SHIFTR_III(32,32,32, __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__0__c, 1U))
                        : VL_SHIFTR_III(32,32,32, __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__0__c, 1U));
                __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__0__c 
                    = ((1U & __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__0__c)
                        ? (0xedb88320U ^ VL_SHIFTR_III(32,32,32, __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__0__c, 1U))
                        : VL_SHIFTR_III(32,32,32, __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__0__c, 1U));
                __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__0__c 
                    = ((1U & __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__0__c)
                        ? (0xedb88320U ^ VL_SHIFTR_III(32,32,32, __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__0__c, 1U))
                        : VL_SHIFTR_III(32,32,32, __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__0__c, 1U));
                __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__0__c 
                    = ((1U & __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__0__c)
                        ? (0xedb88320U ^ VL_SHIFTR_III(32,32,32, __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__0__c, 1U))
                        : VL_SHIFTR_III(32,32,32, __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__0__c, 1U));
                __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__0__c 
                    = ((1U & __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__0__c)
                        ? (0xedb88320U ^ VL_SHIFTR_III(32,32,32, __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__0__c, 1U))
                        : VL_SHIFTR_III(32,32,32, __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__0__c, 1U));
                __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__0__c 
                    = ((1U & __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__0__c)
                        ? (0xedb88320U ^ VL_SHIFTR_III(32,32,32, __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__0__c, 1U))
                        : VL_SHIFTR_III(32,32,32, __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__0__c, 1U));
                __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__0__c 
                    = ((1U & __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__0__c)
                        ? (0xedb88320U ^ VL_SHIFTR_III(32,32,32, __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__0__c, 1U))
                        : VL_SHIFTR_III(32,32,32, __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__0__c, 1U));
                if (((0xffffU & ((IData)(1U) + (IData)(vlSelf->tb_top__DOT__u_eth__DOT__payload_cnt))) 
                     == (IData)(vlSelf->tb_top__DOT__u_eth__DOT__total_payload))) {
                    __Vdly__tb_top__DOT__u_eth__DOT__crc_cnt = 0U;
                    __Vdly__tb_top__DOT__u_eth__DOT__crc_recv_shift = 0U;
                    vlSelf->dbg_payload_cnt_last = 
                        (0xffffU & ((IData)(1U) + (IData)(vlSelf->tb_top__DOT__u_eth__DOT__payload_cnt)));
                    __Vdly__tb_top__DOT__u_eth__DOT__state = 5U;
                }
                vlSelf->tb_top__DOT__u_eth__DOT__payload_cnt 
                    = (0xffffU & ((IData)(1U) + (IData)(vlSelf->tb_top__DOT__u_eth__DOT__payload_cnt)));
                __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__0__Vfuncout 
                    = __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__0__c;
                vlSelf->tb_top__DOT__u_eth__DOT__next_crc 
                    = __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__0__Vfuncout;
                __Vdly__tb_top__DOT__u_eth__DOT__crc_reg 
                    = vlSelf->tb_top__DOT__u_eth__DOT__next_crc;
            }
        } else if ((2U & (IData)(vlSelf->tb_top__DOT__u_eth__DOT__state))) {
            if ((1U & (IData)(vlSelf->tb_top__DOT__u_eth__DOT__state))) {
                if (vlSelf->rx_valid) {
                    __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__1__data_byte 
                        = vlSelf->rx_byte;
                    __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__1__crc_in 
                        = vlSelf->tb_top__DOT__u_eth__DOT__crc_reg;
                    __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__1__c 
                        = (__Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__1__crc_in 
                           ^ (IData)(__Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__1__data_byte));
                    if ((6U > (IData)(vlSelf->tb_top__DOT__u_eth__DOT__hdr_cnt))) {
                        vlSelf->tb_top__DOT__u_eth__DOT__full_dest 
                            = ((0xffffffffff00ULL & 
                                (vlSelf->tb_top__DOT__u_eth__DOT__dest_mac_shift 
                                 << 8U)) | (QData)((IData)(vlSelf->rx_byte)));
                        vlSelf->tb_top__DOT__u_eth__DOT__dest_mac_shift 
                            = vlSelf->tb_top__DOT__u_eth__DOT__full_dest;
                        if ((5U == (IData)(vlSelf->tb_top__DOT__u_eth__DOT__hdr_cnt))) {
                            vlSelf->tb_top__DOT__u_eth__DOT__this_cycle_match 
                                = ((0x1122334455ULL 
                                    == vlSelf->tb_top__DOT__u_eth__DOT__full_dest) 
                                   | (0xffffffffffffULL 
                                      == vlSelf->tb_top__DOT__u_eth__DOT__full_dest));
                            vlSelf->tb_top__DOT__u_eth__DOT__mac_match 
                                = vlSelf->tb_top__DOT__u_eth__DOT__this_cycle_match;
                        }
                    }
                    __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__1__c 
                        = ((1U & __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__1__c)
                            ? (0xedb88320U ^ VL_SHIFTR_III(32,32,32, __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__1__c, 1U))
                            : VL_SHIFTR_III(32,32,32, __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__1__c, 1U));
                    __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__1__c 
                        = ((1U & __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__1__c)
                            ? (0xedb88320U ^ VL_SHIFTR_III(32,32,32, __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__1__c, 1U))
                            : VL_SHIFTR_III(32,32,32, __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__1__c, 1U));
                    __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__1__c 
                        = ((1U & __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__1__c)
                            ? (0xedb88320U ^ VL_SHIFTR_III(32,32,32, __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__1__c, 1U))
                            : VL_SHIFTR_III(32,32,32, __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__1__c, 1U));
                    __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__1__c 
                        = ((1U & __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__1__c)
                            ? (0xedb88320U ^ VL_SHIFTR_III(32,32,32, __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__1__c, 1U))
                            : VL_SHIFTR_III(32,32,32, __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__1__c, 1U));
                    __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__1__c 
                        = ((1U & __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__1__c)
                            ? (0xedb88320U ^ VL_SHIFTR_III(32,32,32, __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__1__c, 1U))
                            : VL_SHIFTR_III(32,32,32, __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__1__c, 1U));
                    __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__1__c 
                        = ((1U & __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__1__c)
                            ? (0xedb88320U ^ VL_SHIFTR_III(32,32,32, __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__1__c, 1U))
                            : VL_SHIFTR_III(32,32,32, __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__1__c, 1U));
                    __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__1__c 
                        = ((1U & __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__1__c)
                            ? (0xedb88320U ^ VL_SHIFTR_III(32,32,32, __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__1__c, 1U))
                            : VL_SHIFTR_III(32,32,32, __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__1__c, 1U));
                    __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__1__c 
                        = ((1U & __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__1__c)
                            ? (0xedb88320U ^ VL_SHIFTR_III(32,32,32, __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__1__c, 1U))
                            : VL_SHIFTR_III(32,32,32, __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__1__c, 1U));
                    __Vdly__tb_top__DOT__u_eth__DOT__hdr_cnt 
                        = (0xffffU & ((IData)(1U) + (IData)(vlSelf->tb_top__DOT__u_eth__DOT__hdr_cnt)));
                    if ((0xdU == (IData)(vlSelf->tb_top__DOT__u_eth__DOT__hdr_cnt))) {
                        __Vdly__tb_top__DOT__u_eth__DOT__state = 4U;
                        vlSelf->tb_top__DOT__u_eth__DOT__payload_cnt = 0U;
                    }
                    __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__1__Vfuncout 
                        = __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__1__c;
                    vlSelf->tb_top__DOT__u_eth__DOT__next_crc 
                        = __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__1__Vfuncout;
                    __Vdly__tb_top__DOT__u_eth__DOT__crc_reg 
                        = vlSelf->tb_top__DOT__u_eth__DOT__next_crc;
                }
            } else if (vlSelf->rx_valid) {
                if ((0xd5U == (IData)(vlSelf->rx_byte))) {
                    __Vdly__tb_top__DOT__u_eth__DOT__crc_reg = 0xffffffffU;
                    vlSelf->tb_top__DOT__u_eth__DOT__crc_started = 1U;
                    __Vdly__tb_top__DOT__u_eth__DOT__crc_recv_shift = 0U;
                    __Vdly__tb_top__DOT__u_eth__DOT__crc_cnt = 0U;
                    __Vdly__tb_top__DOT__u_eth__DOT__state = 3U;
                    __Vdly__tb_top__DOT__u_eth__DOT__hdr_cnt = 0U;
                    vlSelf->tb_top__DOT__u_eth__DOT__dest_mac_shift = 0ULL;
                    vlSelf->tb_top__DOT__u_eth__DOT__mac_match = 0U;
                } else {
                    __Vdly__tb_top__DOT__u_eth__DOT__state = 0U;
                }
            }
        } else if ((1U & (IData)(vlSelf->tb_top__DOT__u_eth__DOT__state))) {
            if (vlSelf->rx_valid) {
                if ((0x55U == (IData)(vlSelf->rx_byte))) {
                    __Vdly__tb_top__DOT__u_eth__DOT__pre_cnt 
                        = (7U & ((IData)(1U) + (IData)(vlSelf->tb_top__DOT__u_eth__DOT__pre_cnt)));
                    if ((6U == (IData)(vlSelf->tb_top__DOT__u_eth__DOT__pre_cnt))) {
                        __Vdly__tb_top__DOT__u_eth__DOT__state = 2U;
                    }
                } else {
                    __Vdly__tb_top__DOT__u_eth__DOT__state = 0U;
                    __Vdly__tb_top__DOT__u_eth__DOT__pre_cnt = 0U;
                }
            }
        } else if (((IData)(vlSelf->rx_valid) & (0x55U 
                                                 == (IData)(vlSelf->rx_byte)))) {
            __Vdly__tb_top__DOT__u_eth__DOT__state = 1U;
            __Vdly__tb_top__DOT__u_eth__DOT__pre_cnt = 1U;
        }
    } else {
        vlSelf->tb_top__DOT__u_prg__DOT__rx2p_data = 0U;
        __Vdly__tb_top__DOT__u_eth__DOT__state = 0U;
        __Vdly__tb_top__DOT__u_eth__DOT__pre_cnt = 0U;
        __Vdly__tb_top__DOT__u_eth__DOT__hdr_cnt = 0U;
        vlSelf->tb_top__DOT__u_eth__DOT__payload_cnt = 0U;
        __Vdly__tb_top__DOT__u_eth__DOT__payload_len = 0U;
        vlSelf->tb_top__DOT__u_eth__DOT__mac_match = 0U;
        vlSelf->payload_valid = 0U;
        __Vdly__tb_top__DOT__u_eth__DOT__crc_cnt = 0U;
        vlSelf->tb_top__DOT__u_eth__DOT__dest_mac_shift = 0ULL;
        __Vdly__tb_top__DOT__u_eth__DOT__crc_reg = 0xffffffffU;
        __Vdly__tb_top__DOT__u_eth__DOT__crc_recv_shift = 0U;
        vlSelf->eth_crc_ok = 0U;
        vlSelf->eth_crc_valid = 0U;
        vlSelf->tb_top__DOT__u_eth__DOT__crc_started = 0U;
        vlSelf->tb_top__DOT__u_eth__DOT__fcs_word = 0U;
        __Vdly__tb_top__DOT__u_eth__DOT__total_payload = 0U;
        vlSelf->dbg_crc_calc = 0U;
        vlSelf->dbg_crc_recv = 0U;
        vlSelf->dbg_payload_len = 0U;
        vlSelf->dbg_total_payload = 0U;
        vlSelf->dbg_payload_cnt_last = 0U;
    }
    vlSelf->tb_top__DOT__u_eth__DOT__state = __Vdly__tb_top__DOT__u_eth__DOT__state;
    vlSelf->tb_top__DOT__u_eth__DOT__crc_recv_shift 
        = __Vdly__tb_top__DOT__u_eth__DOT__crc_recv_shift;
    vlSelf->tb_top__DOT__u_eth__DOT__crc_cnt = __Vdly__tb_top__DOT__u_eth__DOT__crc_cnt;
    vlSelf->tb_top__DOT__u_eth__DOT__payload_len = __Vdly__tb_top__DOT__u_eth__DOT__payload_len;
    vlSelf->tb_top__DOT__u_eth__DOT__total_payload 
        = __Vdly__tb_top__DOT__u_eth__DOT__total_payload;
    vlSelf->tb_top__DOT__u_eth__DOT__crc_reg = __Vdly__tb_top__DOT__u_eth__DOT__crc_reg;
    vlSelf->tb_top__DOT__u_eth__DOT__hdr_cnt = __Vdly__tb_top__DOT__u_eth__DOT__hdr_cnt;
    vlSelf->tb_top__DOT__u_eth__DOT__pre_cnt = __Vdly__tb_top__DOT__u_eth__DOT__pre_cnt;
}

void Vtb_top___024root___eval_nba(Vtb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___eval_nba\n"); );
    // Body
    if ((1ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vtb_top___024root___nba_sequent__TOP__0(vlSelf);
        vlSelf->__Vm_traceActivity[1U] = 1U;
    }
}

void Vtb_top___024root___eval_triggers__act(Vtb_top___024root* vlSelf);

bool Vtb_top___024root___eval_phase__act(Vtb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___eval_phase__act\n"); );
    // Init
    VlTriggerVec<1> __VpreTriggered;
    CData/*0:0*/ __VactExecute;
    // Body
    Vtb_top___024root___eval_triggers__act(vlSelf);
    __VactExecute = vlSelf->__VactTriggered.any();
    if (__VactExecute) {
        __VpreTriggered.andNot(vlSelf->__VactTriggered, vlSelf->__VnbaTriggered);
        vlSelf->__VnbaTriggered.thisOr(vlSelf->__VactTriggered);
        Vtb_top___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

bool Vtb_top___024root___eval_phase__nba(Vtb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___eval_phase__nba\n"); );
    // Init
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = vlSelf->__VnbaTriggered.any();
    if (__VnbaExecute) {
        Vtb_top___024root___eval_nba(vlSelf);
        vlSelf->__VnbaTriggered.clear();
    }
    return (__VnbaExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_top___024root___dump_triggers__ico(Vtb_top___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_top___024root___dump_triggers__nba(Vtb_top___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_top___024root___dump_triggers__act(Vtb_top___024root* vlSelf);
#endif  // VL_DEBUG

void Vtb_top___024root___eval(Vtb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___eval\n"); );
    // Init
    IData/*31:0*/ __VicoIterCount;
    CData/*0:0*/ __VicoContinue;
    IData/*31:0*/ __VnbaIterCount;
    CData/*0:0*/ __VnbaContinue;
    // Body
    __VicoIterCount = 0U;
    vlSelf->__VicoFirstIteration = 1U;
    __VicoContinue = 1U;
    while (__VicoContinue) {
        if (VL_UNLIKELY((0x64U < __VicoIterCount))) {
#ifdef VL_DEBUG
            Vtb_top___024root___dump_triggers__ico(vlSelf);
#endif
            VL_FATAL_MT("tb_top.sv", 3, "", "Input combinational region did not converge.");
        }
        __VicoIterCount = ((IData)(1U) + __VicoIterCount);
        __VicoContinue = 0U;
        if (Vtb_top___024root___eval_phase__ico(vlSelf)) {
            __VicoContinue = 1U;
        }
        vlSelf->__VicoFirstIteration = 0U;
    }
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        if (VL_UNLIKELY((0x64U < __VnbaIterCount))) {
#ifdef VL_DEBUG
            Vtb_top___024root___dump_triggers__nba(vlSelf);
#endif
            VL_FATAL_MT("tb_top.sv", 3, "", "NBA region did not converge.");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        __VnbaContinue = 0U;
        vlSelf->__VactIterCount = 0U;
        vlSelf->__VactContinue = 1U;
        while (vlSelf->__VactContinue) {
            if (VL_UNLIKELY((0x64U < vlSelf->__VactIterCount))) {
#ifdef VL_DEBUG
                Vtb_top___024root___dump_triggers__act(vlSelf);
#endif
                VL_FATAL_MT("tb_top.sv", 3, "", "Active region did not converge.");
            }
            vlSelf->__VactIterCount = ((IData)(1U) 
                                       + vlSelf->__VactIterCount);
            vlSelf->__VactContinue = 0U;
            if (Vtb_top___024root___eval_phase__act(vlSelf)) {
                vlSelf->__VactContinue = 1U;
            }
        }
        if (Vtb_top___024root___eval_phase__nba(vlSelf)) {
            __VnbaContinue = 1U;
        }
    }
}

#ifdef VL_DEBUG
void Vtb_top___024root___eval_debug_assertions(Vtb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((vlSelf->clk & 0xfeU))) {
        Verilated::overWidthError("clk");}
    if (VL_UNLIKELY((vlSelf->rst_n & 0xfeU))) {
        Verilated::overWidthError("rst_n");}
    if (VL_UNLIKELY((vlSelf->rx_valid & 0xfeU))) {
        Verilated::overWidthError("rx_valid");}
    if (VL_UNLIKELY((vlSelf->sink_allow & 0xfeU))) {
        Verilated::overWidthError("sink_allow");}
}
#endif  // VL_DEBUG

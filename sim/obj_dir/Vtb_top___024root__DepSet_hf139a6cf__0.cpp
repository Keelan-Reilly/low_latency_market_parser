// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_top.h for the primary calling header

#include "Vtb_top__pch.h"
#include "Vtb_top__Syms.h"
#include "Vtb_top___024root.h"

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_top___024root___dump_triggers__act(Vtb_top___024root* vlSelf);
#endif  // VL_DEBUG

void Vtb_top___024root___eval_triggers__act(Vtb_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___eval_triggers__act\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VactTriggered.setBit(0U, ((IData)(vlSelfRef.clk) 
                                          & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__clk__0))));
    vlSelfRef.__VactTriggered.setBit(1U, ((~ (IData)(vlSelfRef.rst_n)) 
                                          & (IData)(vlSelfRef.__Vtrigprevexpr___TOP__rst_n__0)));
    vlSelfRef.__Vtrigprevexpr___TOP__clk__0 = vlSelfRef.clk;
    vlSelfRef.__Vtrigprevexpr___TOP__rst_n__0 = vlSelfRef.rst_n;
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vtb_top___024root___dump_triggers__act(vlSelf);
    }
#endif
}

VL_INLINE_OPT void Vtb_top___024root___nba_sequent__TOP__0(Vtb_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___nba_sequent__TOP__0\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
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
    IData/*31:0*/ __Vdly__tb_top__DOT__u_eth__DOT__fcs_word;
    __Vdly__tb_top__DOT__u_eth__DOT__fcs_word = 0;
    IData/*31:0*/ __VdlyMask__tb_top__DOT__u_eth__DOT__fcs_word;
    __VdlyMask__tb_top__DOT__u_eth__DOT__fcs_word = 0;
    CData/*1:0*/ __Vdly__tb_top__DOT__u_pr__DOT__state;
    __Vdly__tb_top__DOT__u_pr__DOT__state = 0;
    SData/*15:0*/ __Vdly__tb_top__DOT__u_pr__DOT__cnt;
    __Vdly__tb_top__DOT__u_pr__DOT__cnt = 0;
    CData/*7:0*/ __Vdly__tb_top__DOT__u_pr__DOT__len_hi;
    __Vdly__tb_top__DOT__u_pr__DOT__len_hi = 0;
    CData/*7:0*/ __Vdly__tb_top__DOT__u_pr__DOT__len_lo;
    __Vdly__tb_top__DOT__u_pr__DOT__len_lo = 0;
    SData/*9:0*/ __Vdly__tb_top__DOT__u_ut__DOT__tick_cnt;
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
    __Vdly__cycle_cnt = vlSelfRef.cycle_cnt;
    __Vdly__tb_top__DOT__u_eth__DOT__state = vlSelfRef.tb_top__DOT__u_eth__DOT__state;
    __Vdly__tb_top__DOT__u_eth__DOT__crc_recv_shift 
        = vlSelfRef.tb_top__DOT__u_eth__DOT__crc_recv_shift;
    __Vdly__tb_top__DOT__u_eth__DOT__crc_cnt = vlSelfRef.tb_top__DOT__u_eth__DOT__crc_cnt;
    __Vdly__tb_top__DOT__u_eth__DOT__payload_len = vlSelfRef.tb_top__DOT__u_eth__DOT__payload_len;
    __Vdly__tb_top__DOT__u_eth__DOT__total_payload 
        = vlSelfRef.tb_top__DOT__u_eth__DOT__total_payload;
    __Vdly__tb_top__DOT__u_eth__DOT__crc_reg = vlSelfRef.tb_top__DOT__u_eth__DOT__crc_reg;
    __Vdly__tb_top__DOT__u_eth__DOT__hdr_cnt = vlSelfRef.tb_top__DOT__u_eth__DOT__hdr_cnt;
    __Vdly__tb_top__DOT__u_eth__DOT__pre_cnt = vlSelfRef.tb_top__DOT__u_eth__DOT__pre_cnt;
    __Vdly__tb_top__DOT__u_pr__DOT__state = vlSelfRef.tb_top__DOT__u_pr__DOT__state;
    __Vdly__tb_top__DOT__u_pr__DOT__cnt = vlSelfRef.tb_top__DOT__u_pr__DOT__cnt;
    __Vdly__tb_top__DOT__u_pr__DOT__len_hi = vlSelfRef.tb_top__DOT__u_pr__DOT__len_hi;
    __Vdly__tb_top__DOT__u_pr__DOT__len_lo = vlSelfRef.tb_top__DOT__u_pr__DOT__len_lo;
    __Vdly__tb_top__DOT__u_prg__DOT__l2t_data_valid 
        = vlSelfRef.tb_top__DOT__u_prg__DOT__l2t_data_valid;
    __Vdly__tb_top__DOT__u_ut__DOT__tick_cnt = vlSelfRef.tb_top__DOT__u_ut__DOT__tick_cnt;
    __Vdly__tb_top__DOT__u_ut__DOT__byte_idx = vlSelfRef.tb_top__DOT__u_ut__DOT__byte_idx;
    __Vdly__tb_top__DOT__u_ut__DOT__sh = vlSelfRef.tb_top__DOT__u_ut__DOT__sh;
    __Vdly__tb_top__DOT__u_ut__DOT__bit_idx = vlSelfRef.tb_top__DOT__u_ut__DOT__bit_idx;
    __Vdly__tb_top__DOT__u_ut__DOT__st = vlSelfRef.tb_top__DOT__u_ut__DOT__st;
    if (vlSelfRef.rst_n) {
        __Vdly__cycle_cnt = ((IData)(1U) + vlSelfRef.cycle_cnt);
        if (vlSelfRef.tb_top__DOT__parser_msg_start) {
            vlSelfRef.t_ingress = vlSelfRef.cycle_cnt;
        }
        if (vlSelfRef.field_valid) {
            vlSelfRef.t_parser = vlSelfRef.cycle_cnt;
            vlSelfRef.tb_top__DOT__u_prg__DOT__p2l_volume_reg 
                = vlSelfRef.volume;
        }
    } else {
        __Vdly__cycle_cnt = 0U;
        vlSelfRef.t_ingress = 0U;
        vlSelfRef.t_parser = 0U;
    }
    if (vlSelfRef.rst_n) {
        if ((2U & (IData)(vlSelfRef.tb_top__DOT__u_ut__DOT__st))) {
            if ((1U & (IData)(vlSelfRef.tb_top__DOT__u_ut__DOT__st))) {
                vlSelfRef.uart_tx = 1U;
                if ((0x363U == (IData)(vlSelfRef.tb_top__DOT__u_ut__DOT__tick_cnt))) {
                    __Vdly__tb_top__DOT__u_ut__DOT__tick_cnt = 0U;
                    if ((3U == (IData)(vlSelfRef.tb_top__DOT__u_ut__DOT__byte_idx))) {
                        __Vdly__tb_top__DOT__u_ut__DOT__st = 0U;
                    } else {
                        __Vdly__tb_top__DOT__u_ut__DOT__byte_idx 
                            = (3U & ((IData)(1U) + (IData)(vlSelfRef.tb_top__DOT__u_ut__DOT__byte_idx)));
                        __Vdly__tb_top__DOT__u_ut__DOT__sh 
                            = (0xffU & ((0U == (IData)(vlSelfRef.tb_top__DOT__u_ut__DOT__byte_idx))
                                         ? (vlSelfRef.tb_top__DOT__u_ut__DOT__word_reg 
                                            >> 8U) : 
                                        ((1U == (IData)(vlSelfRef.tb_top__DOT__u_ut__DOT__byte_idx))
                                          ? (vlSelfRef.tb_top__DOT__u_ut__DOT__word_reg 
                                             >> 0x10U)
                                          : ((2U == (IData)(vlSelfRef.tb_top__DOT__u_ut__DOT__byte_idx))
                                              ? (vlSelfRef.tb_top__DOT__u_ut__DOT__word_reg 
                                                 >> 0x18U)
                                              : 0U))));
                        __Vdly__tb_top__DOT__u_ut__DOT__st = 1U;
                        if ((1U & (~ VL_ONEHOT_I(((
                                                   (2U 
                                                    == (IData)(vlSelfRef.tb_top__DOT__u_ut__DOT__byte_idx)) 
                                                   << 2U) 
                                                  | (((1U 
                                                       == (IData)(vlSelfRef.tb_top__DOT__u_ut__DOT__byte_idx)) 
                                                      << 1U) 
                                                     | (0U 
                                                        == (IData)(vlSelfRef.tb_top__DOT__u_ut__DOT__byte_idx)))))))) {
                            if ((0U != (((2U == (IData)(vlSelfRef.tb_top__DOT__u_ut__DOT__byte_idx)) 
                                         << 2U) | (
                                                   ((1U 
                                                     == (IData)(vlSelfRef.tb_top__DOT__u_ut__DOT__byte_idx)) 
                                                    << 1U) 
                                                   | (0U 
                                                      == (IData)(vlSelfRef.tb_top__DOT__u_ut__DOT__byte_idx)))))) {
                                if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                                    VL_WRITEF_NX("[%0t] %%Error: uart_tx.sv:90: Assertion failed in %Ntb_top.u_ut: unique case, but multiple matches found for '2'h%x'\n",0,
                                                 64,
                                                 VL_TIME_UNITED_Q(1000),
                                                 -9,
                                                 vlSymsp->name(),
                                                 2,
                                                 (IData)(vlSelfRef.tb_top__DOT__u_ut__DOT__byte_idx));
                                    VL_STOP_MT("/Users/keelanreilly/Desktop/low_latency_fpga/tools/../hdl/uart_tx.sv", 90, "");
                                }
                            }
                        }
                    }
                } else {
                    __Vdly__tb_top__DOT__u_ut__DOT__tick_cnt 
                        = (0x3ffU & ((IData)(1U) + (IData)(vlSelfRef.tb_top__DOT__u_ut__DOT__tick_cnt)));
                }
            } else {
                vlSelfRef.uart_tx = (1U & (IData)(vlSelfRef.tb_top__DOT__u_ut__DOT__sh));
                if ((0x363U == (IData)(vlSelfRef.tb_top__DOT__u_ut__DOT__tick_cnt))) {
                    __Vdly__tb_top__DOT__u_ut__DOT__sh 
                        = (0x7fU & ((IData)(vlSelfRef.tb_top__DOT__u_ut__DOT__sh) 
                                    >> 1U));
                    __Vdly__tb_top__DOT__u_ut__DOT__bit_idx 
                        = (7U & ((IData)(1U) + (IData)(vlSelfRef.tb_top__DOT__u_ut__DOT__bit_idx)));
                    __Vdly__tb_top__DOT__u_ut__DOT__tick_cnt = 0U;
                    if ((7U == (IData)(vlSelfRef.tb_top__DOT__u_ut__DOT__bit_idx))) {
                        __Vdly__tb_top__DOT__u_ut__DOT__st = 3U;
                    }
                } else {
                    __Vdly__tb_top__DOT__u_ut__DOT__tick_cnt 
                        = (0x3ffU & ((IData)(1U) + (IData)(vlSelfRef.tb_top__DOT__u_ut__DOT__tick_cnt)));
                }
            }
        } else if ((1U & (IData)(vlSelfRef.tb_top__DOT__u_ut__DOT__st))) {
            vlSelfRef.uart_tx = 0U;
            if ((0x363U == (IData)(vlSelfRef.tb_top__DOT__u_ut__DOT__tick_cnt))) {
                __Vdly__tb_top__DOT__u_ut__DOT__tick_cnt = 0U;
                __Vdly__tb_top__DOT__u_ut__DOT__bit_idx = 0U;
                __Vdly__tb_top__DOT__u_ut__DOT__st = 2U;
            } else {
                __Vdly__tb_top__DOT__u_ut__DOT__tick_cnt 
                    = (0x3ffU & ((IData)(1U) + (IData)(vlSelfRef.tb_top__DOT__u_ut__DOT__tick_cnt)));
            }
        } else {
            vlSelfRef.uart_tx = 1U;
            __Vdly__tb_top__DOT__u_ut__DOT__tick_cnt = 0U;
            __Vdly__tb_top__DOT__u_ut__DOT__bit_idx = 0U;
            __Vdly__tb_top__DOT__u_ut__DOT__byte_idx = 0U;
            if (vlSelfRef.tb_top__DOT__u_ut__DOT__accept) {
                vlSelfRef.tb_top__DOT__u_ut__DOT__word_reg 
                    = vlSelfRef.tb_top__DOT__u_prg__DOT__l2t_data_reg;
                __Vdly__tb_top__DOT__u_ut__DOT__sh 
                    = (0xffU & vlSelfRef.tb_top__DOT__u_prg__DOT__l2t_data_reg);
                __Vdly__tb_top__DOT__u_ut__DOT__st = 1U;
            }
        }
    } else {
        __Vdly__tb_top__DOT__u_ut__DOT__st = 0U;
        vlSelfRef.uart_tx = 1U;
        __Vdly__tb_top__DOT__u_ut__DOT__tick_cnt = 0U;
        __Vdly__tb_top__DOT__u_ut__DOT__byte_idx = 0U;
        __Vdly__tb_top__DOT__u_ut__DOT__bit_idx = 0U;
        __Vdly__tb_top__DOT__u_ut__DOT__sh = 0U;
        vlSelfRef.tb_top__DOT__u_ut__DOT__word_reg = 0U;
    }
    vlSelfRef.tb_top__DOT__u_ut__DOT__tick_cnt = __Vdly__tb_top__DOT__u_ut__DOT__tick_cnt;
    vlSelfRef.tb_top__DOT__u_ut__DOT__byte_idx = __Vdly__tb_top__DOT__u_ut__DOT__byte_idx;
    vlSelfRef.tb_top__DOT__u_ut__DOT__sh = __Vdly__tb_top__DOT__u_ut__DOT__sh;
    vlSelfRef.tb_top__DOT__u_ut__DOT__bit_idx = __Vdly__tb_top__DOT__u_ut__DOT__bit_idx;
    vlSelfRef.parsed_volume_reg = vlSelfRef.tb_top__DOT__u_prg__DOT__p2l_volume_reg;
    if (vlSelfRef.rst_n) {
        if (((0U == (IData)(vlSelfRef.tb_top__DOT__u_ut__DOT__st)) 
             & (IData)(vlSelfRef.tb_top__DOT__u_prg__DOT__l2t_data_valid))) {
            __Vdly__tb_top__DOT__u_prg__DOT__l2t_data_valid = 0U;
        }
        if ((((~ (IData)(vlSelfRef.tb_top__DOT__u_prg__DOT__l2t_data_valid)) 
              | (0U == (IData)(vlSelfRef.tb_top__DOT__u_ut__DOT__st))) 
             & (IData)(vlSelfRef.decision_valid))) {
            vlSelfRef.tb_top__DOT__u_prg__DOT__l2t_data_reg 
                = vlSelfRef.tb_top__DOT__decision_data;
            __Vdly__tb_top__DOT__u_prg__DOT__l2t_data_valid = 1U;
            vlSelfRef.t_logic = vlSelfRef.cycle_cnt;
            vlSelfRef.t_decision = vlSelfRef.cycle_cnt;
        }
    } else {
        __Vdly__tb_top__DOT__u_prg__DOT__l2t_data_valid = 0U;
        vlSelfRef.t_logic = 0U;
        vlSelfRef.t_decision = 0U;
    }
    vlSelfRef.cycle_cnt = __Vdly__cycle_cnt;
    vlSelfRef.tb_top__DOT__u_ut__DOT__st = __Vdly__tb_top__DOT__u_ut__DOT__st;
    vlSelfRef.tb_top__DOT__u_prg__DOT__l2t_data_valid 
        = __Vdly__tb_top__DOT__u_prg__DOT__l2t_data_valid;
    vlSelfRef.tx_word_data = vlSelfRef.tb_top__DOT__u_prg__DOT__l2t_data_reg;
    vlSelfRef.tx_word_valid = ((IData)(vlSelfRef.tb_top__DOT__u_prg__DOT__l2t_data_valid) 
                               & (0U == (IData)(vlSelfRef.tb_top__DOT__u_ut__DOT__st)));
    vlSelfRef.tb_top__DOT__u_ut__DOT__accept = ((0U 
                                                 == (IData)(vlSelfRef.tb_top__DOT__u_ut__DOT__st)) 
                                                & (IData)(vlSelfRef.tb_top__DOT__u_prg__DOT__l2t_data_valid));
    vlSelfRef.decision_valid = ((IData)(vlSelfRef.rst_n) 
                                && (((IData)(vlSelfRef.tb_top__DOT__u_prg__DOT__p2l_data_valid) 
                                     & (0x50U == (IData)(vlSelfRef.tb_top__DOT__u_prg__DOT__p2l_type_reg))) 
                                    & (0x1e8480U > vlSelfRef.tb_top__DOT__u_prg__DOT__p2l_price_reg)));
    if (vlSelfRef.rst_n) {
        if ((((IData)(vlSelfRef.tb_top__DOT__u_prg__DOT__p2l_data_valid) 
              & (0x50U == (IData)(vlSelfRef.tb_top__DOT__u_prg__DOT__p2l_type_reg))) 
             & (0x1e8480U > vlSelfRef.tb_top__DOT__u_prg__DOT__p2l_price_reg))) {
            vlSelfRef.tb_top__DOT__decision_data = vlSelfRef.tb_top__DOT__u_prg__DOT__p2l_price_reg;
        }
    } else {
        vlSelfRef.tb_top__DOT__decision_data = 0U;
    }
    vlSelfRef.tb_top__DOT__u_prg__DOT__p2l_data_valid 
        = ((IData)(vlSelfRef.rst_n) && (IData)(vlSelfRef.field_valid));
    vlSelfRef.parsed_valid_reg = vlSelfRef.tb_top__DOT__u_prg__DOT__p2l_data_valid;
    if (vlSelfRef.rst_n) {
        if (vlSelfRef.field_valid) {
            vlSelfRef.tb_top__DOT__u_prg__DOT__p2l_price_reg 
                = vlSelfRef.price;
            vlSelfRef.tb_top__DOT__u_prg__DOT__p2l_type_reg 
                = vlSelfRef.msg_type;
        }
        vlSelfRef.parsed_price_reg = vlSelfRef.tb_top__DOT__u_prg__DOT__p2l_price_reg;
        vlSelfRef.parsed_type_reg = vlSelfRef.tb_top__DOT__u_prg__DOT__p2l_type_reg;
        vlSelfRef.field_valid = 0U;
        vlSelfRef.tb_top__DOT__parser_msg_start = 0U;
        if ((2U & (IData)(vlSelfRef.tb_top__DOT__u_pr__DOT__state))) {
            if ((1U & (IData)(vlSelfRef.tb_top__DOT__u_pr__DOT__state))) {
                if (vlSelfRef.tb_top__DOT__u_prg__DOT__rx2p_data_valid) {
                    if ((((IData)(1U) + (IData)(vlSelfRef.tb_top__DOT__u_pr__DOT__cnt)) 
                         == (IData)(vlSelfRef.tb_top__DOT__u_pr__DOT__body_left))) {
                        __Vdly__tb_top__DOT__u_pr__DOT__state = 0U;
                        __Vdly__tb_top__DOT__u_pr__DOT__cnt = 0U;
                    } else {
                        __Vdly__tb_top__DOT__u_pr__DOT__cnt 
                            = (0xffffU & ((IData)(1U) 
                                          + (IData)(vlSelfRef.tb_top__DOT__u_pr__DOT__cnt)));
                    }
                }
            } else {
                vlSelfRef.field_valid = 1U;
                vlSelfRef.msg_type = vlSelfRef.tb_top__DOT__u_pr__DOT__type_reg;
                __Vdly__tb_top__DOT__u_pr__DOT__state = 0U;
            }
        } else if ((1U & (IData)(vlSelfRef.tb_top__DOT__u_pr__DOT__state))) {
            if (vlSelfRef.tb_top__DOT__u_prg__DOT__rx2p_data_valid) {
                if (((0xaU <= (IData)(vlSelfRef.tb_top__DOT__u_pr__DOT__cnt)) 
                     & (0x11U >= (IData)(vlSelfRef.tb_top__DOT__u_pr__DOT__cnt)))) {
                    vlSelfRef.order_id = (VL_SHIFTL_QQI(64,64,32, vlSelfRef.order_id, 8U) 
                                          | (QData)((IData)(vlSelfRef.tb_top__DOT__u_prg__DOT__rx2p_data)));
                }
                if (((0x13U <= (IData)(vlSelfRef.tb_top__DOT__u_pr__DOT__cnt)) 
                     & (0x16U >= (IData)(vlSelfRef.tb_top__DOT__u_pr__DOT__cnt)))) {
                    vlSelfRef.volume = (VL_SHIFTL_III(32,32,32, vlSelfRef.volume, 8U) 
                                        | (IData)(vlSelfRef.tb_top__DOT__u_prg__DOT__rx2p_data));
                }
                if (((0x1fU <= (IData)(vlSelfRef.tb_top__DOT__u_pr__DOT__cnt)) 
                     & (0x22U >= (IData)(vlSelfRef.tb_top__DOT__u_pr__DOT__cnt)))) {
                    vlSelfRef.price = (VL_SHIFTL_III(32,32,32, vlSelfRef.price, 8U) 
                                       | (IData)(vlSelfRef.tb_top__DOT__u_prg__DOT__rx2p_data));
                }
                if ((((IData)(1U) + (IData)(vlSelfRef.tb_top__DOT__u_pr__DOT__cnt)) 
                     == (IData)(vlSelfRef.tb_top__DOT__u_pr__DOT__body_left))) {
                    __Vdly__tb_top__DOT__u_pr__DOT__state = 2U;
                    __Vdly__tb_top__DOT__u_pr__DOT__cnt = 0U;
                } else {
                    __Vdly__tb_top__DOT__u_pr__DOT__cnt 
                        = (0xffffU & ((IData)(1U) + (IData)(vlSelfRef.tb_top__DOT__u_pr__DOT__cnt)));
                }
            }
        } else if (vlSelfRef.tb_top__DOT__u_prg__DOT__rx2p_data_valid) {
            if ((0U == (IData)(vlSelfRef.tb_top__DOT__u_pr__DOT__cnt))) {
                vlSelfRef.tb_top__DOT__parser_msg_start = 1U;
                __Vdly__tb_top__DOT__u_pr__DOT__len_hi 
                    = vlSelfRef.tb_top__DOT__u_prg__DOT__rx2p_data;
                __Vdly__tb_top__DOT__u_pr__DOT__cnt = 1U;
            } else if ((1U == (IData)(vlSelfRef.tb_top__DOT__u_pr__DOT__cnt))) {
                __Vdly__tb_top__DOT__u_pr__DOT__len_lo 
                    = vlSelfRef.tb_top__DOT__u_prg__DOT__rx2p_data;
                __Vdly__tb_top__DOT__u_pr__DOT__cnt = 2U;
            } else if ((2U == (IData)(vlSelfRef.tb_top__DOT__u_pr__DOT__cnt))) {
                vlSelfRef.tb_top__DOT__u_pr__DOT__type_reg 
                    = vlSelfRef.tb_top__DOT__u_prg__DOT__rx2p_data;
                vlSelfRef.tb_top__DOT__u_pr__DOT__body_left 
                    = (0xffffU & ((((IData)(vlSelfRef.tb_top__DOT__u_pr__DOT__len_hi) 
                                    << 8U) | (IData)(vlSelfRef.tb_top__DOT__u_pr__DOT__len_lo)) 
                                  - (IData)(1U)));
                __Vdly__tb_top__DOT__u_pr__DOT__cnt = 0U;
                vlSelfRef.order_id = 0ULL;
                vlSelfRef.price = 0U;
                vlSelfRef.volume = 0U;
                __Vdly__tb_top__DOT__u_pr__DOT__state 
                    = ((0x50U == (IData)(vlSelfRef.tb_top__DOT__u_prg__DOT__rx2p_data))
                        ? 1U : 3U);
            }
        }
    } else {
        vlSelfRef.parsed_price_reg = vlSelfRef.tb_top__DOT__u_prg__DOT__p2l_price_reg;
        vlSelfRef.parsed_type_reg = vlSelfRef.tb_top__DOT__u_prg__DOT__p2l_type_reg;
        vlSelfRef.tb_top__DOT__parser_msg_start = 0U;
        __Vdly__tb_top__DOT__u_pr__DOT__state = 0U;
        __Vdly__tb_top__DOT__u_pr__DOT__len_hi = 0U;
        __Vdly__tb_top__DOT__u_pr__DOT__len_lo = 0U;
        vlSelfRef.tb_top__DOT__u_pr__DOT__type_reg = 0U;
        __Vdly__tb_top__DOT__u_pr__DOT__cnt = 0U;
        vlSelfRef.tb_top__DOT__u_pr__DOT__body_left = 0U;
        vlSelfRef.field_valid = 0U;
        vlSelfRef.msg_type = 0U;
        vlSelfRef.order_id = 0ULL;
        vlSelfRef.price = 0U;
        vlSelfRef.volume = 0U;
    }
    vlSelfRef.tb_top__DOT__u_pr__DOT__state = __Vdly__tb_top__DOT__u_pr__DOT__state;
    vlSelfRef.tb_top__DOT__u_pr__DOT__cnt = __Vdly__tb_top__DOT__u_pr__DOT__cnt;
    vlSelfRef.tb_top__DOT__u_pr__DOT__len_hi = __Vdly__tb_top__DOT__u_pr__DOT__len_hi;
    vlSelfRef.tb_top__DOT__u_pr__DOT__len_lo = __Vdly__tb_top__DOT__u_pr__DOT__len_lo;
    vlSelfRef.tb_top__DOT__u_prg__DOT__rx2p_data_valid 
        = ((IData)(vlSelfRef.rst_n) && (IData)(vlSelfRef.payload_valid));
    if (vlSelfRef.rst_n) {
        if (vlSelfRef.payload_valid) {
            vlSelfRef.tb_top__DOT__u_prg__DOT__rx2p_data 
                = vlSelfRef.payload_byte;
        }
    }
    if (vlSelfRef.rst_n) {
        vlSelfRef.payload_valid = 0U;
        vlSelfRef.eth_crc_valid = 0U;
        if ((4U & (IData)(vlSelfRef.tb_top__DOT__u_eth__DOT__state))) {
            if ((2U & (IData)(vlSelfRef.tb_top__DOT__u_eth__DOT__state))) {
                __Vdly__tb_top__DOT__u_eth__DOT__state = 0U;
            } else if ((1U & (IData)(vlSelfRef.tb_top__DOT__u_eth__DOT__state))) {
                if (vlSelfRef.rx_valid) {
                    if ((0U == (IData)(vlSelfRef.tb_top__DOT__u_eth__DOT__crc_cnt))) {
                        __Vdly__tb_top__DOT__u_eth__DOT__crc_recv_shift 
                            = ((0xffffff00U & __Vdly__tb_top__DOT__u_eth__DOT__crc_recv_shift) 
                               | (IData)(vlSelfRef.rx_byte));
                        __Vdly__tb_top__DOT__u_eth__DOT__crc_cnt = 1U;
                    } else if ((1U == (IData)(vlSelfRef.tb_top__DOT__u_eth__DOT__crc_cnt))) {
                        __Vdly__tb_top__DOT__u_eth__DOT__crc_recv_shift 
                            = ((0xffff00ffU & __Vdly__tb_top__DOT__u_eth__DOT__crc_recv_shift) 
                               | ((IData)(vlSelfRef.rx_byte) 
                                  << 8U));
                        __Vdly__tb_top__DOT__u_eth__DOT__crc_cnt = 2U;
                    } else if ((2U == (IData)(vlSelfRef.tb_top__DOT__u_eth__DOT__crc_cnt))) {
                        __Vdly__tb_top__DOT__u_eth__DOT__crc_recv_shift 
                            = ((0xff00ffffU & __Vdly__tb_top__DOT__u_eth__DOT__crc_recv_shift) 
                               | ((IData)(vlSelfRef.rx_byte) 
                                  << 0x10U));
                        __Vdly__tb_top__DOT__u_eth__DOT__crc_cnt = 3U;
                    } else if ((3U == (IData)(vlSelfRef.tb_top__DOT__u_eth__DOT__crc_cnt))) {
                        vlSelfRef.tb_top__DOT__u_eth__DOT__fcs_word 
                            = (((IData)(vlSelfRef.rx_byte) 
                                << 0x18U) | (0xffffffU 
                                             & vlSelfRef.tb_top__DOT__u_eth__DOT__crc_recv_shift));
                        vlSelfRef.dbg_crc_calc = (~ vlSelfRef.tb_top__DOT__u_eth__DOT__crc_reg);
                        vlSelfRef.dbg_crc_recv = vlSelfRef.tb_top__DOT__u_eth__DOT__fcs_word;
                        vlSelfRef.eth_crc_valid = 1U;
                        __Vdly__tb_top__DOT__u_eth__DOT__state = 0U;
                        __Vdly__tb_top__DOT__u_eth__DOT__crc_cnt = 0U;
                        vlSelfRef.eth_crc_ok = ((~ vlSelfRef.tb_top__DOT__u_eth__DOT__crc_reg) 
                                                == vlSelfRef.tb_top__DOT__u_eth__DOT__fcs_word);
                    }
                    if ((1U & (~ VL_ONEHOT_I(((((3U 
                                                 == (IData)(vlSelfRef.tb_top__DOT__u_eth__DOT__crc_cnt)) 
                                                << 3U) 
                                               | ((2U 
                                                   == (IData)(vlSelfRef.tb_top__DOT__u_eth__DOT__crc_cnt)) 
                                                  << 2U)) 
                                              | (((1U 
                                                   == (IData)(vlSelfRef.tb_top__DOT__u_eth__DOT__crc_cnt)) 
                                                  << 1U) 
                                                 | (0U 
                                                    == (IData)(vlSelfRef.tb_top__DOT__u_eth__DOT__crc_cnt)))))))) {
                        if ((0U == ((((3U == (IData)(vlSelfRef.tb_top__DOT__u_eth__DOT__crc_cnt)) 
                                      << 3U) | ((2U 
                                                 == (IData)(vlSelfRef.tb_top__DOT__u_eth__DOT__crc_cnt)) 
                                                << 2U)) 
                                    | (((1U == (IData)(vlSelfRef.tb_top__DOT__u_eth__DOT__crc_cnt)) 
                                        << 1U) | (0U 
                                                  == (IData)(vlSelfRef.tb_top__DOT__u_eth__DOT__crc_cnt)))))) {
                            if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                                VL_WRITEF_NX("[%0t] %%Error: eth_rx.sv:209: Assertion failed in %Ntb_top.u_eth: unique case, but none matched for '32'h%x'\n",0,
                                             64,VL_TIME_UNITED_Q(1000),
                                             -9,vlSymsp->name(),
                                             32,(IData)(vlSelfRef.tb_top__DOT__u_eth__DOT__crc_cnt));
                                VL_STOP_MT("/Users/keelanreilly/Desktop/low_latency_fpga/tools/../hdl/eth_rx.sv", 209, "");
                            }
                        } else if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                            VL_WRITEF_NX("[%0t] %%Error: eth_rx.sv:209: Assertion failed in %Ntb_top.u_eth: unique case, but multiple matches found for '32'h%x'\n",0,
                                         64,VL_TIME_UNITED_Q(1000),
                                         -9,vlSymsp->name(),
                                         32,(IData)(vlSelfRef.tb_top__DOT__u_eth__DOT__crc_cnt));
                            VL_STOP_MT("/Users/keelanreilly/Desktop/low_latency_fpga/tools/../hdl/eth_rx.sv", 209, "");
                        }
                    }
                }
            } else if (vlSelfRef.rx_valid) {
                __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__0__data_byte 
                    = vlSelfRef.rx_byte;
                __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__0__crc_in 
                    = vlSelfRef.tb_top__DOT__u_eth__DOT__crc_reg;
                __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__0__c 
                    = (__Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__0__crc_in 
                       ^ (IData)(__Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__0__data_byte));
                if ((0U == (IData)(vlSelfRef.tb_top__DOT__u_eth__DOT__payload_cnt))) {
                    __Vdly__tb_top__DOT__u_eth__DOT__payload_len 
                        = ((0xffU & (IData)(__Vdly__tb_top__DOT__u_eth__DOT__payload_len)) 
                           | ((IData)(vlSelfRef.rx_byte) 
                              << 8U));
                } else if ((1U == (IData)(vlSelfRef.tb_top__DOT__u_eth__DOT__payload_cnt))) {
                    __Vdly__tb_top__DOT__u_eth__DOT__total_payload 
                        = (0xffffU & ((IData)(2U) + 
                                      ((0xff00U & (IData)(vlSelfRef.tb_top__DOT__u_eth__DOT__payload_len)) 
                                       | (IData)(vlSelfRef.rx_byte))));
                    vlSelfRef.dbg_payload_len = ((0xff00U 
                                                  & (IData)(vlSelfRef.tb_top__DOT__u_eth__DOT__payload_len)) 
                                                 | (IData)(vlSelfRef.rx_byte));
                    vlSelfRef.dbg_total_payload = (0xffffU 
                                                   & ((IData)(2U) 
                                                      + 
                                                      ((0xff00U 
                                                        & (IData)(vlSelfRef.tb_top__DOT__u_eth__DOT__payload_len)) 
                                                       | (IData)(vlSelfRef.rx_byte))));
                    __Vdly__tb_top__DOT__u_eth__DOT__payload_len 
                        = ((0xff00U & (IData)(__Vdly__tb_top__DOT__u_eth__DOT__payload_len)) 
                           | (IData)(vlSelfRef.rx_byte));
                }
                if (vlSelfRef.tb_top__DOT__u_eth__DOT__mac_match) {
                    vlSelfRef.payload_byte = vlSelfRef.rx_byte;
                    vlSelfRef.payload_valid = 1U;
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
                if (((0xffffU & ((IData)(1U) + (IData)(vlSelfRef.tb_top__DOT__u_eth__DOT__payload_cnt))) 
                     == (IData)(vlSelfRef.tb_top__DOT__u_eth__DOT__total_payload))) {
                    __Vdly__tb_top__DOT__u_eth__DOT__crc_cnt = 0U;
                    __Vdly__tb_top__DOT__u_eth__DOT__crc_recv_shift = 0U;
                    vlSelfRef.dbg_payload_cnt_last 
                        = (0xffffU & ((IData)(1U) + (IData)(vlSelfRef.tb_top__DOT__u_eth__DOT__payload_cnt)));
                    __Vdly__tb_top__DOT__u_eth__DOT__state = 5U;
                }
                vlSelfRef.tb_top__DOT__u_eth__DOT__payload_cnt 
                    = (0xffffU & ((IData)(1U) + (IData)(vlSelfRef.tb_top__DOT__u_eth__DOT__payload_cnt)));
                __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__0__Vfuncout 
                    = __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__0__c;
                vlSelfRef.tb_top__DOT__u_eth__DOT__next_crc 
                    = __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__0__Vfuncout;
                __Vdly__tb_top__DOT__u_eth__DOT__crc_reg 
                    = vlSelfRef.tb_top__DOT__u_eth__DOT__next_crc;
            }
        } else if ((2U & (IData)(vlSelfRef.tb_top__DOT__u_eth__DOT__state))) {
            if ((1U & (IData)(vlSelfRef.tb_top__DOT__u_eth__DOT__state))) {
                if (vlSelfRef.rx_valid) {
                    __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__1__data_byte 
                        = vlSelfRef.rx_byte;
                    __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__1__crc_in 
                        = vlSelfRef.tb_top__DOT__u_eth__DOT__crc_reg;
                    __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__1__c 
                        = (__Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__1__crc_in 
                           ^ (IData)(__Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__1__data_byte));
                    if ((6U > (IData)(vlSelfRef.tb_top__DOT__u_eth__DOT__hdr_cnt))) {
                        vlSelfRef.tb_top__DOT__u_eth__DOT__unnamedblk2__DOT__full_dest 
                            = ((0xffffffffff00ULL & 
                                (vlSelfRef.tb_top__DOT__u_eth__DOT__dest_mac_shift 
                                 << 8U)) | (QData)((IData)(vlSelfRef.rx_byte)));
                        vlSelfRef.tb_top__DOT__u_eth__DOT__dest_mac_shift 
                            = vlSelfRef.tb_top__DOT__u_eth__DOT__unnamedblk2__DOT__full_dest;
                        if ((5U == (IData)(vlSelfRef.tb_top__DOT__u_eth__DOT__hdr_cnt))) {
                            vlSelfRef.tb_top__DOT__u_eth__DOT__this_cycle_match 
                                = ((0x1122334455ULL 
                                    == vlSelfRef.tb_top__DOT__u_eth__DOT__unnamedblk2__DOT__full_dest) 
                                   | (0xffffffffffffULL 
                                      == vlSelfRef.tb_top__DOT__u_eth__DOT__unnamedblk2__DOT__full_dest));
                            vlSelfRef.tb_top__DOT__u_eth__DOT__mac_match 
                                = vlSelfRef.tb_top__DOT__u_eth__DOT__this_cycle_match;
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
                        = (0xffffU & ((IData)(1U) + (IData)(vlSelfRef.tb_top__DOT__u_eth__DOT__hdr_cnt)));
                    if ((0xdU == (IData)(vlSelfRef.tb_top__DOT__u_eth__DOT__hdr_cnt))) {
                        __Vdly__tb_top__DOT__u_eth__DOT__state = 4U;
                        vlSelfRef.tb_top__DOT__u_eth__DOT__payload_cnt = 0U;
                    }
                    __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__1__Vfuncout 
                        = __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__1__c;
                    vlSelfRef.tb_top__DOT__u_eth__DOT__next_crc 
                        = __Vfunc_tb_top__DOT__u_eth__DOT__crc32_lsbf__1__Vfuncout;
                    __Vdly__tb_top__DOT__u_eth__DOT__crc_reg 
                        = vlSelfRef.tb_top__DOT__u_eth__DOT__next_crc;
                }
            } else if (vlSelfRef.rx_valid) {
                if ((0xd5U == (IData)(vlSelfRef.rx_byte))) {
                    __Vdly__tb_top__DOT__u_eth__DOT__crc_reg = 0xffffffffU;
                    __Vdly__tb_top__DOT__u_eth__DOT__crc_recv_shift = 0U;
                    __Vdly__tb_top__DOT__u_eth__DOT__crc_cnt = 0U;
                    __Vdly__tb_top__DOT__u_eth__DOT__state = 3U;
                    __Vdly__tb_top__DOT__u_eth__DOT__hdr_cnt = 0U;
                    vlSelfRef.tb_top__DOT__u_eth__DOT__dest_mac_shift = 0ULL;
                    vlSelfRef.tb_top__DOT__u_eth__DOT__mac_match = 0U;
                } else {
                    __Vdly__tb_top__DOT__u_eth__DOT__state = 0U;
                }
            }
        } else if ((1U & (IData)(vlSelfRef.tb_top__DOT__u_eth__DOT__state))) {
            if (vlSelfRef.rx_valid) {
                if ((0x55U == (IData)(vlSelfRef.rx_byte))) {
                    __Vdly__tb_top__DOT__u_eth__DOT__pre_cnt 
                        = (7U & ((IData)(1U) + (IData)(vlSelfRef.tb_top__DOT__u_eth__DOT__pre_cnt)));
                    if ((6U == (IData)(vlSelfRef.tb_top__DOT__u_eth__DOT__pre_cnt))) {
                        __Vdly__tb_top__DOT__u_eth__DOT__state = 2U;
                    }
                } else {
                    __Vdly__tb_top__DOT__u_eth__DOT__state = 0U;
                    __Vdly__tb_top__DOT__u_eth__DOT__pre_cnt = 0U;
                }
            }
        } else if (((IData)(vlSelfRef.rx_valid) & (0x55U 
                                                   == (IData)(vlSelfRef.rx_byte)))) {
            __Vdly__tb_top__DOT__u_eth__DOT__state = 1U;
            __Vdly__tb_top__DOT__u_eth__DOT__pre_cnt = 1U;
        }
    } else {
        __Vdly__tb_top__DOT__u_eth__DOT__state = 0U;
        __Vdly__tb_top__DOT__u_eth__DOT__pre_cnt = 0U;
        __Vdly__tb_top__DOT__u_eth__DOT__hdr_cnt = 0U;
        vlSelfRef.tb_top__DOT__u_eth__DOT__payload_cnt = 0U;
        __Vdly__tb_top__DOT__u_eth__DOT__payload_len = 0U;
        vlSelfRef.tb_top__DOT__u_eth__DOT__mac_match = 0U;
        vlSelfRef.payload_valid = 0U;
        __Vdly__tb_top__DOT__u_eth__DOT__crc_cnt = 0U;
        vlSelfRef.tb_top__DOT__u_eth__DOT__dest_mac_shift = 0ULL;
        __Vdly__tb_top__DOT__u_eth__DOT__crc_reg = 0xffffffffU;
        __Vdly__tb_top__DOT__u_eth__DOT__crc_recv_shift = 0U;
        vlSelfRef.eth_crc_ok = 0U;
        vlSelfRef.eth_crc_valid = 0U;
        __Vdly__tb_top__DOT__u_eth__DOT__fcs_word = 0U;
        __VdlyMask__tb_top__DOT__u_eth__DOT__fcs_word = 0xffffffffU;
        __Vdly__tb_top__DOT__u_eth__DOT__total_payload = 0U;
        vlSelfRef.dbg_crc_calc = 0U;
        vlSelfRef.dbg_crc_recv = 0U;
        vlSelfRef.dbg_payload_len = 0U;
        vlSelfRef.dbg_total_payload = 0U;
        vlSelfRef.dbg_payload_cnt_last = 0U;
    }
    vlSelfRef.tb_top__DOT__u_eth__DOT__state = __Vdly__tb_top__DOT__u_eth__DOT__state;
    vlSelfRef.tb_top__DOT__u_eth__DOT__crc_recv_shift 
        = __Vdly__tb_top__DOT__u_eth__DOT__crc_recv_shift;
    vlSelfRef.tb_top__DOT__u_eth__DOT__crc_cnt = __Vdly__tb_top__DOT__u_eth__DOT__crc_cnt;
    vlSelfRef.tb_top__DOT__u_eth__DOT__payload_len 
        = __Vdly__tb_top__DOT__u_eth__DOT__payload_len;
    vlSelfRef.tb_top__DOT__u_eth__DOT__total_payload 
        = __Vdly__tb_top__DOT__u_eth__DOT__total_payload;
    vlSelfRef.tb_top__DOT__u_eth__DOT__crc_reg = __Vdly__tb_top__DOT__u_eth__DOT__crc_reg;
    vlSelfRef.tb_top__DOT__u_eth__DOT__hdr_cnt = __Vdly__tb_top__DOT__u_eth__DOT__hdr_cnt;
    vlSelfRef.tb_top__DOT__u_eth__DOT__pre_cnt = __Vdly__tb_top__DOT__u_eth__DOT__pre_cnt;
    vlSelfRef.tb_top__DOT__u_eth__DOT__fcs_word = (
                                                   (__Vdly__tb_top__DOT__u_eth__DOT__fcs_word 
                                                    & __VdlyMask__tb_top__DOT__u_eth__DOT__fcs_word) 
                                                   | (vlSelfRef.tb_top__DOT__u_eth__DOT__fcs_word 
                                                      & (~ __VdlyMask__tb_top__DOT__u_eth__DOT__fcs_word)));
    __VdlyMask__tb_top__DOT__u_eth__DOT__fcs_word = 0U;
}

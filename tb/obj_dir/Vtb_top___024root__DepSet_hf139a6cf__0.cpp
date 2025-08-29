// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_top.h for the primary calling header

#include "Vtb_top__pch.h"
#include "Vtb_top__Syms.h"
#include "Vtb_top___024root.h"

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_top___024root___dump_triggers__ico(Vtb_top___024root* vlSelf);
#endif  // VL_DEBUG

void Vtb_top___024root___eval_triggers__ico(Vtb_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root___eval_triggers__ico\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VicoTriggered.setBit(0U, (IData)(vlSelfRef.__VicoFirstIteration));
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vtb_top___024root___dump_triggers__ico(vlSelf);
    }
#endif
}

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
    CData/*0:0*/ __Vdly__tb_top__DOT__u_prg__DOT__s3__DOT__saved_valid;
    __Vdly__tb_top__DOT__u_prg__DOT__s3__DOT__saved_valid = 0;
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
    CData/*7:0*/ __Vdly__tb_top__DOT__u_pr__DOT__len_hi;
    __Vdly__tb_top__DOT__u_pr__DOT__len_hi = 0;
    SData/*15:0*/ __Vdly__tb_top__DOT__u_pr__DOT__cnt;
    __Vdly__tb_top__DOT__u_pr__DOT__cnt = 0;
    CData/*7:0*/ __Vdly__tb_top__DOT__u_pr__DOT__len_lo;
    __Vdly__tb_top__DOT__u_pr__DOT__len_lo = 0;
    CData/*7:0*/ __Vdly__tb_top__DOT__u_pr__DOT__type_reg;
    __Vdly__tb_top__DOT__u_pr__DOT__type_reg = 0;
    QData/*63:0*/ __Vdly__order_id;
    __Vdly__order_id = 0;
    IData/*31:0*/ __Vdly__price;
    __Vdly__price = 0;
    IData/*31:0*/ __Vdly__volume;
    __Vdly__volume = 0;
    CData/*1:0*/ __Vdly__tb_top__DOT__u_pr__DOT__state;
    __Vdly__tb_top__DOT__u_pr__DOT__state = 0;
    SData/*15:0*/ __Vdly__tb_top__DOT__u_pr__DOT__body_left;
    __Vdly__tb_top__DOT__u_pr__DOT__body_left = 0;
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
    __Vdly__tb_top__DOT__u_ut__DOT__tick_cnt = vlSelfRef.tb_top__DOT__u_ut__DOT__tick_cnt;
    __Vdly__tb_top__DOT__u_ut__DOT__byte_idx = vlSelfRef.tb_top__DOT__u_ut__DOT__byte_idx;
    __Vdly__tb_top__DOT__u_ut__DOT__sh = vlSelfRef.tb_top__DOT__u_ut__DOT__sh;
    __Vdly__tb_top__DOT__u_ut__DOT__bit_idx = vlSelfRef.tb_top__DOT__u_ut__DOT__bit_idx;
    __Vdly__tb_top__DOT__u_ut__DOT__st = vlSelfRef.tb_top__DOT__u_ut__DOT__st;
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
    __Vdly__tb_top__DOT__u_prg__DOT__s3__DOT__saved_valid 
        = vlSelfRef.tb_top__DOT__u_prg__DOT__s3__DOT__saved_valid;
    __Vdly__tb_top__DOT__u_pr__DOT__len_hi = vlSelfRef.tb_top__DOT__u_pr__DOT__len_hi;
    __Vdly__tb_top__DOT__u_pr__DOT__cnt = vlSelfRef.tb_top__DOT__u_pr__DOT__cnt;
    __Vdly__tb_top__DOT__u_pr__DOT__len_lo = vlSelfRef.tb_top__DOT__u_pr__DOT__len_lo;
    __Vdly__tb_top__DOT__u_pr__DOT__type_reg = vlSelfRef.tb_top__DOT__u_pr__DOT__type_reg;
    __Vdly__tb_top__DOT__u_pr__DOT__state = vlSelfRef.tb_top__DOT__u_pr__DOT__state;
    __Vdly__tb_top__DOT__u_pr__DOT__body_left = vlSelfRef.tb_top__DOT__u_pr__DOT__body_left;
    __Vdly__order_id = vlSelfRef.order_id;
    __Vdly__price = vlSelfRef.price;
    __Vdly__volume = vlSelfRef.volume;
    vlSelfRef.tb_top__DOT__u_prg__DOT__s1__DOT__saved_valid = 0U;
    if ((1U & (~ (IData)(vlSelfRef.rst_n)))) {
        vlSelfRef.tb_top__DOT__u_prg__DOT__s1__DOT__saved_data = 0U;
    }
    if (vlSelfRef.rst_n) {
        if (vlSelfRef.l2t_stall) {
            vlSelfRef.l2t_stall_cycles = ((IData)(1U) 
                                          + vlSelfRef.l2t_stall_cycles);
        }
        __Vdly__cycle_cnt = ((IData)(1U) + vlSelfRef.cycle_cnt);
        if ((((IData)(vlSelfRef.parsed_valid_reg) & 
              (0x50U == (IData)(vlSelfRef.parsed_type_reg))) 
             & (0x1e8480U > vlSelfRef.parsed_price_reg))) {
            vlSelfRef.tb_top__DOT__u_tl__DOT__d_volume 
                = vlSelfRef.parsed_volume_reg;
            vlSelfRef.tb_top__DOT__u_tl__DOT__d_order_id 
                = (((QData)((IData)(vlSelfRef.tb_top__DOT__u_prg__DOT__p2l_bus_out[5U])) 
                    << 0x20U) | (QData)((IData)(vlSelfRef.tb_top__DOT__u_prg__DOT__p2l_bus_out[4U])));
            vlSelfRef.tb_top__DOT__decision_type = vlSelfRef.parsed_type_reg;
            vlSelfRef.tb_top__DOT__decision_data = vlSelfRef.parsed_price_reg;
        }
    } else {
        vlSelfRef.l2t_stall_cycles = 0U;
        __Vdly__cycle_cnt = 0U;
        vlSelfRef.tb_top__DOT__u_tl__DOT__d_volume = 0U;
        vlSelfRef.tb_top__DOT__u_tl__DOT__d_order_id = 0ULL;
        vlSelfRef.tb_top__DOT__decision_type = 0U;
        vlSelfRef.tb_top__DOT__decision_data = 0U;
    }
    if (vlSelfRef.rst_n) {
        if ((2U & (IData)(vlSelfRef.tb_top__DOT__u_ut__DOT__st))) {
            if ((1U & (IData)(vlSelfRef.tb_top__DOT__u_ut__DOT__st))) {
                vlSelfRef.uart_tx = 1U;
                if ((0x879U == (IData)(vlSelfRef.tb_top__DOT__u_ut__DOT__tick_cnt))) {
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
                                    VL_WRITEF_NX("[%0t] %%Error: uart_tx.sv:119: Assertion failed in %Ntb_top.u_ut: unique case, but multiple matches found for '2'h%x'\n",0,
                                                 64,
                                                 VL_TIME_UNITED_Q(1000),
                                                 -9,
                                                 vlSymsp->name(),
                                                 2,
                                                 (IData)(vlSelfRef.tb_top__DOT__u_ut__DOT__byte_idx));
                                    VL_STOP_MT("/Users/keelanreilly/Desktop/low_latency_market_parser/hdl/uart_tx.sv", 119, "");
                                }
                            }
                        }
                    }
                } else {
                    __Vdly__tb_top__DOT__u_ut__DOT__tick_cnt 
                        = (0xfffU & ((IData)(1U) + (IData)(vlSelfRef.tb_top__DOT__u_ut__DOT__tick_cnt)));
                }
            } else {
                vlSelfRef.uart_tx = (1U & (IData)(vlSelfRef.tb_top__DOT__u_ut__DOT__sh));
                if ((0x879U == (IData)(vlSelfRef.tb_top__DOT__u_ut__DOT__tick_cnt))) {
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
                        = (0xfffU & ((IData)(1U) + (IData)(vlSelfRef.tb_top__DOT__u_ut__DOT__tick_cnt)));
                }
            }
        } else if ((1U & (IData)(vlSelfRef.tb_top__DOT__u_ut__DOT__st))) {
            vlSelfRef.uart_tx = 0U;
            if ((0x879U == (IData)(vlSelfRef.tb_top__DOT__u_ut__DOT__tick_cnt))) {
                __Vdly__tb_top__DOT__u_ut__DOT__tick_cnt = 0U;
                __Vdly__tb_top__DOT__u_ut__DOT__bit_idx = 0U;
                __Vdly__tb_top__DOT__u_ut__DOT__st = 2U;
            } else {
                __Vdly__tb_top__DOT__u_ut__DOT__tick_cnt 
                    = (0xfffU & ((IData)(1U) + (IData)(vlSelfRef.tb_top__DOT__u_ut__DOT__tick_cnt)));
            }
        } else {
            vlSelfRef.uart_tx = 1U;
            __Vdly__tb_top__DOT__u_ut__DOT__tick_cnt = 0U;
            __Vdly__tb_top__DOT__u_ut__DOT__bit_idx = 0U;
            __Vdly__tb_top__DOT__u_ut__DOT__byte_idx = 0U;
            if (vlSelfRef.tb_top__DOT__u_ut__DOT__accept) {
                vlSelfRef.tb_top__DOT__u_ut__DOT__word_reg 
                    = vlSelfRef.tx_word_data;
                __Vdly__tb_top__DOT__u_ut__DOT__sh 
                    = (0xffU & vlSelfRef.tx_word_data);
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
    if (vlSelfRef.rst_n) {
        vlSelfRef.tb_top__DOT__u_prg__DOT__s2__DOT__saved_valid = 0U;
    } else {
        vlSelfRef.tb_top__DOT__u_prg__DOT__s2__DOT__saved_valid = 0U;
        vlSelfRef.tb_top__DOT__u_prg__DOT__s2__DOT__saved_data[0U] = 0U;
        vlSelfRef.tb_top__DOT__u_prg__DOT__s2__DOT__saved_data[1U] = 0U;
        vlSelfRef.tb_top__DOT__u_prg__DOT__s2__DOT__saved_data[2U] = 0U;
        vlSelfRef.tb_top__DOT__u_prg__DOT__s2__DOT__saved_data[3U] = 0U;
        vlSelfRef.tb_top__DOT__u_prg__DOT__s2__DOT__saved_data[4U] = 0U;
        vlSelfRef.tb_top__DOT__u_prg__DOT__s2__DOT__saved_data[5U] = 0U;
        vlSelfRef.tb_top__DOT__u_prg__DOT__s2__DOT__saved_data[6U] = 0U;
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
                        vlSelfRef.tb_top__DOT__u_eth__DOT__unnamedblk2__DOT__new_fcs 
                            = (((IData)(vlSelfRef.rx_byte) 
                                << 0x18U) | (0xffffffU 
                                             & vlSelfRef.tb_top__DOT__u_eth__DOT__crc_recv_shift));
                        vlSelfRef.tb_top__DOT__u_eth__DOT__fcs_word 
                            = vlSelfRef.tb_top__DOT__u_eth__DOT__unnamedblk2__DOT__new_fcs;
                        vlSelfRef.dbg_crc_calc = (~ vlSelfRef.tb_top__DOT__u_eth__DOT__crc_reg);
                        vlSelfRef.eth_crc_valid = 1U;
                        vlSelfRef.tb_top__DOT__u_eth__DOT__crc_started = 0U;
                        __Vdly__tb_top__DOT__u_eth__DOT__state = 0U;
                        __Vdly__tb_top__DOT__u_eth__DOT__crc_cnt = 0U;
                        vlSelfRef.dbg_crc_recv = vlSelfRef.tb_top__DOT__u_eth__DOT__unnamedblk2__DOT__new_fcs;
                        vlSelfRef.eth_crc_ok = ((~ vlSelfRef.tb_top__DOT__u_eth__DOT__crc_reg) 
                                                == vlSelfRef.tb_top__DOT__u_eth__DOT__unnamedblk2__DOT__new_fcs);
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
                                VL_WRITEF_NX("[%0t] %%Error: eth_rx.sv:276: Assertion failed in %Ntb_top.u_eth: unique case, but none matched for '32'h%x'\n",0,
                                             64,VL_TIME_UNITED_Q(1000),
                                             -9,vlSymsp->name(),
                                             32,(IData)(vlSelfRef.tb_top__DOT__u_eth__DOT__crc_cnt));
                                VL_STOP_MT("/Users/keelanreilly/Desktop/low_latency_market_parser/hdl/eth_rx.sv", 276, "");
                            }
                        } else if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                            VL_WRITEF_NX("[%0t] %%Error: eth_rx.sv:276: Assertion failed in %Ntb_top.u_eth: unique case, but multiple matches found for '32'h%x'\n",0,
                                         64,VL_TIME_UNITED_Q(1000),
                                         -9,vlSymsp->name(),
                                         32,(IData)(vlSelfRef.tb_top__DOT__u_eth__DOT__crc_cnt));
                            VL_STOP_MT("/Users/keelanreilly/Desktop/low_latency_market_parser/hdl/eth_rx.sv", 276, "");
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
                        vlSelfRef.tb_top__DOT__u_eth__DOT__full_dest 
                            = ((0xffffffffff00ULL & 
                                (vlSelfRef.tb_top__DOT__u_eth__DOT__dest_mac_shift 
                                 << 8U)) | (QData)((IData)(vlSelfRef.rx_byte)));
                        vlSelfRef.tb_top__DOT__u_eth__DOT__dest_mac_shift 
                            = vlSelfRef.tb_top__DOT__u_eth__DOT__full_dest;
                        if ((5U == (IData)(vlSelfRef.tb_top__DOT__u_eth__DOT__hdr_cnt))) {
                            vlSelfRef.tb_top__DOT__u_eth__DOT__this_cycle_match 
                                = ((0x1122334455ULL 
                                    == vlSelfRef.tb_top__DOT__u_eth__DOT__full_dest) 
                                   | (0xffffffffffffULL 
                                      == vlSelfRef.tb_top__DOT__u_eth__DOT__full_dest));
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
                    vlSelfRef.tb_top__DOT__u_eth__DOT__crc_started = 1U;
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
        vlSelfRef.tb_top__DOT__u_eth__DOT__crc_started = 0U;
        vlSelfRef.tb_top__DOT__u_eth__DOT__fcs_word = 0U;
        __Vdly__tb_top__DOT__u_eth__DOT__total_payload = 0U;
        vlSelfRef.dbg_crc_calc = 0U;
        vlSelfRef.dbg_crc_recv = 0U;
        vlSelfRef.dbg_payload_len = 0U;
        vlSelfRef.dbg_total_payload = 0U;
        vlSelfRef.dbg_payload_cnt_last = 0U;
    }
    if (vlSelfRef.rst_n) {
        if (vlSelfRef.tb_top__DOT__uart_ready_masked) {
            __Vdly__tb_top__DOT__u_prg__DOT__s3__DOT__saved_valid = 0U;
        }
        if ((((IData)(vlSelfRef.decision_valid) & (~ (IData)(vlSelfRef.tb_top__DOT__uart_ready_masked))) 
             & (~ (IData)(vlSelfRef.tb_top__DOT__u_prg__DOT__s3__DOT__saved_valid)))) {
            __Vdly__tb_top__DOT__u_prg__DOT__s3__DOT__saved_valid = 1U;
            vlSelfRef.tb_top__DOT__u_prg__DOT__s3__DOT__saved_data[0U] 
                = vlSelfRef.tb_top__DOT__u_prg__DOT__l2t_bus_in[0U];
            vlSelfRef.tb_top__DOT__u_prg__DOT__s3__DOT__saved_data[1U] 
                = vlSelfRef.tb_top__DOT__u_prg__DOT__l2t_bus_in[1U];
            vlSelfRef.tb_top__DOT__u_prg__DOT__s3__DOT__saved_data[2U] 
                = vlSelfRef.tb_top__DOT__u_prg__DOT__l2t_bus_in[2U];
            vlSelfRef.tb_top__DOT__u_prg__DOT__s3__DOT__saved_data[3U] 
                = vlSelfRef.tb_top__DOT__u_prg__DOT__l2t_bus_in[3U];
            vlSelfRef.tb_top__DOT__u_prg__DOT__s3__DOT__saved_data[4U] 
                = vlSelfRef.tb_top__DOT__u_prg__DOT__l2t_bus_in[4U];
            vlSelfRef.tb_top__DOT__u_prg__DOT__s3__DOT__saved_data[5U] 
                = vlSelfRef.tb_top__DOT__u_prg__DOT__l2t_bus_in[5U];
        }
        if (vlSelfRef.tb_top__DOT__parser_msg_start) {
            vlSelfRef.tb_top__DOT__u_prg__DOT__ingress_last 
                = vlSelfRef.cycle_cnt;
        }
        vlSelfRef.field_valid = 0U;
        vlSelfRef.tb_top__DOT__parser_msg_start = 0U;
        if ((0U == (IData)(vlSelfRef.tb_top__DOT__u_pr__DOT__state))) {
            if (vlSelfRef.tb_top__DOT__rx2p_out_valid) {
                if ((0U == (IData)(vlSelfRef.tb_top__DOT__u_pr__DOT__cnt))) {
                    vlSelfRef.tb_top__DOT__parser_msg_start = 1U;
                    __Vdly__tb_top__DOT__u_pr__DOT__len_hi 
                        = vlSelfRef.tb_top__DOT__rx2p_out;
                    __Vdly__tb_top__DOT__u_pr__DOT__cnt = 1U;
                } else if ((1U == (IData)(vlSelfRef.tb_top__DOT__u_pr__DOT__cnt))) {
                    __Vdly__tb_top__DOT__u_pr__DOT__len_lo 
                        = vlSelfRef.tb_top__DOT__rx2p_out;
                    __Vdly__tb_top__DOT__u_pr__DOT__cnt = 2U;
                } else if ((2U == (IData)(vlSelfRef.tb_top__DOT__u_pr__DOT__cnt))) {
                    __Vdly__tb_top__DOT__u_pr__DOT__type_reg 
                        = vlSelfRef.tb_top__DOT__rx2p_out;
                    vlSelfRef.tb_top__DOT__u_pr__DOT__length 
                        = (((IData)(vlSelfRef.tb_top__DOT__u_pr__DOT__len_hi) 
                            << 8U) | (IData)(vlSelfRef.tb_top__DOT__u_pr__DOT__len_lo));
                    __Vdly__tb_top__DOT__u_pr__DOT__cnt = 0U;
                    __Vdly__order_id = 0ULL;
                    __Vdly__price = 0U;
                    __Vdly__volume = 0U;
                    __Vdly__tb_top__DOT__u_pr__DOT__state 
                        = ((0x50U == (IData)(vlSelfRef.tb_top__DOT__rx2p_out))
                            ? 1U : 2U);
                    __Vdly__tb_top__DOT__u_pr__DOT__body_left 
                        = (0xffffU & ((((IData)(vlSelfRef.tb_top__DOT__u_pr__DOT__len_hi) 
                                        << 8U) | (IData)(vlSelfRef.tb_top__DOT__u_pr__DOT__len_lo)) 
                                      - (IData)(1U)));
                }
            }
        } else if ((1U == (IData)(vlSelfRef.tb_top__DOT__u_pr__DOT__state))) {
            if (vlSelfRef.tb_top__DOT__rx2p_out_valid) {
                if (((0xaU <= (IData)(vlSelfRef.tb_top__DOT__u_pr__DOT__cnt)) 
                     & (0x11U >= (IData)(vlSelfRef.tb_top__DOT__u_pr__DOT__cnt)))) {
                    __Vdly__order_id = (VL_SHIFTL_QQI(64,64,32, vlSelfRef.order_id, 8U) 
                                        | (QData)((IData)(vlSelfRef.tb_top__DOT__rx2p_out)));
                }
                if (((0x13U <= (IData)(vlSelfRef.tb_top__DOT__u_pr__DOT__cnt)) 
                     & (0x16U >= (IData)(vlSelfRef.tb_top__DOT__u_pr__DOT__cnt)))) {
                    __Vdly__volume = (VL_SHIFTL_III(32,32,32, vlSelfRef.volume, 8U) 
                                      | (IData)(vlSelfRef.tb_top__DOT__rx2p_out));
                }
                if (((0x1fU <= (IData)(vlSelfRef.tb_top__DOT__u_pr__DOT__cnt)) 
                     & (0x22U >= (IData)(vlSelfRef.tb_top__DOT__u_pr__DOT__cnt)))) {
                    __Vdly__price = (VL_SHIFTL_III(32,32,32, vlSelfRef.price, 8U) 
                                     | (IData)(vlSelfRef.tb_top__DOT__rx2p_out));
                }
                if ((0x22U == (IData)(vlSelfRef.tb_top__DOT__u_pr__DOT__cnt))) {
                    vlSelfRef.field_valid = 1U;
                    vlSelfRef.msg_type = vlSelfRef.tb_top__DOT__u_pr__DOT__type_reg;
                }
                if ((((IData)(1U) + (IData)(vlSelfRef.tb_top__DOT__u_pr__DOT__cnt)) 
                     == (IData)(vlSelfRef.tb_top__DOT__u_pr__DOT__body_left))) {
                    __Vdly__tb_top__DOT__u_pr__DOT__state = 0U;
                    __Vdly__tb_top__DOT__u_pr__DOT__cnt = 0U;
                } else {
                    __Vdly__tb_top__DOT__u_pr__DOT__cnt 
                        = (0xffffU & ((IData)(1U) + (IData)(vlSelfRef.tb_top__DOT__u_pr__DOT__cnt)));
                }
            }
        } else if ((2U == (IData)(vlSelfRef.tb_top__DOT__u_pr__DOT__state))) {
            if (vlSelfRef.tb_top__DOT__rx2p_out_valid) {
                if ((((IData)(1U) + (IData)(vlSelfRef.tb_top__DOT__u_pr__DOT__cnt)) 
                     == (IData)(vlSelfRef.tb_top__DOT__u_pr__DOT__body_left))) {
                    __Vdly__tb_top__DOT__u_pr__DOT__state = 0U;
                    __Vdly__tb_top__DOT__u_pr__DOT__cnt = 0U;
                } else {
                    __Vdly__tb_top__DOT__u_pr__DOT__cnt 
                        = (0xffffU & ((IData)(1U) + (IData)(vlSelfRef.tb_top__DOT__u_pr__DOT__cnt)));
                }
            }
        }
    } else {
        __Vdly__tb_top__DOT__u_prg__DOT__s3__DOT__saved_valid = 0U;
        vlSelfRef.tb_top__DOT__u_prg__DOT__s3__DOT__saved_data[0U] = 0U;
        vlSelfRef.tb_top__DOT__u_prg__DOT__s3__DOT__saved_data[1U] = 0U;
        vlSelfRef.tb_top__DOT__u_prg__DOT__s3__DOT__saved_data[2U] = 0U;
        vlSelfRef.tb_top__DOT__u_prg__DOT__s3__DOT__saved_data[3U] = 0U;
        vlSelfRef.tb_top__DOT__u_prg__DOT__s3__DOT__saved_data[4U] = 0U;
        vlSelfRef.tb_top__DOT__u_prg__DOT__s3__DOT__saved_data[5U] = 0U;
        vlSelfRef.tb_top__DOT__u_prg__DOT__ingress_last = 0U;
        vlSelfRef.tb_top__DOT__parser_msg_start = 0U;
        __Vdly__tb_top__DOT__u_pr__DOT__state = 0U;
        __Vdly__tb_top__DOT__u_pr__DOT__len_hi = 0U;
        __Vdly__tb_top__DOT__u_pr__DOT__len_lo = 0U;
        vlSelfRef.tb_top__DOT__u_pr__DOT__length = 0U;
        __Vdly__tb_top__DOT__u_pr__DOT__type_reg = 0U;
        __Vdly__tb_top__DOT__u_pr__DOT__cnt = 0U;
        __Vdly__tb_top__DOT__u_pr__DOT__body_left = 0U;
        vlSelfRef.field_valid = 0U;
        vlSelfRef.msg_type = 0U;
        __Vdly__order_id = 0ULL;
        __Vdly__price = 0U;
        __Vdly__volume = 0U;
    }
    vlSelfRef.tb_top__DOT__u_ut__DOT__tick_cnt = __Vdly__tb_top__DOT__u_ut__DOT__tick_cnt;
    vlSelfRef.tb_top__DOT__u_ut__DOT__byte_idx = __Vdly__tb_top__DOT__u_ut__DOT__byte_idx;
    vlSelfRef.tb_top__DOT__u_ut__DOT__sh = __Vdly__tb_top__DOT__u_ut__DOT__sh;
    vlSelfRef.tb_top__DOT__u_ut__DOT__bit_idx = __Vdly__tb_top__DOT__u_ut__DOT__bit_idx;
    vlSelfRef.tb_top__DOT__u_ut__DOT__st = __Vdly__tb_top__DOT__u_ut__DOT__st;
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
    vlSelfRef.tb_top__DOT__u_prg__DOT__s3__DOT__saved_valid 
        = __Vdly__tb_top__DOT__u_prg__DOT__s3__DOT__saved_valid;
    vlSelfRef.cycle_cnt = __Vdly__cycle_cnt;
    vlSelfRef.tb_top__DOT__uart_ready_masked = ((IData)(vlSelfRef.sink_allow) 
                                                & (0U 
                                                   == (IData)(vlSelfRef.tb_top__DOT__u_ut__DOT__st)));
    vlSelfRef.decision_valid = ((IData)(vlSelfRef.rst_n) 
                                && (((IData)(vlSelfRef.parsed_valid_reg) 
                                     & (0x50U == (IData)(vlSelfRef.parsed_type_reg))) 
                                    & (0x1e8480U > vlSelfRef.parsed_price_reg)));
    vlSelfRef.tb_top__DOT__rx2p_out_valid = ((IData)(vlSelfRef.payload_valid) 
                                             | (IData)(vlSelfRef.tb_top__DOT__u_prg__DOT__s1__DOT__saved_valid));
    vlSelfRef.tb_top__DOT__u_pr__DOT__len_hi = __Vdly__tb_top__DOT__u_pr__DOT__len_hi;
    vlSelfRef.tb_top__DOT__u_pr__DOT__cnt = __Vdly__tb_top__DOT__u_pr__DOT__cnt;
    vlSelfRef.tb_top__DOT__u_pr__DOT__len_lo = __Vdly__tb_top__DOT__u_pr__DOT__len_lo;
    vlSelfRef.tb_top__DOT__u_pr__DOT__type_reg = __Vdly__tb_top__DOT__u_pr__DOT__type_reg;
    vlSelfRef.tb_top__DOT__u_pr__DOT__state = __Vdly__tb_top__DOT__u_pr__DOT__state;
    vlSelfRef.tb_top__DOT__u_pr__DOT__body_left = __Vdly__tb_top__DOT__u_pr__DOT__body_left;
    vlSelfRef.tb_top__DOT__rx2p_out = ((IData)(vlSelfRef.tb_top__DOT__u_prg__DOT__s1__DOT__saved_valid)
                                        ? (IData)(vlSelfRef.tb_top__DOT__u_prg__DOT__s1__DOT__saved_data)
                                        : (IData)(vlSelfRef.payload_byte));
    vlSelfRef.order_id = __Vdly__order_id;
    vlSelfRef.price = __Vdly__price;
    vlSelfRef.volume = __Vdly__volume;
    vlSelfRef.tb_top__DOT__l2t_out_valid = ((IData)(vlSelfRef.decision_valid) 
                                            | (IData)(vlSelfRef.tb_top__DOT__u_prg__DOT__s3__DOT__saved_valid));
    vlSelfRef.parsed_valid_reg = ((IData)(vlSelfRef.field_valid) 
                                  | (IData)(vlSelfRef.tb_top__DOT__u_prg__DOT__s2__DOT__saved_valid));
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

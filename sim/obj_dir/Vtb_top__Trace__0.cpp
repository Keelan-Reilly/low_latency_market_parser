// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vtb_top__Syms.h"


void Vtb_top___024root__trace_chg_0_sub_0(Vtb_top___024root* vlSelf, VerilatedVcd::Buffer* bufp);

void Vtb_top___024root__trace_chg_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root__trace_chg_0\n"); );
    // Init
    Vtb_top___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtb_top___024root*>(voidSelf);
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    // Body
    Vtb_top___024root__trace_chg_0_sub_0((&vlSymsp->TOP), bufp);
}

void Vtb_top___024root__trace_chg_0_sub_0(Vtb_top___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    if (false && vlSelf) {}  // Prevent unused
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root__trace_chg_0_sub_0\n"); );
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode + 1);
    // Body
    if (VL_UNLIKELY(vlSelf->__Vm_traceActivity[1U])) {
        bufp->chgBit(oldp+0,((0U == (IData)(vlSelf->tb_top__DOT__u_ut__DOT__st))));
        bufp->chgCData(oldp+1,(vlSelf->tb_top__DOT__decision_type),8);
        bufp->chgIData(oldp+2,(vlSelf->tb_top__DOT__decision_data),32);
        bufp->chgBit(oldp+3,((0U != (IData)(vlSelf->tb_top__DOT__u_ut__DOT__st))));
        bufp->chgBit(oldp+4,(vlSelf->tb_top__DOT__parser_msg_start));
        bufp->chgCData(oldp+5,(vlSelf->tb_top__DOT__u_prg__DOT__rx2p_data),8);
        bufp->chgBit(oldp+6,(vlSelf->tb_top__DOT__u_prg__DOT__rx2p_data_valid));
        bufp->chgQData(oldp+7,(vlSelf->tb_top__DOT__u_prg__DOT__p2l_order_id_reg),64);
        bufp->chgBit(oldp+9,((1U & ((~ (IData)(vlSelf->tb_top__DOT__u_prg__DOT__l2t_data_valid)) 
                                    | (0U == (IData)(vlSelf->tb_top__DOT__u_ut__DOT__st))))));
        bufp->chgCData(oldp+10,(vlSelf->tb_top__DOT__u_prg__DOT__l2t_type_reg),8);
        bufp->chgBit(oldp+11,(vlSelf->tb_top__DOT__u_prg__DOT__l2t_data_valid));
        bufp->chgCData(oldp+12,(vlSelf->tb_top__DOT__u_eth__DOT__state),3);
        bufp->chgCData(oldp+13,(vlSelf->tb_top__DOT__u_eth__DOT__pre_cnt),3);
        bufp->chgCData(oldp+14,(vlSelf->tb_top__DOT__u_eth__DOT__crc_cnt),4);
        bufp->chgSData(oldp+15,(vlSelf->tb_top__DOT__u_eth__DOT__hdr_cnt),16);
        bufp->chgSData(oldp+16,(vlSelf->tb_top__DOT__u_eth__DOT__payload_cnt),16);
        bufp->chgSData(oldp+17,(vlSelf->tb_top__DOT__u_eth__DOT__payload_len),16);
        bufp->chgQData(oldp+18,(vlSelf->tb_top__DOT__u_eth__DOT__dest_mac_shift),48);
        bufp->chgBit(oldp+20,(vlSelf->tb_top__DOT__u_eth__DOT__mac_match));
        bufp->chgIData(oldp+21,(vlSelf->tb_top__DOT__u_eth__DOT__crc_reg),32);
        bufp->chgIData(oldp+22,(vlSelf->tb_top__DOT__u_eth__DOT__crc_recv_shift),32);
        bufp->chgBit(oldp+23,(vlSelf->tb_top__DOT__u_eth__DOT__this_cycle_match));
        bufp->chgIData(oldp+24,(vlSelf->tb_top__DOT__u_eth__DOT__next_crc),32);
        bufp->chgIData(oldp+25,(vlSelf->tb_top__DOT__u_eth__DOT__fcs_word),32);
        bufp->chgSData(oldp+26,(vlSelf->tb_top__DOT__u_eth__DOT__total_payload),16);
        bufp->chgBit(oldp+27,(vlSelf->tb_top__DOT__u_eth__DOT__crc_started));
        bufp->chgQData(oldp+28,(vlSelf->tb_top__DOT__u_eth__DOT__unnamedblk2__DOT__full_dest),48);
        bufp->chgIData(oldp+30,(vlSelf->tb_top__DOT__u_eth__DOT__unnamedblk3__DOT__new_fcs),32);
        bufp->chgCData(oldp+31,(vlSelf->tb_top__DOT__u_pr__DOT__state),2);
        bufp->chgSData(oldp+32,(vlSelf->tb_top__DOT__u_pr__DOT__length),16);
        bufp->chgCData(oldp+33,(vlSelf->tb_top__DOT__u_pr__DOT__len_hi),8);
        bufp->chgCData(oldp+34,(vlSelf->tb_top__DOT__u_pr__DOT__len_lo),8);
        bufp->chgCData(oldp+35,(vlSelf->tb_top__DOT__u_pr__DOT__type_reg),8);
        bufp->chgSData(oldp+36,(vlSelf->tb_top__DOT__u_pr__DOT__cnt),16);
        bufp->chgSData(oldp+37,(vlSelf->tb_top__DOT__u_pr__DOT__body_left),16);
        bufp->chgCData(oldp+38,(vlSelf->tb_top__DOT__u_prg__DOT__p2l_type_reg),8);
        bufp->chgIData(oldp+39,(vlSelf->tb_top__DOT__u_prg__DOT__p2l_price_reg),32);
        bufp->chgIData(oldp+40,(vlSelf->tb_top__DOT__u_prg__DOT__p2l_volume_reg),32);
        bufp->chgBit(oldp+41,(vlSelf->tb_top__DOT__u_prg__DOT__p2l_data_valid));
        bufp->chgIData(oldp+42,(vlSelf->tb_top__DOT__u_prg__DOT__ingress_last),32);
        bufp->chgIData(oldp+43,(vlSelf->tb_top__DOT__u_prg__DOT__ingress_s2),32);
        bufp->chgIData(oldp+44,(vlSelf->tb_top__DOT__u_prg__DOT__p2l_timestamp),32);
        bufp->chgIData(oldp+45,(vlSelf->tb_top__DOT__u_prg__DOT__l2t_data_reg),32);
        bufp->chgIData(oldp+46,(vlSelf->tb_top__DOT__u_prg__DOT__t_ingress_cap),32);
        bufp->chgIData(oldp+47,(vlSelf->tb_top__DOT__u_prg__DOT__t_parser_cap),32);
        bufp->chgIData(oldp+48,(vlSelf->tb_top__DOT__u_prg__DOT__t_logic_cap),32);
        bufp->chgIData(oldp+49,(vlSelf->tb_top__DOT__u_prg__DOT__t_decision_cap),32);
        bufp->chgQData(oldp+50,(vlSelf->tb_top__DOT__u_tl__DOT__d_order_id),64);
        bufp->chgIData(oldp+52,(vlSelf->tb_top__DOT__u_tl__DOT__d_volume),32);
        bufp->chgSData(oldp+53,(vlSelf->tb_top__DOT__u_ut__DOT__tick_cnt),10);
        bufp->chgCData(oldp+54,(vlSelf->tb_top__DOT__u_ut__DOT__st),2);
        bufp->chgIData(oldp+55,(vlSelf->tb_top__DOT__u_ut__DOT__word_reg),32);
        bufp->chgCData(oldp+56,(vlSelf->tb_top__DOT__u_ut__DOT__byte_idx),2);
        bufp->chgCData(oldp+57,(vlSelf->tb_top__DOT__u_ut__DOT__bit_idx),3);
        bufp->chgCData(oldp+58,(vlSelf->tb_top__DOT__u_ut__DOT__sh),8);
        bufp->chgBit(oldp+59,(((0U == (IData)(vlSelf->tb_top__DOT__u_ut__DOT__st)) 
                               & (IData)(vlSelf->tb_top__DOT__u_prg__DOT__l2t_data_valid))));
    }
    bufp->chgBit(oldp+60,(vlSelf->clk));
    bufp->chgBit(oldp+61,(vlSelf->rst_n));
    bufp->chgCData(oldp+62,(vlSelf->rx_byte),8);
    bufp->chgBit(oldp+63,(vlSelf->rx_valid));
    bufp->chgBit(oldp+64,(vlSelf->uart_tx));
    bufp->chgBit(oldp+65,(vlSelf->payload_valid));
    bufp->chgCData(oldp+66,(vlSelf->payload_byte),8);
    bufp->chgBit(oldp+67,(vlSelf->field_valid));
    bufp->chgCData(oldp+68,(vlSelf->msg_type),8);
    bufp->chgBit(oldp+69,(vlSelf->decision_valid));
    bufp->chgQData(oldp+70,(vlSelf->order_id),64);
    bufp->chgIData(oldp+72,(vlSelf->price),32);
    bufp->chgIData(oldp+73,(vlSelf->volume),32);
    bufp->chgBit(oldp+74,(vlSelf->eth_crc_ok));
    bufp->chgBit(oldp+75,(vlSelf->eth_crc_valid));
    bufp->chgIData(oldp+76,(vlSelf->t_ingress),32);
    bufp->chgIData(oldp+77,(vlSelf->t_parser),32);
    bufp->chgIData(oldp+78,(vlSelf->t_parser_event),32);
    bufp->chgIData(oldp+79,(vlSelf->t_logic),32);
    bufp->chgIData(oldp+80,(vlSelf->t_decision),32);
    bufp->chgIData(oldp+81,(vlSelf->cycle_cnt),32);
    bufp->chgIData(oldp+82,(vlSelf->dbg_crc_calc),32);
    bufp->chgIData(oldp+83,(vlSelf->dbg_crc_recv),32);
    bufp->chgSData(oldp+84,(vlSelf->dbg_payload_len),16);
    bufp->chgSData(oldp+85,(vlSelf->dbg_total_payload),16);
    bufp->chgSData(oldp+86,(vlSelf->dbg_payload_cnt_last),16);
    bufp->chgBit(oldp+87,(vlSelf->parsed_valid_reg));
    bufp->chgCData(oldp+88,(vlSelf->parsed_type_reg),8);
    bufp->chgIData(oldp+89,(vlSelf->parsed_price_reg),32);
    bufp->chgIData(oldp+90,(vlSelf->parsed_volume_reg),32);
    bufp->chgBit(oldp+91,(vlSelf->tx_word_valid));
    bufp->chgIData(oldp+92,(vlSelf->tx_word_data),32);
}

void Vtb_top___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root__trace_cleanup\n"); );
    // Init
    Vtb_top___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtb_top___024root*>(voidSelf);
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    vlSymsp->__Vm_activity = false;
    vlSymsp->TOP.__Vm_traceActivity[0U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[1U] = 0U;
}

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
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root__trace_chg_0_sub_0\n"); );
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode + 1);
    // Body
    if (VL_UNLIKELY((vlSelfRef.__Vm_traceActivity[1U]))) {
        bufp->chgBit(oldp+0,((0U == (IData)(vlSelfRef.tb_top__DOT__u_ut__DOT__st))));
        bufp->chgCData(oldp+1,(vlSelfRef.tb_top__DOT__decision_type),8);
        bufp->chgIData(oldp+2,(vlSelfRef.tb_top__DOT__decision_data),32);
        bufp->chgBit(oldp+3,((0U != (IData)(vlSelfRef.tb_top__DOT__u_ut__DOT__st))));
        bufp->chgBit(oldp+4,(vlSelfRef.tb_top__DOT__parser_msg_start));
        bufp->chgCData(oldp+5,(vlSelfRef.tb_top__DOT__rx2p_out),8);
        bufp->chgBit(oldp+6,(vlSelfRef.tb_top__DOT__rx2p_out_valid));
        bufp->chgQData(oldp+7,((((QData)((IData)(vlSelfRef.tb_top__DOT__u_prg__DOT__p2l_bus_out[5U])) 
                                 << 0x20U) | (QData)((IData)(
                                                             vlSelfRef.tb_top__DOT__u_prg__DOT__p2l_bus_out[4U])))),64);
        bufp->chgCData(oldp+9,((0xffU & vlSelfRef.tb_top__DOT__u_prg__DOT__l2t_bus_out[5U])),8);
        bufp->chgBit(oldp+10,(vlSelfRef.tb_top__DOT__l2t_out_valid));
        bufp->chgCData(oldp+11,(vlSelfRef.tb_top__DOT__u_eth__DOT__state),3);
        bufp->chgCData(oldp+12,(vlSelfRef.tb_top__DOT__u_eth__DOT__pre_cnt),3);
        bufp->chgCData(oldp+13,(vlSelfRef.tb_top__DOT__u_eth__DOT__crc_cnt),4);
        bufp->chgSData(oldp+14,(vlSelfRef.tb_top__DOT__u_eth__DOT__hdr_cnt),16);
        bufp->chgSData(oldp+15,(vlSelfRef.tb_top__DOT__u_eth__DOT__payload_cnt),16);
        bufp->chgSData(oldp+16,(vlSelfRef.tb_top__DOT__u_eth__DOT__payload_len),16);
        bufp->chgQData(oldp+17,(vlSelfRef.tb_top__DOT__u_eth__DOT__dest_mac_shift),48);
        bufp->chgBit(oldp+19,(vlSelfRef.tb_top__DOT__u_eth__DOT__mac_match));
        bufp->chgIData(oldp+20,(vlSelfRef.tb_top__DOT__u_eth__DOT__crc_reg),32);
        bufp->chgIData(oldp+21,(vlSelfRef.tb_top__DOT__u_eth__DOT__crc_recv_shift),32);
        bufp->chgBit(oldp+22,(vlSelfRef.tb_top__DOT__u_eth__DOT__this_cycle_match));
        bufp->chgIData(oldp+23,(vlSelfRef.tb_top__DOT__u_eth__DOT__next_crc),32);
        bufp->chgIData(oldp+24,(vlSelfRef.tb_top__DOT__u_eth__DOT__fcs_word),32);
        bufp->chgSData(oldp+25,(vlSelfRef.tb_top__DOT__u_eth__DOT__total_payload),16);
        bufp->chgBit(oldp+26,(vlSelfRef.tb_top__DOT__u_eth__DOT__crc_started));
        bufp->chgQData(oldp+27,(vlSelfRef.tb_top__DOT__u_eth__DOT__full_dest),48);
        bufp->chgIData(oldp+29,(vlSelfRef.tb_top__DOT__u_eth__DOT__unnamedblk2__DOT__new_fcs),32);
        bufp->chgCData(oldp+30,(vlSelfRef.tb_top__DOT__u_pr__DOT__state),2);
        bufp->chgSData(oldp+31,(vlSelfRef.tb_top__DOT__u_pr__DOT__length),16);
        bufp->chgCData(oldp+32,(vlSelfRef.tb_top__DOT__u_pr__DOT__len_hi),8);
        bufp->chgCData(oldp+33,(vlSelfRef.tb_top__DOT__u_pr__DOT__len_lo),8);
        bufp->chgCData(oldp+34,(vlSelfRef.tb_top__DOT__u_pr__DOT__type_reg),8);
        bufp->chgSData(oldp+35,(vlSelfRef.tb_top__DOT__u_pr__DOT__cnt),16);
        bufp->chgSData(oldp+36,(vlSelfRef.tb_top__DOT__u_pr__DOT__body_left),16);
        bufp->chgIData(oldp+37,(vlSelfRef.tb_top__DOT__u_prg__DOT__ingress_last),32);
        bufp->chgCData(oldp+38,((0xffU & vlSelfRef.tb_top__DOT__u_prg__DOT__p2l_bus_in[6U])),8);
        bufp->chgQData(oldp+39,((((QData)((IData)(vlSelfRef.tb_top__DOT__u_prg__DOT__p2l_bus_in[5U])) 
                                  << 0x20U) | (QData)((IData)(
                                                              vlSelfRef.tb_top__DOT__u_prg__DOT__p2l_bus_in[4U])))),64);
        bufp->chgIData(oldp+41,(vlSelfRef.tb_top__DOT__u_prg__DOT__p2l_bus_in[3U]),32);
        bufp->chgIData(oldp+42,(vlSelfRef.tb_top__DOT__u_prg__DOT__p2l_bus_in[2U]),32);
        bufp->chgIData(oldp+43,(vlSelfRef.tb_top__DOT__u_prg__DOT__p2l_bus_in[1U]),32);
        bufp->chgIData(oldp+44,(vlSelfRef.tb_top__DOT__u_prg__DOT__p2l_bus_in[0U]),32);
        bufp->chgCData(oldp+45,((0xffU & vlSelfRef.tb_top__DOT__u_prg__DOT__p2l_bus_out[6U])),8);
        bufp->chgIData(oldp+46,(vlSelfRef.tb_top__DOT__u_prg__DOT__p2l_bus_out[3U]),32);
        bufp->chgIData(oldp+47,(vlSelfRef.tb_top__DOT__u_prg__DOT__p2l_bus_out[2U]),32);
        bufp->chgIData(oldp+48,(vlSelfRef.tb_top__DOT__u_prg__DOT__p2l_bus_out[1U]),32);
        bufp->chgIData(oldp+49,(vlSelfRef.tb_top__DOT__u_prg__DOT__p2l_bus_out[0U]),32);
        bufp->chgCData(oldp+50,((0xffU & vlSelfRef.tb_top__DOT__u_prg__DOT__l2t_bus_in[5U])),8);
        bufp->chgIData(oldp+51,(vlSelfRef.tb_top__DOT__u_prg__DOT__l2t_bus_in[4U]),32);
        bufp->chgIData(oldp+52,(vlSelfRef.tb_top__DOT__u_prg__DOT__l2t_bus_in[3U]),32);
        bufp->chgIData(oldp+53,(vlSelfRef.tb_top__DOT__u_prg__DOT__l2t_bus_in[2U]),32);
        bufp->chgIData(oldp+54,(vlSelfRef.tb_top__DOT__u_prg__DOT__l2t_bus_in[1U]),32);
        bufp->chgIData(oldp+55,(vlSelfRef.tb_top__DOT__u_prg__DOT__l2t_bus_in[0U]),32);
        bufp->chgIData(oldp+56,(vlSelfRef.tb_top__DOT__u_prg__DOT__l2t_bus_out[4U]),32);
        bufp->chgIData(oldp+57,(vlSelfRef.tb_top__DOT__u_prg__DOT__l2t_bus_out[3U]),32);
        bufp->chgIData(oldp+58,(vlSelfRef.tb_top__DOT__u_prg__DOT__l2t_bus_out[2U]),32);
        bufp->chgIData(oldp+59,(vlSelfRef.tb_top__DOT__u_prg__DOT__l2t_bus_out[1U]),32);
        bufp->chgIData(oldp+60,(vlSelfRef.tb_top__DOT__u_prg__DOT__l2t_bus_out[0U]),32);
        bufp->chgBit(oldp+61,(vlSelfRef.tb_top__DOT__u_prg__DOT__s1__DOT__saved_valid));
        bufp->chgCData(oldp+62,(vlSelfRef.tb_top__DOT__u_prg__DOT__s1__DOT__saved_data),8);
        bufp->chgWData(oldp+63,(vlSelfRef.tb_top__DOT__u_prg__DOT__p2l_bus_in),200);
        bufp->chgWData(oldp+70,(vlSelfRef.tb_top__DOT__u_prg__DOT__p2l_bus_out),200);
        bufp->chgBit(oldp+77,(vlSelfRef.tb_top__DOT__u_prg__DOT__s2__DOT__saved_valid));
        bufp->chgWData(oldp+78,(vlSelfRef.tb_top__DOT__u_prg__DOT__s2__DOT__saved_data),200);
        bufp->chgWData(oldp+85,(vlSelfRef.tb_top__DOT__u_prg__DOT__l2t_bus_in),168);
        bufp->chgWData(oldp+91,(vlSelfRef.tb_top__DOT__u_prg__DOT__l2t_bus_out),168);
        bufp->chgBit(oldp+97,(vlSelfRef.tb_top__DOT__u_prg__DOT__s3__DOT__saved_valid));
        bufp->chgWData(oldp+98,(vlSelfRef.tb_top__DOT__u_prg__DOT__s3__DOT__saved_data),168);
        bufp->chgQData(oldp+104,(vlSelfRef.tb_top__DOT__u_tl__DOT__d_order_id),64);
        bufp->chgIData(oldp+106,(vlSelfRef.tb_top__DOT__u_tl__DOT__d_volume),32);
        bufp->chgSData(oldp+107,(vlSelfRef.tb_top__DOT__u_ut__DOT__tick_cnt),12);
        bufp->chgCData(oldp+108,(vlSelfRef.tb_top__DOT__u_ut__DOT__st),2);
        bufp->chgIData(oldp+109,(vlSelfRef.tb_top__DOT__u_ut__DOT__word_reg),32);
        bufp->chgCData(oldp+110,(vlSelfRef.tb_top__DOT__u_ut__DOT__byte_idx),2);
        bufp->chgCData(oldp+111,(vlSelfRef.tb_top__DOT__u_ut__DOT__bit_idx),3);
        bufp->chgCData(oldp+112,(vlSelfRef.tb_top__DOT__u_ut__DOT__sh),8);
        bufp->chgBit(oldp+113,(((0U == (IData)(vlSelfRef.tb_top__DOT__u_ut__DOT__st)) 
                                & (IData)(vlSelfRef.tb_top__DOT__l2t_out_valid))));
    }
    bufp->chgBit(oldp+114,(vlSelfRef.clk));
    bufp->chgBit(oldp+115,(vlSelfRef.rst_n));
    bufp->chgCData(oldp+116,(vlSelfRef.rx_byte),8);
    bufp->chgBit(oldp+117,(vlSelfRef.rx_valid));
    bufp->chgBit(oldp+118,(vlSelfRef.sink_allow));
    bufp->chgBit(oldp+119,(vlSelfRef.uart_tx));
    bufp->chgBit(oldp+120,(vlSelfRef.payload_valid));
    bufp->chgCData(oldp+121,(vlSelfRef.payload_byte),8);
    bufp->chgBit(oldp+122,(vlSelfRef.field_valid));
    bufp->chgCData(oldp+123,(vlSelfRef.msg_type),8);
    bufp->chgBit(oldp+124,(vlSelfRef.decision_valid));
    bufp->chgQData(oldp+125,(vlSelfRef.order_id),64);
    bufp->chgIData(oldp+127,(vlSelfRef.price),32);
    bufp->chgIData(oldp+128,(vlSelfRef.volume),32);
    bufp->chgBit(oldp+129,(vlSelfRef.eth_crc_ok));
    bufp->chgBit(oldp+130,(vlSelfRef.eth_crc_valid));
    bufp->chgIData(oldp+131,(vlSelfRef.t_ingress),32);
    bufp->chgIData(oldp+132,(vlSelfRef.t_parser),32);
    bufp->chgIData(oldp+133,(vlSelfRef.t_parser_event),32);
    bufp->chgIData(oldp+134,(vlSelfRef.t_logic),32);
    bufp->chgIData(oldp+135,(vlSelfRef.t_decision),32);
    bufp->chgIData(oldp+136,(vlSelfRef.cycle_cnt),32);
    bufp->chgIData(oldp+137,(vlSelfRef.dbg_crc_calc),32);
    bufp->chgIData(oldp+138,(vlSelfRef.dbg_crc_recv),32);
    bufp->chgSData(oldp+139,(vlSelfRef.dbg_payload_len),16);
    bufp->chgSData(oldp+140,(vlSelfRef.dbg_total_payload),16);
    bufp->chgSData(oldp+141,(vlSelfRef.dbg_payload_cnt_last),16);
    bufp->chgBit(oldp+142,(vlSelfRef.parsed_valid_reg));
    bufp->chgCData(oldp+143,(vlSelfRef.parsed_type_reg),8);
    bufp->chgIData(oldp+144,(vlSelfRef.parsed_price_reg),32);
    bufp->chgIData(oldp+145,(vlSelfRef.parsed_volume_reg),32);
    bufp->chgBit(oldp+146,(vlSelfRef.tx_word_valid));
    bufp->chgIData(oldp+147,(vlSelfRef.tx_word_data),32);
    bufp->chgBit(oldp+148,(vlSelfRef.l2t_stall));
    bufp->chgIData(oldp+149,(vlSelfRef.l2t_stall_cycles),32);
    bufp->chgBit(oldp+150,(vlSelfRef.tb_top__DOT__uart_ready_masked));
    bufp->chgBit(oldp+151,((1U & ((~ (IData)(vlSelfRef.tb_top__DOT__u_prg__DOT__s3__DOT__saved_valid)) 
                                  | (IData)(vlSelfRef.tb_top__DOT__uart_ready_masked)))));
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

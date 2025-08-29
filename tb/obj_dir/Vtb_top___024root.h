// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtb_top.h for the primary calling header

#ifndef VERILATED_VTB_TOP___024ROOT_H_
#define VERILATED_VTB_TOP___024ROOT_H_  // guard

#include "verilated.h"


class Vtb_top__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtb_top___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    // Anonymous structures to workaround compiler member-count bugs
    struct {
        VL_IN8(clk,0,0);
        VL_IN8(rst_n,0,0);
        VL_IN8(rx_byte,7,0);
        VL_IN8(rx_valid,0,0);
        VL_IN8(sink_allow,0,0);
        VL_OUT8(uart_tx,0,0);
        VL_OUT8(payload_valid,0,0);
        VL_OUT8(payload_byte,7,0);
        VL_OUT8(field_valid,0,0);
        VL_OUT8(msg_type,7,0);
        VL_OUT8(decision_valid,0,0);
        VL_OUT8(eth_crc_ok,0,0);
        VL_OUT8(eth_crc_valid,0,0);
        VL_OUT8(parsed_valid_reg,0,0);
        VL_OUT8(parsed_type_reg,7,0);
        VL_OUT8(tx_word_valid,0,0);
        VL_OUT8(l2t_stall,0,0);
        CData/*0:0*/ tb_top__DOT__parser_ready;
        CData/*0:0*/ tb_top__DOT__uart_ready_masked;
        CData/*0:0*/ tb_top__DOT__dummy_p2l_ready;
        CData/*0:0*/ tb_top__DOT__unused_parser_ready;
        CData/*7:0*/ tb_top__DOT__decision_type;
        CData/*0:0*/ tb_top__DOT__parser_msg_start;
        CData/*7:0*/ tb_top__DOT__rx2p_out;
        CData/*0:0*/ tb_top__DOT__rx2p_out_valid;
        CData/*0:0*/ tb_top__DOT__rx2p_out_ready;
        CData/*0:0*/ tb_top__DOT__l2t_out_valid;
        CData/*0:0*/ tb_top__DOT__u_prg__DOT__s1__DOT__saved_valid;
        CData/*7:0*/ tb_top__DOT__u_prg__DOT__s1__DOT__saved_data;
        CData/*0:0*/ tb_top__DOT__u_prg__DOT__s2__DOT__saved_valid;
        CData/*0:0*/ tb_top__DOT__u_prg__DOT__s3__DOT__saved_valid;
        CData/*2:0*/ tb_top__DOT__u_eth__DOT__state;
        CData/*2:0*/ tb_top__DOT__u_eth__DOT__pre_cnt;
        CData/*3:0*/ tb_top__DOT__u_eth__DOT__crc_cnt;
        CData/*0:0*/ tb_top__DOT__u_eth__DOT__mac_match;
        CData/*0:0*/ tb_top__DOT__u_eth__DOT__this_cycle_match;
        CData/*0:0*/ tb_top__DOT__u_eth__DOT__crc_started;
        CData/*1:0*/ tb_top__DOT__u_pr__DOT__state;
        CData/*7:0*/ tb_top__DOT__u_pr__DOT__len_hi;
        CData/*7:0*/ tb_top__DOT__u_pr__DOT__len_lo;
        CData/*7:0*/ tb_top__DOT__u_pr__DOT__type_reg;
        CData/*1:0*/ tb_top__DOT__u_ut__DOT__st;
        CData/*1:0*/ tb_top__DOT__u_ut__DOT__byte_idx;
        CData/*2:0*/ tb_top__DOT__u_ut__DOT__bit_idx;
        CData/*7:0*/ tb_top__DOT__u_ut__DOT__sh;
        CData/*0:0*/ tb_top__DOT__u_ut__DOT__accept;
        CData/*0:0*/ __VstlFirstIteration;
        CData/*0:0*/ __VicoFirstIteration;
        CData/*0:0*/ __Vtrigprevexpr___TOP__clk__0;
        CData/*0:0*/ __Vtrigprevexpr___TOP__rst_n__0;
        CData/*0:0*/ __VactContinue;
        VL_OUT16(dbg_payload_len,15,0);
        VL_OUT16(dbg_total_payload,15,0);
        VL_OUT16(dbg_payload_cnt_last,15,0);
        SData/*15:0*/ tb_top__DOT__u_eth__DOT__hdr_cnt;
        SData/*15:0*/ tb_top__DOT__u_eth__DOT__payload_cnt;
        SData/*15:0*/ tb_top__DOT__u_eth__DOT__payload_len;
        SData/*15:0*/ tb_top__DOT__u_eth__DOT__total_payload;
        SData/*15:0*/ tb_top__DOT__u_pr__DOT__length;
        SData/*15:0*/ tb_top__DOT__u_pr__DOT__cnt;
        SData/*15:0*/ tb_top__DOT__u_pr__DOT__body_left;
        SData/*11:0*/ tb_top__DOT__u_ut__DOT__tick_cnt;
        VL_OUT(price,31,0);
        VL_OUT(volume,31,0);
    };
    struct {
        VL_OUT(t_ingress,31,0);
        VL_OUT(t_parser,31,0);
        VL_OUT(t_parser_event,31,0);
        VL_OUT(t_logic,31,0);
        VL_OUT(t_decision,31,0);
        VL_OUT(cycle_cnt,31,0);
        VL_OUT(dbg_crc_calc,31,0);
        VL_OUT(dbg_crc_recv,31,0);
        VL_OUT(parsed_price_reg,31,0);
        VL_OUT(parsed_volume_reg,31,0);
        VL_OUT(tx_word_data,31,0);
        VL_OUT(l2t_stall_cycles,31,0);
        IData/*31:0*/ tb_top__DOT__t_ingress_unused;
        IData/*31:0*/ tb_top__DOT__decision_data;
        IData/*31:0*/ tb_top__DOT__u_prg__DOT__ingress_last;
        VlWide<7>/*199:0*/ tb_top__DOT__u_prg__DOT__s2__DOT__saved_data;
        VlWide<6>/*167:0*/ tb_top__DOT__u_prg__DOT__s3__DOT__saved_data;
        IData/*31:0*/ tb_top__DOT__u_eth__DOT__crc_reg;
        IData/*31:0*/ tb_top__DOT__u_eth__DOT__crc_recv_shift;
        IData/*31:0*/ tb_top__DOT__u_eth__DOT__next_crc;
        IData/*31:0*/ tb_top__DOT__u_eth__DOT__fcs_word;
        IData/*31:0*/ tb_top__DOT__u_eth__DOT__unnamedblk2__DOT__new_fcs;
        IData/*31:0*/ tb_top__DOT__u_tl__DOT__d_volume;
        IData/*31:0*/ tb_top__DOT__u_ut__DOT__word_reg;
        IData/*31:0*/ __VactIterCount;
        VL_OUT64(order_id,63,0);
        VlWide<7>/*199:0*/ tb_top__DOT__u_prg__DOT__p2l_bus_in;
        VlWide<7>/*199:0*/ tb_top__DOT__u_prg__DOT__p2l_bus_out;
        VlWide<6>/*167:0*/ tb_top__DOT__u_prg__DOT__l2t_bus_in;
        VlWide<6>/*167:0*/ tb_top__DOT__u_prg__DOT__l2t_bus_out;
        QData/*47:0*/ tb_top__DOT__u_eth__DOT__dest_mac_shift;
        QData/*47:0*/ tb_top__DOT__u_eth__DOT__full_dest;
        QData/*63:0*/ tb_top__DOT__u_tl__DOT__d_order_id;
        VlUnpacked<CData/*0:0*/, 2> __Vm_traceActivity;
    };
    VlTriggerVec<1> __VstlTriggered;
    VlTriggerVec<1> __VicoTriggered;
    VlTriggerVec<2> __VactTriggered;
    VlTriggerVec<2> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vtb_top__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vtb_top___024root(Vtb_top__Syms* symsp, const char* v__name);
    ~Vtb_top___024root();
    VL_UNCOPYABLE(Vtb_top___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard

// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vtb_top__pch.h"
#include "verilated_vcd_c.h"

//============================================================
// Constructors

Vtb_top::Vtb_top(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vtb_top__Syms(contextp(), _vcname__, this)}
    , clk{vlSymsp->TOP.clk}
    , rst_n{vlSymsp->TOP.rst_n}
    , rx_byte{vlSymsp->TOP.rx_byte}
    , rx_valid{vlSymsp->TOP.rx_valid}
    , sink_allow{vlSymsp->TOP.sink_allow}
    , uart_tx{vlSymsp->TOP.uart_tx}
    , payload_valid{vlSymsp->TOP.payload_valid}
    , payload_byte{vlSymsp->TOP.payload_byte}
    , field_valid{vlSymsp->TOP.field_valid}
    , msg_type{vlSymsp->TOP.msg_type}
    , decision_valid{vlSymsp->TOP.decision_valid}
    , eth_crc_ok{vlSymsp->TOP.eth_crc_ok}
    , eth_crc_valid{vlSymsp->TOP.eth_crc_valid}
    , parsed_valid_reg{vlSymsp->TOP.parsed_valid_reg}
    , parsed_type_reg{vlSymsp->TOP.parsed_type_reg}
    , tx_word_valid{vlSymsp->TOP.tx_word_valid}
    , l2t_stall{vlSymsp->TOP.l2t_stall}
    , dbg_payload_len{vlSymsp->TOP.dbg_payload_len}
    , dbg_total_payload{vlSymsp->TOP.dbg_total_payload}
    , dbg_payload_cnt_last{vlSymsp->TOP.dbg_payload_cnt_last}
    , price{vlSymsp->TOP.price}
    , volume{vlSymsp->TOP.volume}
    , t_ingress{vlSymsp->TOP.t_ingress}
    , t_parser{vlSymsp->TOP.t_parser}
    , t_parser_event{vlSymsp->TOP.t_parser_event}
    , t_logic{vlSymsp->TOP.t_logic}
    , t_decision{vlSymsp->TOP.t_decision}
    , cycle_cnt{vlSymsp->TOP.cycle_cnt}
    , dbg_crc_calc{vlSymsp->TOP.dbg_crc_calc}
    , dbg_crc_recv{vlSymsp->TOP.dbg_crc_recv}
    , parsed_price_reg{vlSymsp->TOP.parsed_price_reg}
    , parsed_volume_reg{vlSymsp->TOP.parsed_volume_reg}
    , tx_word_data{vlSymsp->TOP.tx_word_data}
    , l2t_stall_cycles{vlSymsp->TOP.l2t_stall_cycles}
    , order_id{vlSymsp->TOP.order_id}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vtb_top::Vtb_top(const char* _vcname__)
    : Vtb_top(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vtb_top::~Vtb_top() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vtb_top___024root___eval_debug_assertions(Vtb_top___024root* vlSelf);
#endif  // VL_DEBUG
void Vtb_top___024root___eval_static(Vtb_top___024root* vlSelf);
void Vtb_top___024root___eval_initial(Vtb_top___024root* vlSelf);
void Vtb_top___024root___eval_settle(Vtb_top___024root* vlSelf);
void Vtb_top___024root___eval(Vtb_top___024root* vlSelf);

void Vtb_top::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vtb_top::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vtb_top___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_activity = true;
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        vlSymsp->__Vm_didInit = true;
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vtb_top___024root___eval_static(&(vlSymsp->TOP));
        Vtb_top___024root___eval_initial(&(vlSymsp->TOP));
        Vtb_top___024root___eval_settle(&(vlSymsp->TOP));
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vtb_top___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vtb_top::eventsPending() { return false; }

uint64_t Vtb_top::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "%Error: No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* Vtb_top::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vtb_top___024root___eval_final(Vtb_top___024root* vlSelf);

VL_ATTR_COLD void Vtb_top::final() {
    Vtb_top___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vtb_top::hierName() const { return vlSymsp->name(); }
const char* Vtb_top::modelName() const { return "Vtb_top"; }
unsigned Vtb_top::threads() const { return 1; }
void Vtb_top::prepareClone() const { contextp()->prepareClone(); }
void Vtb_top::atClone() const {
    contextp()->threadPoolpOnClone();
}
std::unique_ptr<VerilatedTraceConfig> Vtb_top::traceConfig() const {
    return std::unique_ptr<VerilatedTraceConfig>{new VerilatedTraceConfig{false, false, false}};
};

//============================================================
// Trace configuration

void Vtb_top___024root__trace_decl_types(VerilatedVcd* tracep);

void Vtb_top___024root__trace_init_top(Vtb_top___024root* vlSelf, VerilatedVcd* tracep);

VL_ATTR_COLD static void trace_init(void* voidSelf, VerilatedVcd* tracep, uint32_t code) {
    // Callback from tracep->open()
    Vtb_top___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtb_top___024root*>(voidSelf);
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (!vlSymsp->_vm_contextp__->calcUnusedSigs()) {
        VL_FATAL_MT(__FILE__, __LINE__, __FILE__,
            "Turning on wave traces requires Verilated::traceEverOn(true) call before time 0.");
    }
    vlSymsp->__Vm_baseCode = code;
    tracep->pushPrefix(std::string{vlSymsp->name()}, VerilatedTracePrefixType::SCOPE_MODULE);
    Vtb_top___024root__trace_decl_types(tracep);
    Vtb_top___024root__trace_init_top(vlSelf, tracep);
    tracep->popPrefix();
}

VL_ATTR_COLD void Vtb_top___024root__trace_register(Vtb_top___024root* vlSelf, VerilatedVcd* tracep);

VL_ATTR_COLD void Vtb_top::trace(VerilatedVcdC* tfp, int levels, int options) {
    if (tfp->isOpen()) {
        vl_fatal(__FILE__, __LINE__, __FILE__,"'Vtb_top::trace()' shall not be called after 'VerilatedVcdC::open()'.");
    }
    if (false && levels && options) {}  // Prevent unused
    tfp->spTrace()->addModel(this);
    tfp->spTrace()->addInitCb(&trace_init, &(vlSymsp->TOP));
    Vtb_top___024root__trace_register(&(vlSymsp->TOP), tfp->spTrace());
}

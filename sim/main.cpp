#include "Vtb_top.h"
#include "verilated.h"

#include <fstream>
#include <vector>
#include <cstdint>
#include <iomanip>
#include <algorithm>
#include <iterator>
#include <string>

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    Vtb_top* top = new Vtb_top;

    // -------- Load raw Ethernet+ITCH frames --------
    std::vector<uint8_t> packet_bytes;
    {
        std::ifstream in("../messages/packets.bin", std::ios::binary);
        packet_bytes.assign(std::istreambuf_iterator<char>(in),
                            std::istreambuf_iterator<char>());
    }

    // -------- Open outputs --------
    std::ofstream uart_out    ("../sim/output_capture.txt");
    std::ofstream payload_out ("../sim/payload_capture.txt");
    std::ofstream parser_out  ("../sim/parser_log.txt");
    std::ofstream decision_out("../sim/decision_log.txt");
    std::ofstream crc_out     ("../sim/crc_log.txt");
    std::ofstream lat_out     ("../sim/latencies.csv");
    std::ofstream bp_out      ("../sim/backpressure_log.txt");
    lat_out << "ingress,parser,logic,decision,parser_lat,logic_lat,total_lat\n";

    // -------- Reset --------
    top->clk      = 0;
    top->rst_n    = 0;
    top->rx_valid = 0;
    top->sink_allow = 1;
    top->eval();
    for (int i = 0; i < 10; i++) {
        top->clk = !top->clk;
        top->eval();
    }
    top->rst_n = 1;
    top->eval();

    // -------- Helpers (edge-detected TX logging, event logging) --------
    bool prev_tx_word_valid = false;
    int stall_ctr = 0;

     auto apply_backpressure = [&](){
        // Periodic stall: 200 cycles stall every 2000 cycles (deterministic)
        stall_ctr = (stall_ctr + 1) % 2000;
        bool allow = (stall_ctr < 1800);    // 1800 allow, 200 stall
        top->sink_allow = allow ? 1 : 0;
    };

    auto log_backpressure = [&](){
        if (top->l2t_stall) {
            bp_out << "STALL @" << top->cycle_cnt << "\n";
        }
    };

    auto log_txword_edge = [&]() {
        bool cur = top->tx_word_valid;
        if (cur && !prev_tx_word_valid) {
            parser_out << "TXWORD @" << top->cycle_cnt
                       << " 0x" << std::hex << std::setw(8) << std::setfill('0')
                       << top->tx_word_data << std::dec << "\n";
        }
    };

    auto log_parser = [&]() {
        if (top->parsed_valid_reg) {
            parser_out << "PARSED @" << top->t_parser_event
                       << " type="   << char(top->parsed_type_reg)
                       << " price="  << std::dec << top->parsed_price_reg
                       << " volume=" << top->parsed_volume_reg << "\n";
        }
    };

    auto log_decision = [&]() {
        bool cur = top->tx_word_valid;
        if (cur && !prev_tx_word_valid) {
            decision_out << "DECISION @" << top->t_decision
                        << " data=0x" << std::hex << std::setw(8) << std::setfill('0')
                        << top->tx_word_data << std::dec << "\n";
        }
    };

    auto log_crc = [&]() {
        if (top->eth_crc_valid) {
            crc_out << std::hex
                    << "CRC " << (top->eth_crc_ok ? "PASS" : "FAIL")
                    << " calc=0x" << std::setw(8) << std::setfill('0') << top->dbg_crc_calc
                    << " recv=0x" << std::setw(8) << std::setfill('0') << top->dbg_crc_recv
                    << std::dec
                    << " bytes_crc="     << top->dbg_payload_cnt_last
                    << " itch_len="       << top->dbg_payload_len
                    << " total_payload="  << top->dbg_total_payload
                    << " at cycle "       << top->cycle_cnt << "\n";
        }
    };

    auto log_latency_on_tx_accept = [&]() {
        bool cur = top->tx_word_valid;
        if (cur && !prev_tx_word_valid) {
            // Compute latencies *from raw timestamps* here
            auto U32 = [](uint64_t x){ return static_cast<uint32_t>(x); };
            const uint64_t MOD = 1ull<<32;

            auto wrap_delta = [&](uint32_t a, uint32_t b){
                return static_cast<uint32_t>((uint64_t(b) + MOD - uint64_t(a)) % MOD);
            };

            uint32_t ingress  = top->t_ingress;
            uint32_t parser_t = top->t_parser;
            uint32_t logic_t  = top->t_logic;
            uint32_t decision = top->t_decision;

            uint32_t parser_lat = wrap_delta(ingress,  parser_t);
            uint32_t logic_lat  = wrap_delta(parser_t, logic_t);
            uint32_t total_lat  = wrap_delta(ingress,  decision);

            // CSV header (once): ingress,parser,logic,decision,parser_lat,logic_lat,total_lat
            lat_out << ingress << "," << parser_t << "," << logic_t << "," << decision << ","
                    << parser_lat << "," << logic_lat << "," << total_lat << "\n";
        }
    };

    auto log_payload = [&]() {
        if (top->payload_valid) {
            payload_out << std::hex << std::setw(2) << std::setfill('0')
                        << int(top->payload_byte) << "\n";
        }
    };

    auto tick_one_cycle = [&](){
        apply_backpressure();  // set sink_allow before cycle
        top->clk = 0; top->eval();
        top->clk = 1; top->eval();

        // capture exactly once per full clock
        uart_out << int(top->uart_tx) << "\n";

        // log events once per cycle (prevents duplicates)
        log_payload();
        log_parser();
        log_crc();
        log_latency_on_tx_accept();
        log_txword_edge();
        log_decision();
        log_backpressure();

        prev_tx_word_valid = top->tx_word_valid;
    };

    // -------- Feed bytes (one full cycle per byte) --------
    for (auto byte : packet_bytes) {
        top->rx_byte  = byte;
        top->rx_valid = 1;

        tick_one_cycle(); // one full cycle per byte
    }

    // -------- Drain: stop driving input, let pipeline/UART finish --------
    top->rx_valid = 0;
    top->eval();

    // Give plenty of time for UART (slow) to flush; ~2M cycles is safe
    const int timeout_cycles = 2'000'000;
    for (int i = 0; i < timeout_cycles; ++i) {
        tick_one_cycle(); // one full cycle
    }

    // -------- Tidy --------
    uart_out.close();
    payload_out.close();
    parser_out.close();
    decision_out.close();
    crc_out.close();
    lat_out.close();

    delete top;
    return 0;
}
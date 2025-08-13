// Verilator Testbench for tb_top
//
// Purpose:
//   Simulates the top-level FPGA design (tb_top) by feeding in
//   Ethernet + ITCH packet data, driving the clock/reset, and
//   logging various internal events to multiple output files.
//
// Key features:
//   • Loads a binary packet capture and feeds bytes to DUT
//   • Applies periodic backpressure to simulate downstream stalls
//   • Logs UART TX output, parsed payload, parser events,
//     decision outputs, CRC check results, and latency breakdowns
//   • Drains the pipeline to allow UART transmission to complete
//
// Outputs:
//   - output_capture.txt       : UART bitstream log
//   - payload_capture.txt      : Hex dump of payload bytes
//   - parser_log.txt           : Parsed message fields + TX words
//   - decision_log.txt         : Decision outputs from trading logic
//   - crc_log.txt              : Ethernet CRC pass/fail with debug info
//   - latencies.csv            : Timestamps & computed latencies
//   - backpressure_log.txt     : Records stall events

#include "Vtb_top.h"           // Verilated model header for top module
#include "verilated.h"         // Verilator core API

#include <fstream>
#include <vector>
#include <cstdint>
#include <iomanip>
#include <algorithm>
#include <iterator>
#include <string>

int main(int argc, char** argv) {

    // Pass command-line arguments into Verilated simulation
    Verilated::commandArgs(argc, argv);

    // Instantiate the top-level DUT
    Vtb_top* top = new Vtb_top;

    // Load raw Ethernet+ITCH frames
    std::vector<uint8_t> packet_bytes;
    {
        std::ifstream in("../messages/packets.bin", std::ios::binary);
        packet_bytes.assign(std::istreambuf_iterator<char>(in),
                            std::istreambuf_iterator<char>());
    }

    // Open output files
    std::ofstream uart_out    ("../sim/output_capture.txt");
    std::ofstream payload_out ("../sim/payload_capture.txt");
    std::ofstream parser_out  ("../sim/parser_log.txt");
    std::ofstream decision_out("../sim/decision_log.txt");
    std::ofstream crc_out     ("../sim/crc_log.txt");
    std::ofstream lat_out     ("../sim/latencies.csv");
    std::ofstream bp_out      ("../sim/backpressure_log.txt");
    lat_out << "ingress,parser,logic,decision,parser_lat,logic_lat,total_lat\n";

    // Reset DUT
    top->clk      = 0;
    top->rst_n    = 0;
    top->rx_valid = 0;
    top->sink_allow = 1;
    top->eval();

    // 10 half-cycles with reset asserted
    for (int i = 0; i < 10; i++) {
        top->clk = !top->clk;
        top->eval();
    }

    // Deassert reset
    top->rst_n = 1;
    top->eval();

    // Helpers for event logging
    bool prev_tx_word_valid = false;   // edge detection state
    int stall_ctr = 0;                // backpressure counter

    // Simulate periodic downstream backpressure (200 cycles stall / 2000 cycles total)
    auto apply_backpressure = [&](){
        stall_ctr = (stall_ctr + 1) % 2000;
        bool allow = (stall_ctr < 1800);    // 1800 allow, 200 stall
        top->sink_allow = allow ? 1 : 0;
    };

    // Log when the downstream is stalled
    auto log_backpressure = [&](){
        if (top->l2t_stall) {
            bp_out << "STALL @" << top->cycle_cnt << "\n";
        }
    };

    // Log when TX word valid rises
    auto log_txword_edge = [&]() {
        bool cur = top->tx_word_valid;
        if (cur && !prev_tx_word_valid) {
            parser_out << "TXWORD @" << top->cycle_cnt
                       << " 0x" << std::hex << std::setw(8) << std::setfill('0')
                       << top->tx_word_data << std::dec << "\n";
        }
    };

    // Log parsed ITCH message fields
    auto log_parser = [&]() {
        if (top->parsed_valid_reg) {
            parser_out << "PARSED @" << top->t_parser_event
                       << " type="   << char(top->parsed_type_reg)
                       << " price="  << std::dec << top->parsed_price_reg
                       << " volume=" << top->parsed_volume_reg << "\n";
        }
    };

    // Log decision output events
    auto log_decision = [&]() {
        bool cur = top->tx_word_valid;
        if (cur && !prev_tx_word_valid) {
            decision_out << "DECISION @" << top->t_decision
                        << " data=0x" << std::hex << std::setw(8) << std::setfill('0')
                        << top->tx_word_data << std::dec << "\n";
        }
    };

    // Log Ethernet CRC results with debug counters
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

    // Log latency from ingress to parser to logic to decision
    auto log_latency_on_tx_accept = [&]() {
        bool cur = top->tx_word_valid;
        if (cur && !prev_tx_word_valid) {

            // Compute latencies from raw timestamps
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

    // Log payload bytes in hex
    auto log_payload = [&]() {
        if (top->payload_valid) {
            payload_out << std::hex << std::setw(2) << std::setfill('0')
                        << int(top->payload_byte) << "\n";
        }
    };

    // Advance simulation by one full clock cycle and log all events
    auto tick_one_cycle = [&](){
        apply_backpressure();  // update sink_allow before tick
        top->clk = 0; top->eval();
        top->clk = 1; top->eval();

        // UART TX bit capture (once per full cycle)
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

    // Feed packet bytes into DUT (1 cycle per byte)
    for (auto byte : packet_bytes) {
        top->rx_byte  = byte;
        top->rx_valid = 1;

        tick_one_cycle(); // one full cycle per byte
    }

    // Stop driving input; let pipeline drain
    top->rx_valid = 0;
    top->eval();

    // Give plenty of time for slow UART to flush; ~2M cycles is safe
    const int timeout_cycles = 2'000'000;
    for (int i = 0; i < timeout_cycles; ++i) {
        tick_one_cycle();
    }

    // Close logs and cleanup
    uart_out.close();
    payload_out.close();
    parser_out.close();
    decision_out.close();
    crc_out.close();
    lat_out.close();

    delete top;
    return 0;
}
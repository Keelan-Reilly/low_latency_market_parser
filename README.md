# Ultra-Low-Latency FPGA Trading Interface

This project is a small, end-to-end trading system built on FPGA hardware. It takes in a market-data feed, parses it, applies a simple trading rule, and sends out a decision in ~152 ns (38 cycles) from igress to output at 250 MHZ. It demonstrates how FPGA pipelines can be used for ultra-low-latency decision-making in a realistic market-data processing workflow.

Pipeline:

- Ethernet byte stream → ITCH parser → simple trading rule → UART transmit
- Fall-through ready/valid handshakes (1-deep skid buffers) with lossless backpressure
- Early dispatch in parser (pulses on the last price byte), zero bubbles into trading logic
- Cycle-accurate timestamps per message (ingress, parser exit, logic/decision)
- Reference Python parser to cross-check RTL outputs

---

### Key Results
- **Latency:** ~152 ns ingress→decision at 250 MHz (38 cycles in simulation).
- **Footprint:** Lossless backpressure, tiny hardware resource use.
- **Clock target:** Design closes at 250 MHz with headroom.

---

### Recent Changes
- Reduced parser/logic boundaries to remove bubbles
- Early dispatch of parsed fields on last price byte
- UART TX optimized to accept decisions without delay

---

### FPGA Build
- **Device:** xc7a200tfbg676-2
- **Top module:** `fpga_top.sv` instantiates all stages and UART output.
- **Timing:** Meets 250 MHz constraint with WNS +0.009 ns. (OUT OF DATE)
- **Reports:** `vivado/` folder contains `utilization.rpt`, `timing_summary.rpt`, `messages.log`.

---

## What this project contains

### RTL modules (SystemVerilog)


- **`hdl/fpga_top.sv`** — Synthesis top-level for Vivado; instantiates Ethernet RX, parser, trading logic, pipeline registers, and UART TX.
- **`hdl/eth_rx.sv`** — Ethernet byte-stream receiver. Detects preamble/SFD, filters Destination MAC (our MAC or broadcast), streams payload, computes CRC-32 (IEEE 802.3), checks FCS.
- **`hdl/parser.sv`** — ITCH message parser. Reads length (2B) + type (1B). For type ‘P’ (Trade, non-cross) it extracts order_id, price, volume.
- **`hdl/trading_logic.sv`** — Very simple rule: if type='P' and price < THRESHOLD, emit a decision.
- **`hdl/uart_tx.sv`** — UART transmitter. Sends a 32-bit word as 4 bytes (8N1), LSB-first within each byte, little-endian byte order.
- **`hdl/pipeline_regs.sv`** — Fall-through stage boundaries (skid buffers) between RX ↔ Parser, Parser ↔ Logic, Logic ↔ TX. Carries per-message timestamps so you can compute stage latencies.
- **`hdl/tb_top.sv`** — Testbench top module.

### Simulation (Verilator)

- **`tb/main.cpp`** — Verilator harness with UART decoding, timestamp capture, and backpressure.

### Bench / reference

- **`bench/reference_parser.py`** — “Golden” offline parser that reads messages/packets.bin, re-checks CRC, decodes the same fields as RTL, and writes CSVs.
- **`bench/compare_outputs.py`** — Compares the reference parse to the RTL sim/parser_log.txt.

### Packet generation

- **`bench/build_itch_from_gzpart.py`** - Converts real Nasdaq ITCH dumps into valid Ethernet frames.

---

# Quick start

## 1) Generate test packets from a .gz.part (real ITCH sample)

```bash
# From repo root
python bench/build_itch_from_gzpart.py --source itch_sample.gz.part
# Optional:
#   --limit N     # cap number of ITCH messages (helps avoid multi-GB outputs)
#   --skip K      # skip K ITCH messages first (e.g., to reach first 'P' trade)
# Examples:
python bench/build_itch_from_gzpart.py --source itch_sample.gz.part --skip 240000 --limit 100000
```

This creates:

- `messages/packets.bin` — byte-accurate Ethernet frames (with preamble and FCS)
- `messages/sample.mem` — the same frames, one byte per line in hex

> Real ITCH is huge. Use `--limit` to keep sample.mem reasonable.

## 2) Build and run the Verilator simulation

```bash
make run
```

Outputs (in `sim/`):

- `parser_log.txt` — lines like PARSED @<cycle> type=P price=... volume=...
- `decision_log.txt` — lines like DECISION @<cycle> data=0x...
- `crc_log.txt` — per-frame CRC PASS/FAIL and folded byte counts
- `latencies.csv` — raw timestamps + per-stage + end-to-end latencies (cycles)
- `output_capture.txt` — UART line state per clock (bit-level view)
- `vlt_dump.vcd` — waveform dump for GTKWave
- `backpressure_log.txt` — when we intentionally stall the TX sink in the test

The harness periodically de-asserts sink readiness to prove backpressure is working. You’ll see gaps between PARSED and TXWORD/DECISION during those forced stalls.

## 3) Cross-check RTL vs reference

```bash
# Parse packets.bin with the Python "golden" reference
python bench/reference_parser.py

# Compare to the RTL log
python bench/compare_outputs.py
```

You will get `reference_parsed.csv` and (if the rule triggers) `reference_decisions.csv`, plus a pass/fail report from the comparator.

---

## Results

### Functional (simulation)

End-to-end latency measured from the Verilator log (`sim/latencies.csv`):

| t_ingress | t_parser | t_logic | t_decision | parser_lat (cyc) | logic_lat (cyc) | total_lat (cyc) |
|-----------|----------|---------|------------|------------------|-----------------|-----------------|
| 239381    | 239419   | 239419  | 239419     | 38               | 0               | **38**          |
| 239453    | 239491   | 239491  | 239491     | 38               | 0               | **38**          |

**38 cycles at 250 MHz ≈ 152 ns**

---

### Implementation (Vivado 2025.1)

Note: Vivado reports are out-of-date and were last generated from a previous revision of the design.

**Device:** `xc7a200tfbg676-2` • **Design state:** Routed

**Clocking**
- `core_clk` waveform `{0.000 2.000}` → **Period 4.000 ns (250 MHz)**

**Timing summary**
- **All constraints met**
- **WNS (setup): +0.009 ns**
- **WHS (hold): +0.152 ns**
- **PW slack:** +1.500 ns

---

## Requirements

- Verilator (build and run sim)
- Python 3.9+
- No network needed for .gz.part path.

---

## How the data flows

### eth_rx

- Looks for 7×0x55 preamble then 0xD5 SFD.
- Filters Destination MAC (constant OUR_MAC or broadcast).
- Streams payload bytes (`payload_byte`, `payload_valid`/`payload_ready`).
- Computes CRC-32 (802.3, reflected) over header+payload, ingests FCS (LSB-first), and reports `crc_valid` + `crc_ok`.

### parser

- Reads length MSB, length LSB, type.
- For type 'P', accumulates big-endian order_id (8B), volume (4B), price (4B).
- **Early-dispatch:** pulses `field_valid` *on the cycle the last price byte arrives* (no extra wait).
- Never back-pressures upstream (`in_ready=1`).

### pipeline_regs

- One-register isolators between stages (RX↔Parser, Parser↔Logic, Logic↔UART).
- Carries per-message timestamps: on `msg_start` (ingress), at parser exit, and when a decision is accepted.
- Exposes `t_ingress`, `t_parser`, `t_logic`, `t_decision` so the harness can log stage and end-to-end latency.

### trading_logic

- Rule: if type=='P' and price < THRESHOLD → emit a decision (word encodes price).
- Parameter: THRESHOLD (default 2_000_000, i.e. 200.0000 in $/1e4).

### uart_tx

- Sends the 32-bit decision as four bytes, each 8N1.
- LSB-first within each byte, little-endian byte order.
- Parameters: CLK_FREQ_HZ (default 100 MHz), BAUD_RATE (default 115200).

---

## Backpressure & timing

Every stage uses a valid/ready handshake. Data only moves when both are true.

The test harness periodically lowers the TX sink’s “ready” (via `sink_allow`) to prove the pipeline holds data and does not lose bytes or messages.

When backpressure is active, you’ll see PARSED events continue (parser output is buffered) while TXWORD/DECISION is delayed. That’s expected.

---

## Configuration

- **ETH MAC filter** — `hdl/eth_rx.sv`: `OUR_MAC` constant
- **Trading rule** — `hdl/trading_logic.sv`: `THRESHOLD` parameter
- **UART timing** — `hdl/uart_tx.sv`: `CLK_FREQ_HZ`, `BAUD_RATE`
- **Backpressure pattern (sim only)** — `sim/main.cpp`: `apply_backpressure()` (e.g., 1800 cycles allow, 200 stall)
- **Packet generation** — `tools/build_itch_from_gzpart.py`: `--skip`, `--limit`, `--dst-mac`, `--src-mac`, `--ethertype`

---

## Repository layout 

```python
.
├─ bench/
├─ docs/
├─ hdl/
├─ messages/
├─ sim/
├─ tb/
├─ vivado/
├─ itch_sample.gz.part
├─ Makefile
└─ README.md

```

---

## Notes and Limitations 

- Only basic ITCH message parsing and a single hardcoded trading rule are implemented.
- No support for multiple symbols, users, or sessions.
- Security, error handling, and compliance features are not included.
- The design is not intended for production use, high throughput, or distributed operation.
- UART output and simulation scripts are for demonstration only.
- Hardware portability and scalability are not considered.
- Documentation and testing are minimal and focused on illustrating core concepts.




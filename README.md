# Ultra-Low-Latency FPGA Trading Interface

A tiny, end-to-end market-data pipeline:

- Ethernet byte stream → ITCH parser → simple trading rule → UART transmit
- Deterministic ready/valid handshakes with lossless backpressure
- Cycle-accurate timestamps per message (ingress, parser exit, logic/decision)
- Reference Python parser to cross-check RTL outputs

---

## What this project contains

### RTL modules (SystemVerilog)

- **`hdl/eth_rx.sv`** — Ethernet byte-stream receiver. Detects preamble/SFD, filters Destination MAC (our MAC or broadcast), streams payload, computes CRC-32 (IEEE 802.3), checks FCS.
- **`hdl/parser.sv`** — ITCH message parser. Reads length (2B) + type (1B). For type ‘P’ (Trade, non-cross) it extracts order_id, price, volume.
- **`hdl/trading_logic.sv`** — Very simple rule: if type='P' and price < THRESHOLD, emit a decision.
- **`hdl/uart_tx.sv`** — UART transmitter. Sends a 32-bit word as 4 bytes (8N1), LSB-first within each byte, little-endian byte order.
- **`hdl/pipeline_regs.sv`** — One-register boundaries between RX ↔ Parser, Parser ↔ Logic, Logic ↔ TX. Carries per-message timestamps so you can compute stage latencies.

### Simulation (Verilator)

- **`sim/tb_top.sv`** — Top that wires the modules together.
- **`sim/main.cpp`** — Verilator harness. Feeds bytes from messages/packets.bin, applies periodic backpressure to exercise ready/valid, logs events and latencies.
- **`sim/run_sim.sh`** — Build & run the sim (obj_dir/sim_vlt), generate logs and vlt_dump.vcd.

### Bench / reference

- **`bench/reference_parser.py`** — “Golden” offline parser that reads messages/packets.bin, re-checks CRC, decodes the same fields as RTL, and writes CSVs.
- **`bench/compare_outputs.py`** — Compares the reference parse to the RTL sim/parser_log.txt.

### Packet generation

- **`tools/build_itch_from_gzpart.py`** — Reads a partial gzip (*.gz.part) of real Nasdaq ITCH, safely decompresses whatever is present, splits into ITCH messages, wraps each into a full Ethernet frame (preamble/SFD + header + payload + FCS), and writes:
    - `messages/packets.bin` (raw frames, concatenated)
    - `messages/sample.mem` (one hex byte per line for quick viewing)

### Documents

- **`docs/architecture.drawio`** — Block diagram (draw.io).
- **`docs/design_notes.md`** — Design notes (architecture, state machines, latency method, tests).

---

# Quick start

## 1) Generate test packets from a .gz.part (real ITCH sample)

```bash
# From repo root
python tools/build_itch_from_gzpart.py --source itch_sample.gz.part
# Optional:
#   --limit N     # cap number of ITCH messages (helps avoid multi-GB outputs)
#   --skip K      # skip K ITCH messages first (e.g., to reach first 'P' trade)
# Examples:
python tools/build_itch_from_gzpart.py --source itch_sample.gz.part --skip 240000 --limit 100000
```

This creates:

- `messages/packets.bin` — byte-accurate Ethernet frames (with preamble and FCS)
- `messages/sample.mem` — the same frames, one byte per line in hex

> Real ITCH is huge. Use `--limit` to keep sample.mem reasonable.

## 2) Build and run the Verilator simulation

```bash
cd sim
../tools/run_sim.sh
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

## Requirements

- Verilator (build and run sim)
- Python 3.9+
- No network needed for .gz.part path.

Install examples (Ubuntu):

```bash
sudo apt-get install verilator
python -m venv .venv && source .venv/bin/activate
```

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
- Pulses `field_valid` for one cycle with the decoded fields.
- Pulses `msg_start` on the very first header byte so timestamps can align per message.

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
│  ├─ analyse_latencies.py        # Analyse per-stage latencies
│  ├─ compare_outputs.py          # Diff reference vs RTL logs
│  └─ reference_parser.py         # Offline “golden” parser + CRC
├─ docs/
│  ├─ architecture.drawio         # Block diagram (draw.io)
│  ├─ design_notes.md             # Architecture, FSMs, latency, tests
│  └─ timing_diagram.svg          # UART / handshake timing diagram
├─ hdl/
│  ├─ eth_rx.sv                   # Ethernet RX
│  ├─ parser.sv                   # ITCH parser
│  ├─ pipeline_regs.sv            # Stage boundary registers
│  ├─ trading_logic.sv            # Simple trading rule
│  └─ uart_tx.sv                  # UART transmitter
├─ messages/
│  ├─ packets.bin                 # Generated Ethernet frames (binary)
│  └─ sample.mem                  # Same bytes, one per line (hex)
├─ sim/
│  ├─ backpressure_log.txt        # Backpressure stall markers
│  ├─ crc_log.txt                 # CRC PASS/FAIL report
│  ├─ decision_log.txt            # DECISION events
│  ├─ latencies.csv               # Per-message stage timings
│  ├─ main.cpp                    # Verilator harness
│  ├─ output_capture.txt          # UART line state per clock
│  ├─ parser_log.txt              # PARSED events
│  ├─ payload_capture.txt         # Payload bytes captured
│  ├─ reference_decisions.csv     # Expected DECISION events
│  ├─ reference_parsed.csv        # Expected PARSED events
│  ├─ tb_top.sv                   # Top-level SV testbench
│  └─ vlt_dump.vcd                 # Waveform dump (GTKWave)
├─ tools/
│  ├─ build_itch_from_gzpart.py   # .gz.part → packets.bin + sample.mem
│  ├─ decode_uart.py              # Optional: UART log decoder
│  └─ run_sim.sh                  # Build & run script
├─ itch_sample.gz.part            # Sample ITCH input (truncated gzip)
└─ README.md

```

---

## Notes on formats

Ethernet framing in `packets.bin` includes preamble (7×0x55), SFD (0xD5), header (DA/SA/EtherType), payload (ITCH message), and FCS (CRC-32).

FCS is stored LSB-first (wire order). The receiver computes CRC with the reflected 802.3 polynomial (init 0xFFFFFFFF, xorout 0xFFFFFFFF), excludes the SFD, and compares.

---

## Troubleshooting

- **sample.mem is huge** — Add `--limit` when you build from a real ITCH dump.
- **No ‘P’ trades near the start** — Use `--skip` to jump ahead (e.g., `--skip 240000`).
- **CRC fails** — Make sure `packets.bin` wasn’t edited; the generator recomputes FCS per frame.

- **No TX words for some PARSED lines** — Your rule didn’t trigger (price >= THRESHOLD) or TX was back-pressured at that moment (it will transmit when ready returns).


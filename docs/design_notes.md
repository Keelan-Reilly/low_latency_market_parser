# Ultra-Low-Latency Trading Interface – Design Notes

These notes document the actual architecture, protocols, control logic, pipeline design decisions, latency measurement process, and testing strategy for this ultra-low-latency trading interface project.

---

## Performance Summary

- **Latency:** ~**192 ns** ingress→decision at 250 MHz (48 cycles in simulation)
- **Timing:** Meets **250 MHz** on `xc7a200tfbg676-2` (WNS +0.009 ns, TNS 0)
- **Resource usage:** ~0.4 % LUTs, ~0.3 % FFs, 12 I/Os
- **Design state:** Fully routed with all constraints met

---

## 1. Protocol Overviews

### 1.1 Ethernet Frame Format
The interface receives and processes Ethernet frames containing market data.

- **Preamble & SFD:** 7 bytes of `0x55` followed by one Start Frame Delimiter (`0xD5`), used to synchronise with the sender.
- **Destination MAC (6 bytes):** Checked against a configured value; non-matching frames are discarded.
- **Source MAC (6 bytes)** – not used for filtering here.
- **EtherType (2 bytes):** Indicates payload type (e.g. IPv4 = `0x0800`).
- **Payload (46–1500 bytes):** Encapsulated market data message (in our case, ITCH).
- **Frame Check Sequence (4 bytes):** IEEE 802.3 CRC-32 used to confirm the frame is valid.

### 1.2 ITCH Market Data Format
- **Fixed-length binary messages** for very low latency.
- **Header:** 2-byte length and 1-byte message type.
- **Fields:** e.g. Order ID, Price, Volume, etc., each with defined size.
- ASCII protocols like FIX are not used here due to their overhead.

---

## 2. Module Breakdown

### Ethernet Receiver (`eth_rx.sv`)
- Reads incoming bytes, detects preamble/SFD, and validates the destination MAC.
- Strips Ethernet header and CRC, outputting only the payload bytes to the parser.
- Verifies CRC-32 and logs pass/fail for each frame.

### Message Parser (`parser.sv`)
- Implements a byte-driven state machine that recognises ITCH message boundaries.
- Reads length and type from the header, accumulates the remaining fields into registers, and then makes the parsed data available to the decision logic.

### Decision Logic (`trading_logic.sv`)
- Simple rule-based filter: e.g., if the message is a trade and the price is below a threshold, flag a “buy” decision.
- Can be extended for more complex strategies.

### UART Transmitter (`uart_tx.sv`)
- Converts 32-bit decision data into four serial bytes for output over UART.
- Sends each byte in **8N1 format** (1 start bit, 8 data bits LSB-first, 1 stop bit).
- Ensures complete transmission before accepting new data.

### Pipeline Registers (`pipeline_regs.sv`)
- Sits between each processing stage to improve timing stability.
- Captures timestamps at each stage for per-stage latency measurement.

### FPGA Top-Level (`fpga_top.sv`)

- Instantiates all core modules: Ethernet RX, message parser, decision logic, UART transmitter, and pipeline registers.
- Connects stage-to-stage handshakes, routes timing signals for latency measurement, and exposes I/O pins for external interfaces.
- Wraps the design for synthesis/implementation in Vivado with a 250 MHz clock constraint.

### Simulation Top-Level (`tb_top.sv`)

- Drives the DUT (Device Under Test) with Ethernet+ITCH payloads from packets.bin via a behavioural PHY model.
- Captures UART output, stage-by-stage timestamps, CRC logs, and decision events for verification.
- Used exclusively in Verilator for latency measurement and functional testing before synthesis.

---

## 3. State Machine Summaries

**`eth_rx`**
- **IDLE:** Wait for first preamble byte (`0x55`).
- **PREAMBLE:** Count 7 preamble bytes.
- **SFD:** Detect `0xD5` start frame delimiter.
- **LOAD_HEADER:** Read MAC and EtherType.
- **LOAD_PAYLD:** Pass payload bytes to parser.

**`parser`**
- **WAIT_HEADER:** Read message length and type.
- **READ_FIELDS:** Accumulate the message fields.
- **DISPATCH:** Mark parsed data as valid for one cycle.
- **SKIP:** Ignore messages that aren’t relevant.

**`uart_tx`**
- **IDLE:** Wait for valid data.
- **START:** Send UART start bit (0).
- **DATA:** Send 8 bits LSB-first.
- **STOP:** Send UART stop bit (1).
- **NEXT_BYTE/IDLE:** Either load the next byte or finish.

---

## 4. Pipeline and Latency Considerations

- **Registers between stages** reduce the length of any single combinational path, helping the design run at a higher clock speed.
- More stages = more total cycles of latency, but a higher maximum operating frequency.
- Backpressure control (ready/valid handshakes) is used to temporarily pause upstream stages if a downstream stage can’t accept new data.

---

## 5. Latency Measurement

- A global cycle counter runs throughout simulation.
- **Ingress timestamp** is taken when the first payload byte of a message arrives.
- **Stage timestamps** are recorded after parsing and after decision logic.
- **Decision timestamp** is recorded when a decision is ready to transmit.
- Stage and total latencies are written to CSV for analysis.

---

## 6. Testing and Verification

- **Simulator:** Verilator, with C++ testbench feeding captured Ethernet+ITCH data from `packets.bin`.
- Testbench applies deterministic backpressure patterns to verify stalling behaviour.
- Multiple log outputs:
  - UART output
  - Payload bytes
  - Parsed message log
  - Decision log
  - CRC results
  - Latency breakdown
- Expected vs actual behaviour compared against a Python reference parser.
- Post-route resource and timing reports are stored in `vivado/` for reproducibility.
---

## 7. Potential Optimisations

While the current design prioritises correctness and functional completeness, there are clear opportunities to reduce latency further:

- Cut-through parsing: Begin parsing fields as bytes arrive, rather than waiting for the full payload.
-Wider datapath: Process multiple bytes per cycle (e.g., 32- or 64-bit) to reduce parser cycles.
-Stage merging: Combine parser output and trading logic into a single cycle to reduce register boundaries.
-Speculative decision emission: Issue a decision before CRC check completion and retract if the CRC fails.

Based on cycle counts, these changes could reduce end-to-end latency from 48 cycles (~192 ns) to ~12–20 cycles (~40–80 ns) at 250–300 MHz.

---

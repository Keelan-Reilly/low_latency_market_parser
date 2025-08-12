Design Notes

These notes document the architecture, protocols, state machines, pipeline tradeoffs, latency measurement methodology, and testing strategies for the Ultra-Low-Latency FPGA Trading Interface project.

⸻

1. Protocol Overviews

1.1 Ethernet Frame Format
	•	Preamble & SFD: 7 bytes of 0x55 followed by 1 byte Start Frame Delimiter (0xD5). Used for receiver clock alignment and frame start detection.
	•	Destination MAC (6 bytes): Hardware address to filter frames.
	•	Source MAC (6 bytes)
	•	EtherType (2 bytes): Indicates payload type (e.g., 0x0800 for IPv4).
	•	Payload (46–1500 bytes): Encapsulated data (our ITCH/FIX messages).
	•	Frame Check Sequence (4 bytes): CRC32 for error detection.

1.2 ITCH / FIX Message Formats
	•	ITCH (e.g., Nasdaq TotalView-ITCH): Binary messages with fixed headers.
	•	Message Header: 2-byte length, 1-byte type.
	•	Fields: Order ID (64-bit), Price (32-bit integer), Volume (32-bit integer), etc.
	•	FIX: ASCII key-value pairs, delimited by SOH (0x01). More verbose, higher overhead.

We focus on ITCH for low-latency, using fixed-length binary formats.

⸻

2. Module Breakdown

2.1 eth_rx.sv
	•	Function: Ingests raw byte stream, detects preamble/SFD, filters by destination MAC, strips header and CRC, and outputs payload bytes.
	•	Interfaces:
	•	Inputs: clk, rst_n, rx_byte[7:0], rx_valid
	•	Outputs: payload_byte[7:0], payload_valid, payload_ready
	•	Key Logic:
	•	FSM to detect preamble (IDLE → PREAMBLE → SFD → LOAD_HEADER).
	•	MAC address compare, drop non-matching frames.
	•	CRC32 checking.

2.2 parser.sv
	•	Function: FSM-based decoding of ITCH messages from byte stream.
	•	Interfaces:
	•	Inputs: clk, rst_n, in_byte[7:0], in_valid, in_ready
	•	Outputs: msg_type[7:0], field_valid, parsed fields bus.
	•	FSM States:
	1.	WAIT_HEADER: Read length (2 bytes) and type (1 byte).
	2.	READ_FIELDS: Based on length, accumulate bytes into field registers.
	3.	DISPATCH: Assert field_valid, hold fields for one cycle.
	4.	IDLE: Return to WAIT_HEADER when in_valid deasserts.

2.3 trading_logic.sv
	•	Function: Implements simple decision rule.
	•	Logic: if (msg_type == TRADE && price < THRESHOLD) issue_buy <= 1;
	•	Outputs: decision_valid, decision_type, decision payload.

2.4 uart_tx.sv
	•	Function: Serialises decision payload over a UART link.
	•	Interfaces:
	•	Inputs: clk, rst_n, data_in[31:0], data_valid
	•	Outputs: tx_line, busy
	•	FSM:
	1.	IDLE: Wait for data_valid.
	2.	START_BIT: Drive 0 for 1 bit-period.
	3.	SEND_BITS: Shift out data bits LSB first.
	4.	STOP_BIT: Drive 1 for 1 bit-period.
	5.	BACK_TO_IDLE.

2.5 pipeline_regs.sv
	•	Function: Registers between pipeline stages for throughput and timing isolation.
	•	Contents: Instantiates flops for each bus: RX→Parser, Parser→Logic, Logic→TX.
	•	Timestamp Tagging: Captures cycle counter at ingress and decision output for latency calc.

⸻

3. FSM State Descriptions

Module	State	Description
eth_rx	IDLE	Wait for rx_valid and detect preamble byte 0x55
	PREAMBLE	Count consecutive 0x55 bytes
	SFD	Detect Start Frame Delimiter (0xD5)
	LOAD_HEADER	Capture MAC header and EtherType
	LOAD_PAYLD	Stream payload bytes to parser

| parser     | WAIT_HEADER | Read message length & type                         |
|            | READ_FIELDS | Accumulate message fields based on length          |
|            | DISPATCH    | Assert parsed fields valid, handshake with logic   |
|            | SKIP        | Drop invalid or unwanted message types             |

| uart_tx    | IDLE        | Wait for data_valid                                |
|            | START_BIT   | Transmit start bit                                 |
|            | SEND_BITS   | Shift out each data bit                            |
|            | STOP_BIT    | Transmit stop bit                                  |
|            | CLEANUP     | Reset internal counters, return to IDLE            |

⸻

4. Pipeline & Latency Tradeoffs
	•	Deep Pipelining reduces combinational delay per stage, allowing higher clock frequencies, but adds register-to-register latency.
	•	Shallow Pipeline (fewer stages) reduces stage-to-stage overhead but may limit max clock frequency.
	•	Technique: Insert registers after header extraction, after parsing, and after decision logic. Comparing designs with and without intermediate registers reveals cycle vs frequency tradeoffs.
	•	Backpressure: Use ready/valid handshake to stall upstream when downstream is busy, preventing data loss at the expense of throughput.

⸻

5. Latency Measurement Methodology
	1.	Cycle Counter: Global 32-bit counter incremented each clock.
	2.	Ingress Timestamp: On first payload byte valid, latch t_ingress = cycle_counter.
	3.	Decision Timestamp: On assertion of decision_valid, latch t_decision = cycle_counter.
	4.	Latency (cycles) = t_decision - t_ingress.
	5.	Convert to time: latency_ns = cycles * (1e9 / f_clk_MHz).
	6.	Per-Stage Latency: Latch timestamps at pipeline boundaries (e.g. end of parser stage) to break down into RX, parse, logic, TX delays.

Record latency distributions by logging multiple events and computing min/median/max.

⸻

6. Testing & Verification
	•	Functional Simulation: Verilator + GTKWave.
	•	Drive standard test vectors from sample.mem.
	•	Assert expected parsed fields and decisions.
	•	Reference Model: reference_parser.py outputs expected events for comparison.
	•	Automated Diff: compare_outputs.py flags mismatches.
	•	Waveform Debugging: dump signals:
	•	rx_byte, payload_valid, parsed fields, decision_valid, tx_line, cycle counter.
	•	Use GTKWave to inspect timing and handshake correctness.
	•	Assertions: Add assert in SystemVerilog for critical invariants (e.g., assert(payload_valid |-> in_parser_state)).

⸻

7. Extensions
	•	Limit Order Book: Expand trading logic to maintain book levels.
	•	Multi-Channel Support: Scale to 10G/40G serial inputs, wider data buses.

⸻

These design notes will evolve as the project progresses.
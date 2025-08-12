# README.md

Ultra-Low-Latency FPGA Trading Interface
=========================================

This project implements an FPGA-based low-latency trading interface using ITCH protocol.

## Directory Structure

LOW_LATENCY_FPGA/
├── bench/
│   ├── reference_parser.py    # Golden ITCH parser
│   └── compare_outputs.py     # Diff tool
├── docs/
│   ├── architecture.draw.io
│   ├── design_notes.md
│   ├── timing_diagram.svg 
├── hdl/
│   ├── eth_rx.sv              # Ethernet RX
│   ├── parser.sv              # ITCH parser
│   ├── trading_logic.sv       # Simple decision logic
│   ├── uart_tx.sv             # UART transmitter
│   └── pipeline_regs.sv       # Pipeline registers & timestamps
├── messages/
│   ├── generate_packets.py    # Script to build test frames
│   └── sample.mem             # Sample frame memory
├── sim/
│   ├── tb_top.sv              # SystemVerilog testbench
│   ├── file_reader.cpp        # MEM loader helper
│   ├── main.cpp               # Verilator C++ harness
│   ├── output_capture.txt     # Captured UART bits
│   └── vlt_dump.vcd           # Waveform dump (generated)
├── tools/
│   ├── run_sim.sh             # Build & run simulation
│   └── synth_estimate.sh      # Yosys synthesis estimate
└── README.md

## Prerequisites

- **Verilator** for simulation
- **Yosys** for synthesis estimates
- Python 3 for bench tools

## Simulation

```bash
cd sim
../tools/run_sim.sh


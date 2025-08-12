#!/usr/bin/env bash
set -e

# Locate project dirs
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$SCRIPT_DIR/.."
SIM_DIR="$REPO_ROOT/sim"
HDL_DIR="$REPO_ROOT/hdl"

cd "$SIM_DIR"
rm -rf obj_dir

echo "About to run Verilator in $(pwd):"
set -x

# Build with auto-main (no main.cpp)
verilator --cc --exe --build \
    --trace \
    --timing \
    --error-limit 0 \
    --Wno-TIMESCALEMOD \
    --Wno-WIDTHEXPAND \
    --Wno-WIDTHTRUNC \
    --Wno-CASEINCOMPLETE \
    --top-module tb_top \
    -CFLAGS "-std=c++17" \
    "$HDL_DIR"/eth_rx.sv \
    "$HDL_DIR"/parser.sv \
    "$HDL_DIR"/pipeline_regs.sv \
    "$HDL_DIR"/trading_logic.sv \
    "$HDL_DIR"/uart_tx.sv \
    tb_top.sv \
    main.cpp \
    -o sim_vlt

obj_dir/sim_vlt

echo
echo "✅ Simulation complete."
echo "   • UART bits → output_capture.txt"
echo "   • Waveforms → vlt_dump.vcd"
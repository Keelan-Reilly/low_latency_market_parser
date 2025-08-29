# Makefile — Verilator simulation runner
# --------------------------------------
# Builds and runs the Verilator testbench for the FPGA market data pipeline

# Project directories
SCRIPT_DIR := $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))
REPO_ROOT  := $(SCRIPT_DIR)
TB_DIR     := $(REPO_ROOT)/tb
HDL_DIR    := $(REPO_ROOT)/hdl
SIM_DIR    := $(TB_DIR)

# Verilator sources
HDL_SRCS := \
	$(HDL_DIR)/eth_rx.sv \
	$(HDL_DIR)/parser.sv \
	$(HDL_DIR)/pipeline_regs.sv \
	$(HDL_DIR)/trading_logic.sv \
	$(HDL_DIR)/uart_tx.sv \
	$(HDL_DIR)/tb_top.sv \
	$(TB_DIR)/main.cpp

# Output binary
VLT_EXE := $(SIM_DIR)/obj_dir/sim_vlt

# Default target: build and run
.PHONY: run
run: $(VLT_EXE)
	@echo
	@echo "Running simulation..."
	@$(VLT_EXE)
	@echo
	@echo "✅ Simulation complete."
	@echo "   • UART bits → output_capture.txt"
	@echo "   • Waveforms → vlt_dump.vcd"

# Build Verilator simulation
$(VLT_EXE):
	@echo "Building Verilator testbench..."
	@cd $(SIM_DIR) && verilator --cc --exe --build \
		--trace --trace-structs --trace-max-array 1024 --trace-depth 99 \
		--timing \
		--hierarchical \
		--error-limit 0 \
		--Wno-TIMESCALEMOD \
		--Wno-WIDTHEXPAND \
		--Wno-WIDTHTRUNC \
		--Wno-CASEINCOMPLETE \
		--top-module tb_top \
		-CFLAGS "-std=c++17" \
		$(HDL_SRCS) \
		-o sim_vlt

# Clean simulation outputs
.PHONY: clean
clean:
	rm -rf $(SIM_DIR)/obj_dir
	rm -f  $(SIM_DIR)/vlt_dump.vcd
	rm -f  $(SIM_DIR)/output_capture.txt
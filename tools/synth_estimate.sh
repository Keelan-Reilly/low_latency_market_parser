# tools/synth_estimate.sh
#!/usr/bin/env bash
set -e

# Synthesis with Yosys (ICE40 example)
yosys -p "
    read_verilog ../hdl/*.sv
    proc; opt; fsm; opt
    synth_ice40 -top eth_rx -json synth_eth_rx.json
    stat
"

echo "Synthesis estimates written to synth_eth_rx.json"
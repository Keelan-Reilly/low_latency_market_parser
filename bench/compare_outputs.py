#!/usr/bin/env python3
import csv
import re
import sys


def load_ref(path):
    """
    Load parsed reference data (from reference_parser.py CSV).
    Returns list of (price, volume) tuples for 'P' messages only.
    """
    out = []
    with open(path) as f:
        r = csv.DictReader(f)
        for row in r:
            if row["msg_type"] == "P" and row.get("price") and row.get("volume"):
                out.append((int(row["price"]), int(row["volume"])))
    return out


def load_fpga(path):
    """
    Load FPGA parser output log.
    Matches lines like: PARSED @1234 type=P price=10000 volume=1000
    Returns list of (price, volume) tuples for 'P' messages only.
    """
    pat = re.compile(r"type=([A-Za-z]) price=(\d+) volume=(\d+)")
    out = []
    with open(path) as f:
        for line in f:
            m = pat.search(line)
            if m and m.group(1) == "P":
                out.append((int(m.group(2)), int(m.group(3))))
    return out


def main():
    # Load reference and FPGA parsed outputs
    ref = load_ref("sim/reference_parsed.csv")
    fpga = load_fpga("sim/parser_log.txt")

    # Compare only up to the shorter list length
    n = min(len(ref), len(fpga))

    # Collect mismatches as (index, ref_tuple, fpga_tuple)
    mism = [(i, ref[i], fpga[i]) for i in range(n) if ref[i] != fpga[i]]

    print(f"REF P-messages: {len(ref)}   FPGA P-messages: {len(fpga)}   Compared: {n}")

    if mism:
        # Show first mismatch and exit with error
        print(
            f"First mismatch at index {mism[0][0]}  REF={mism[0][1]}  FPGA={mism[0][2]}"
        )
        sys.exit(1)
    else:
        # All compared tuples match
        print("OK: All compared messages match.")
        sys.exit(0)


if __name__ == "__main__":
    main()

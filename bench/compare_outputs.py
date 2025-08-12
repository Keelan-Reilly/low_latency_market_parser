#!/usr/bin/env python3
import csv, re, sys

def load_ref(path):
    out = []
    with open(path) as f:
        r = csv.DictReader(f)
        for row in r:
            if row["msg_type"] == "P" and row.get("price") and row.get("volume"):
                out.append((int(row["price"]), int(row["volume"])))
    return out

def load_fpga(path):
    # lines like: PARSED @1234 type=P price=10000 volume=1000
    pat = re.compile(r"type=([A-Za-z]) price=(\d+) volume=(\d+)")
    out = []
    with open(path) as f:
        for line in f:
            m = pat.search(line)
            if m and m.group(1) == "P":
                out.append((int(m.group(2)), int(m.group(3))))
    return out

def main():
    ref = load_ref("reference_parsed.csv")
    fpga = load_fpga("sim/parser_log.txt")
    n = min(len(ref), len(fpga))
    mism = [(i, ref[i], fpga[i]) for i in range(n) if ref[i] != fpga[i]]
    print(f"REF P-messages: {len(ref)}   FPGA P-messages: {len(fpga)}   Compared: {n}")
    if mism:
        print(f"First mismatch at index {mism[0][0]}  REF={mism[0][1]}  FPGA={mism[0][2]}")
        sys.exit(1)
    else:
        print("OK: All compared messages match.")
        sys.exit(0)

if __name__ == "__main__":
    main()
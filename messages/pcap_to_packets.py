#!/usr/bin/env python3
"""
pcap_to_packets.py
Convert a PCAP of Ethernet frames (with ITCH inside) to:
  - packets.bin : raw concatenated frames (preamble+SFD+header+payload+FCS)
  - sample.mem  : one hex byte per line (for easy viewing)

All paths default to this script's directory.
"""

import os, argparse
from scapy.all import rdpcap, Ether
from scapy.layers.inet import UDP
from zlib import crc32

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PREAMBLE = bytes([0x55]*7 + [0xD5])

def crc32_ieee8023(data: bytes) -> int:
    # Ethernet FCS = CRC-32/IEEE (ref-in/out, init=0xFFFFFFFF, xorout=0xFFFFFFFF)
    # zlib.crc32 implements this variant already; no manual seeding or extra xor needed.
    return crc32(data) & 0xFFFFFFFF

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("pcap", help="Input PCAP")
    ap.add_argument("-o", "--out", default=os.path.join(SCRIPT_DIR, "packets.bin"),
                    help="Output concatenated frames (default: messages/packets.bin)")
    ap.add_argument("--mem", default=os.path.join(SCRIPT_DIR, "sample.mem"),
                    help="Output .mem with one hex byte per line (default: messages/sample.mem)")
    ap.add_argument("--ethertype", default="0800",
                    help="Hex EtherType to keep (default 0800). Use 'any' to keep all.")
    args = ap.parse_args()

    # Resolve PCAP path
    pcap_path = args.pcap if os.path.isabs(args.pcap) else os.path.abspath(args.pcap)
    pkts = rdpcap(pcap_path)

    out_bytes = bytearray()
    kept = 0

    for pkt in pkts:
        if not pkt.haslayer(Ether):
            continue
        eth = pkt[Ether]
        dest_mac = bytes.fromhex(eth.dst.replace(":", ""))
        src_mac  = bytes.fromhex(eth.src.replace(":", ""))
        etype    = int(eth.type) if isinstance(eth.type, int) else int(str(eth.type), 0)

        # Filter
        if args.ethertype.lower() != "any":
            if etype != int(args.ethertype, 16):
                continue

        if pkt.haslayer(UDP):
            payload = bytes(pkt[UDP].payload)  # <-- just ITCH bytes
        else:
            continue  # skip non-UDP frames for this pipeline

        header = dest_mac + src_mac + etype.to_bytes(2, "big")
        frame_wo_fcs = header + payload

        fcs_val = crc32_ieee8023(frame_wo_fcs)
        fcs     = fcs_val.to_bytes(4, "little")  # Ethernet FCS is LSB-first on the wire

        # sanity check (prevents regressions)
        _check = crc32(frame_wo_fcs) & 0xFFFFFFFF
        assert _check == int.from_bytes(fcs, "little"), "FCS self-check failed"

        frame = PREAMBLE + frame_wo_fcs + fcs
        out_bytes += frame
        kept += 1

    os.makedirs(os.path.dirname(args.out), exist_ok=True)
    with open(args.out, "wb") as f:
        f.write(out_bytes)

    # Also write .mem for VSCode viewing
    if args.mem:
        os.makedirs(os.path.dirname(args.mem), exist_ok=True)
        with open(args.mem, "w") as f:
            for b in out_bytes:
                f.write(f"{b:02X}\n")

    print(f"Kept {kept} frames.")
    print(f"Wrote {len(out_bytes)} bytes to {args.out}")
    if args.mem:
        print(f"Wrote {args.mem}")

if __name__ == "__main__":
    main()
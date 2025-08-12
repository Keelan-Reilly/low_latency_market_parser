#!/usr/bin/env python3
"""
make_itch_pcap.py
Downloads Nasdaq ITCH 5.0 sample, wraps each message in Ethernet/IP/UDP,
writes a PCAP file next to this script, then calls pcap_to_packets.py
to produce packets.bin and sample.mem in the same folder.

Requirements:
    pip install scapy requests
"""

import os, sys, struct, subprocess, requests
from scapy.all import Ether, IP, UDP, wrpcap

ITCH_URL = "https://www.nasdaqtrader.com/content/technicalsupport/specifications/dataproducts/NasdaqTotalView-ITCH5.0sample.dat"

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))   # <-- everything relative to here
OUT_PCAP   = os.path.join(SCRIPT_DIR, "itch_wrapped.pcap")
OUT_BIN    = os.path.join(SCRIPT_DIR, "packets.bin")
OUT_MEM    = os.path.join(SCRIPT_DIR, "sample.mem")
ITCH_BIN   = os.path.join(SCRIPT_DIR, "nasdaq_itch_sample.bin")
PCAP_TO_PACKETS = os.path.join(SCRIPT_DIR, "pcap_to_packets.py")

def download_itch_sample(path=ITCH_BIN):
    if not os.path.exists(path):
        print(f"Downloading ITCH sample from {ITCH_URL}...")
        r = requests.get(ITCH_URL, timeout=30)
        r.raise_for_status()

        # Guard: make sure we didn't get an HTML error/redirect page
        ct = r.headers.get("Content-Type", "").lower()
        if "text/html" in ct or b"<html" in r.content[:1024].lower() or b"<!doctype" in r.content[:64].lower():
            raise RuntimeError("Download returned HTML (error/redirect) – not an ITCH binary.")

        with open(path, "wb") as f:
            f.write(r.content)
        print(f"Saved to {path}")
    else:
        print(f"Found existing {path}")
    return path

def split_itch_messages(raw: bytes):
    """Yield [len(2, BE) | type(1) | body] messages."""
    i = 0
    n = len(raw)
    while i + 2 <= n:
        length = struct.unpack(">H", raw[i:i+2])[0]
        end = i + 2 + length
        if length < 1 or end > n:
            break
        yield raw[i:end]
        i = end

def make_pcap(itch_msgs, pcap_path=OUT_PCAP):
    frames = []
    for msg in itch_msgs:
        eth = Ether(dst="ff:ff:ff:ff:ff:ff", src="00:11:22:33:44:55")
        ip  = IP(src="192.168.0.1", dst="239.0.0.1")
        udp = UDP(sport=12345, dport=12345)
        frames.append(eth / ip / udp / msg)
    wrpcap(pcap_path, frames)
    print(f"Wrote {len(frames)} frames to {pcap_path}")
    return pcap_path

def run_pcap_to_packets(pcap_path, out_bin=OUT_BIN, out_mem=OUT_MEM):
    # Use the same interpreter; call the helper by absolute path; set cwd to SCRIPT_DIR
    print(f"Converting {pcap_path} to {out_bin} and {out_mem} ...")
    subprocess.run(
        [sys.executable, PCAP_TO_PACKETS, pcap_path, "-o", out_bin, "--mem", out_mem],
        check=True,
        cwd=SCRIPT_DIR
    )
    print(f"Created {out_bin} and {out_mem}")

def main():
    os.makedirs(SCRIPT_DIR, exist_ok=True)

    itch_file = download_itch_sample()
    with open(itch_file, "rb") as f:
        raw = f.read()

    msgs = list(split_itch_messages(raw))
    print(f"Split into {len(msgs)} ITCH messages.")

    pcap_file = make_pcap(msgs, OUT_PCAP)
    run_pcap_to_packets(pcap_file, OUT_BIN, OUT_MEM)

if __name__ == "__main__":
    main()
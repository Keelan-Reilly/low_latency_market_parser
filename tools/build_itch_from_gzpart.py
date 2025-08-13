#!/usr/bin/env python3
"""
build_itch_from_gzpart.py

Read a (possibly truncated) gzip file of Nasdaq ITCH 5.0 messages (e.g. *.gz.part),
decompress as far as possible, extract complete ITCH messages, wrap each as an
Ethernet frame with preamble/SFD and CRC-32 FCS, and write:

  - messages/packets.bin  (concatenated frames)
  - messages/sample.mem   (one hex byte per line)

Usage examples:
  python tools/build_itch_from_gzpart.py --source ~/Downloads/ITCH.gz.part
  python tools/build_itch_from_gzpart.py --source itch.dat --limit 5000
"""

import os, sys, argparse, gzip, io
from zlib import crc32

PREAMBLE = bytes([0x55]*7 + [0xD5])

def mac_to_bytes(s: str) -> bytes:
    s = s.replace(":", "").replace("-", "")
    if len(s) != 12: raise ValueError(f"Bad MAC '{s}'")
    return bytes.fromhex(s)

def iter_raw_bytes_lenient(path: str, chunk=1<<20):
    """
    Yield raw ITCH bytes from `path`.
    - If file looks gzip (magic 1f 8b), stream-decompress; on truncation, stop without error.
    - Otherwise, stream raw bytes.
    """
    with open(path, "rb") as f:
        head = f.read(2)
        rest = f.read()  # read the rest; we'll wrap into a BytesIO either way
        buf = head + rest

    if len(head) >= 2 and head[:2] == b"\x1f\x8b":
        # Lenient gzip read: read() in chunks and stop on EOF/OSError
        bio = io.BytesIO(buf)
        gz = gzip.GzipFile(fileobj=bio, mode="rb")
        while True:
            try:
                data = gz.read(chunk)
            except (OSError, EOFError):
                # Truncated or CRC mismatch at end — keep what we have and stop.
                break
            if not data:
                break
            yield data
    else:
        # Raw bytes
        off = 0
        n = len(buf)
        while off < n:
            take = min(chunk, n - off)
            yield buf[off:off+take]
            off += take

def iter_itch_messages(byte_iter):
    """
    Assemble bytes from `byte_iter` and yield complete ITCH messages:
      [len(2 BE) | type(1) | body (len-1 bytes)]
    Discards trailing partial message (from truncation).
    """
    buf = bytearray()
    for chunk in byte_iter:
        buf += chunk
        # peel complete messages
        while True:
            if len(buf) < 3:
                break
            ln = int.from_bytes(buf[0:2], "big")
            end = 2 + ln
            if ln < 1 or end > len(buf):
                break
            yield bytes(buf[:end])
            del buf[:end]
    # any leftover in buf is partial → ignored

def wrap_frame(itch_msg: bytes, dst_mac: bytes, src_mac: bytes, ethertype: int) -> bytes:
    header = dst_mac + src_mac + ethertype.to_bytes(2, "big")
    frame_wo_fcs = header + itch_msg
    fcs = crc32(frame_wo_fcs) & 0xFFFFFFFF
    return PREAMBLE + frame_wo_fcs + fcs.to_bytes(4, "little")  # FCS is LSB-first on wire

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--source", required=True,
                    help="Path to ITCH .dat or .gz/.gz.part (partial gzip OK)")
    ap.add_argument("--out-dir", default="messages", help="Output directory")
    ap.add_argument("--limit", type=int, default=0, help="Limit messages (0=all available)")
    ap.add_argument("--dst-mac", default="FF:FF:FF:FF:FF:FF", help="Destination MAC")
    ap.add_argument("--src-mac", default="00:11:22:33:44:55", help="Source MAC")
    ap.add_argument("--ethertype", default="0800", help="EtherType hex (default 0800)")
    ap.add_argument("--skip", type=int, default=0, help="Number of ITCH messages to skip before writing")
    args = ap.parse_args()

    os.makedirs(args.out_dir, exist_ok=True)
    packets_bin = os.path.join(args.out_dir, "packets.bin")
    sample_mem  = os.path.join(args.out_dir, "sample.mem")

    dst = mac_to_bytes(args.dst_mac)
    src = mac_to_bytes(args.src_mac)
    et  = int(args.ethertype, 16)

    total_msgs = 0
    total_bytes = 0
    trades_P = 0
    first_P = None
    skipped = 0

    with open(packets_bin, "wb") as fbin, open(sample_mem, "w") as fmem:
        for msg in iter_itch_messages(iter_raw_bytes_lenient(args.source)):
            if skipped < args.skip:
                skipped += 1
                continue  # don't write until we've skipped enough

            total_msgs += 1
            if msg[2:3] == b'P':
                trades_P += 1
                if first_P is None:
                    first_P = total_msgs - 1  # zero-based index

            frame = wrap_frame(msg, dst, src, et)
            fbin.write(frame)
            for b in frame:
                fmem.write(f"{b:02X}\n")
            total_bytes += len(frame)

            if args.limit and total_msgs >= args.limit:
                break


    print(f"[gzpart] source: {args.source}")
    print(f"[gzpart] wrote {total_msgs} messages, {total_bytes:,} bytes")
    print(f"[gzpart] P_count={trades_P}, first_P_index={first_P}")
    print(f"[gzpart] -> {packets_bin}")
    print(f"[gzpart] -> {sample_mem}")

if __name__ == "__main__":
    main()

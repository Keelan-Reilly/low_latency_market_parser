#!/usr/bin/env python3
"""
Build Ethernet frames from a (possibly truncated) Nasdaq ITCH gzip part.

Usage example:
itch_sample.gz.part  →  writes:
  - messages/packets.bin  (concatenated Ethernet frames incl. preamble+FCS)
  - messages/sample.mem   (same bytes, 1 hex byte per line)

"""

import os
import argparse
import gzip
import io
from zlib import crc32

# Ethernet preamble (7×0x55) + SFD (0xD5)
PREAMBLE = bytes([0x55] * 7 + [0xD5])


def mac_to_bytes(s: str) -> bytes:
    """'AA:BB:CC:DD:EE:FF' → 6-byte value."""
    s = s.replace(":", "").replace("-", "")
    if len(s) != 12:
        raise ValueError(f"Bad MAC '{s}'")
    return bytes.fromhex(s)


def iter_raw_bytes_lenient(path: str, chunk=1 << 20):
    """
    Stream bytes from `path`.
    - If gzip (1F 8B), decompress until data ends (tolerates truncation).
    - Otherwise, stream as-is.
    """
    with open(path, "rb") as f:
        head = f.read(2)
        rest = f.read()
        buf = head + rest

    if head == b"\x1f\x8b":
        bio = io.BytesIO(buf)
        gz = gzip.GzipFile(fileobj=bio, mode="rb")
        while True:
            try:
                data = gz.read(chunk)
            except (OSError, EOFError):
                break  # truncated tail: keep whatever we decoded
            if not data:
                break
            yield data
    else:
        # raw file
        for off in range(0, len(buf), chunk):
            yield buf[off : off + chunk]


def iter_itch_messages(byte_iter):
    """
    Yield complete ITCH messages from a byte stream.
    Format: [len_hi, len_lo, type, body...]  with total length = len.
    Trailing partial message is dropped (expected with .gz.part).
    """
    buf = bytearray()
    for chunk in byte_iter:
        buf += chunk
        while True:
            if len(buf) < 3:
                break
            ln = int.from_bytes(buf[0:2], "big")
            end = 2 + ln
            if ln < 1 or end > len(buf):
                break
            yield bytes(buf[:end])
            del buf[:end]


def wrap_frame(
    itch_msg: bytes, dst_mac: bytes, src_mac: bytes, ethertype: int
) -> bytes:
    """
    Ethernet II frame (with preamble+SFD and little-endian FCS on wire):
      DST(6) | SRC(6) | EtherType(2) | ITCH payload | FCS(4 LSB-first)
    """
    header = dst_mac + src_mac + ethertype.to_bytes(2, "big")
    frame_wo_fcs = header + itch_msg
    fcs = crc32(frame_wo_fcs) & 0xFFFFFFFF
    return PREAMBLE + frame_wo_fcs + fcs.to_bytes(4, "little")


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument(
        "--source", required=True, help="ITCH .dat or .gz/.gz.part (truncated OK)"
    )
    ap.add_argument("--out-dir", default="messages")
    ap.add_argument("--limit", type=int, default=0, help="Max messages (0=all)")
    ap.add_argument("--skip", type=int, default=0, help="Skip first N messages")
    ap.add_argument("--dst-mac", default="FF:FF:FF:FF:FF:FF")
    ap.add_argument("--src-mac", default="00:11:22:33:44:55")
    ap.add_argument(
        "--ethertype", default="0800", help="Hex EtherType (default 0x0800)"
    )
    args = ap.parse_args()

    os.makedirs(args.out_dir, exist_ok=True)
    packets_bin = os.path.join(args.out_dir, "packets.bin")
    sample_mem = os.path.join(args.out_dir, "sample.mem")

    dst = mac_to_bytes(args.dst_mac)
    src = mac_to_bytes(args.src_mac)
    et = int(args.ethertype, 16)

    total_msgs = 0
    total_bytes = 0
    trades_P = 0
    first_P = None
    skipped = 0

    with open(packets_bin, "wb") as fbin, open(sample_mem, "w") as fmem:
        for msg in iter_itch_messages(iter_raw_bytes_lenient(args.source)):
            if skipped < args.skip:
                skipped += 1
                continue

            total_msgs += 1

            # Count 'P' (Trade, non-cross) messages for convenience
            if msg[2:3] == b"P":
                trades_P += 1
                if first_P is None:
                    first_P = total_msgs - 1

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

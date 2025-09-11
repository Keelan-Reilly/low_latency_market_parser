#!/usr/bin/env python3
"""
reference_parser.py
Parse messages/packets.bin (from build_itch_from_gzpart.py), verify IEEE 802.3 CRC,
and decode a subset of ITCH messages for comparison with FPGA logs.

Outputs:
  --out-parsed     CSV of all decoded frames (with CRC check + ITCH fields)
  --out-decisions  CSV of 'BUY' decisions for trades under --threshold price
"""

import struct
import csv
import argparse
import sys

PREAMBLE = bytes([0x55] * 7 + [0xD5])


def crc32_ieee8023(data: bytes) -> int:
    """Software IEEE 802.3 CRC-32 (little-endian on wire)."""
    crc = 0xFFFFFFFF
    for b in data:
        crc ^= b
        for _ in range(8):
            crc = (crc >> 1) ^ 0xEDB88320 if (crc & 1) else crc >> 1
    return crc ^ 0xFFFFFFFF


def iter_frames(blob: bytes):
    """
    Scan binary blob for preamble/SFD → parse Ethernet frame:
      DST(6) | SRC(6) | EtherType(2) | ITCH payload | FCS(4, little-endian)
    Yields: (offset, header, payload, fcs_bytes, crc_ok)
    """
    i, n = 0, len(blob)
    while i + 8 <= n:
        if blob[i : i + 8] != PREAMBLE:
            i += 1
            continue
        start = i
        i += 8

        if i + 14 > n:
            break
        header = blob[i : i + 14]
        i += 14

        if i + 3 > n:
            break
        length = struct.unpack(">H", blob[i : i + 2])[0]
        if length < 1:
            i += 1
            continue

        msg_total = 2 + length
        payload_end = i + msg_total
        if payload_end + 4 > n:
            break

        payload = blob[i:payload_end]
        i = payload_end

        fcs_bytes = blob[i : i + 4]
        i += 4

        calc = crc32_ieee8023(header + payload)
        recv = int.from_bytes(fcs_bytes, "little")
        yield start, header, payload, fcs_bytes, (calc == recv)


def parse_itch_payload(payload: bytes):
    """
    Decode length + type; for 'P' Trade (non-cross) extract:
      order_id, price, volume
    """
    length = struct.unpack(">H", payload[0:2])[0]
    msg_type = payload[2]
    body = payload[3 : 2 + length]
    if msg_type == ord("P") and len(body) >= 35:
        order_id = int.from_bytes(body[10:18], "big")
        volume = int.from_bytes(body[19:23], "big")
        price = int.from_bytes(body[31:35], "big")
        return msg_type, {"order_id": order_id, "price": price, "volume": volume}
    return msg_type, None


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--in", dest="infile", default="messages/packets.bin")
    ap.add_argument("--threshold", type=int, default=2_000_000)
    ap.add_argument("--out-parsed", default="sim/reference_parsed.csv")
    ap.add_argument("--out-decisions", default="sim/reference_decisions.csv")
    args = ap.parse_args()

    try:
        blob = open(args.infile, "rb").read()
    except FileNotFoundError:
        sys.exit(f"error: {args.infile} not found")

    parsed_rows, decisions = [], []
    frames, crc_ok_cnt, p_cnt = 0, 0, 0

    for idx, (off, hdr, payload, fcs, ok) in enumerate(iter_frames(blob)):
        frames += 1
        if ok:
            crc_ok_cnt += 1

        dest = ":".join(f"{b:02x}" for b in hdr[0:6])
        src = ":".join(f"{b:02x}" for b in hdr[6:12])
        ethtype = int.from_bytes(hdr[12:14], "big")

        msg_type, fields = parse_itch_payload(payload)
        row = {
            "frame_index": idx,
            "offset": off,
            "dest": dest,
            "src": src,
            "ethertype": f"0x{ethtype:04X}",
            "crc_ok": int(ok),
            "msg_type": chr(msg_type) if 32 <= msg_type < 127 else f"{msg_type}",
            "order_id": "",
            "price": "",
            "volume": "",
        }
        if fields:
            row.update(fields)
            if msg_type == ord("P"):
                p_cnt += 1
                if fields["price"] < args.threshold:
                    decisions.append({"frame_index": idx, **fields, "decision": "BUY"})
        parsed_rows.append(row)

    # Write outputs
    fieldnames = [
        "frame_index",
        "offset",
        "dest",
        "src",
        "ethertype",
        "crc_ok",
        "msg_type",
        "order_id",
        "price",
        "volume",
    ]

    with open(args.out_parsed, "w", newline="") as f:
        w = csv.DictWriter(f, fieldnames=fieldnames)
        w.writeheader()
        w.writerows(parsed_rows)

    if decisions:
        with open(args.out_decisions, "w", newline="") as f:
            w = csv.DictWriter(f, fieldnames=list(decisions[0].keys()))
            w.writeheader()
            w.writerows(decisions)

    print(f"Wrote {args.out_parsed} with {len(parsed_rows)} frames.")
    print(f"Wrote {args.out_decisions} with {len(decisions)} decisions.")
    print(
        f"CRC ok {crc_ok_cnt}/{frames} | P messages {p_cnt} | threshold {args.threshold}"
    )


if __name__ == "__main__":
    main()

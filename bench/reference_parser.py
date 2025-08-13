#!/usr/bin/env python3
"""
reference_parser.py
Parse messages/packets.bin (as produced by build_itch_from_gzpart.py / pcap_to_packets.py),
verify CRC, and decode a subset of ITCH messages for cross-checking against FPGA logs.
"""

import struct, csv, argparse, sys

PREAMBLE = bytes([0x55] * 7 + [0xD5])

def crc32_ieee8023(data: bytes) -> int:
    crc = 0xFFFFFFFF
    for b in data:
        crc ^= b
        for _ in range(8):
            if (crc & 1):
                crc = (crc >> 1) ^ 0xEDB88320
            else:
                crc >>= 1
    return crc ^ 0xFFFFFFFF

def iter_frames(blob: bytes):
    """Yield (offset, header(14B), payload(ITCH msg), fcs(4B), crc_ok)."""
    i, n = 0, len(blob)
    while i + 8 <= n:
        if blob[i:i+8] != PREAMBLE:
            i += 1
            continue
        start = i
        i += 8  # skip preamble/SFD

        if i + 14 > n: break
        header = blob[i:i+14]  # dest(6), src(6), ethertype(2)
        i += 14

        if i + 3 > n: break
        length = struct.unpack(">H", blob[i:i+2])[0]
        if length < 1:
            i += 1
            continue
        msg_total = 2 + length  # len(2) + length bytes (TYPE+BODY)
        payload_end = i + msg_total
        if payload_end + 4 > n: break

        payload = blob[i:payload_end]
        i = payload_end

        fcs_bytes = blob[i:i+4]
        i += 4

        calc = crc32_ieee8023(header + payload)
        recv = int.from_bytes(fcs_bytes, "little")  # little-endian on wire/file
        yield start, header, payload, fcs_bytes, (calc == recv)

def parse_itch_payload(payload: bytes):
    length = struct.unpack(">H", payload[0:2])[0]
    msg_type = payload[2]
    body = payload[3:2+length]  # bytes after TYPE
    if msg_type == ord('P'):
        # Need at least offsets up to 34 after TYPE.
        if len(body) < 35:
            return msg_type, None
        order_id = int.from_bytes(body[10:18], "big")
        volume   = int.from_bytes(body[19:23], "big")
        price    = int.from_bytes(body[31:35], "big")
        return msg_type, {"order_id": order_id, "price": price, "volume": volume}
    return msg_type, None

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--in", dest="infile", default="messages/packets.bin")
    ap.add_argument("--threshold", type=int, default=2_000_000)  # match RTL default
    ap.add_argument("--out-parsed", default="reference_parsed.csv")
    ap.add_argument("--out-decisions", default="reference_decisions.csv")
    args = ap.parse_args()

    try:
        blob = open(args.infile, "rb").read()
    except FileNotFoundError:
        print(f"error: {args.infile} not found", file=sys.stderr)
        sys.exit(2)

    parsed_rows, decisions = [], []
    frames, crc_ok_cnt, p_cnt = 0, 0, 0

    for idx, (off, hdr, payload, fcs, ok) in enumerate(iter_frames(blob)):
        frames += 1
        if ok: crc_ok_cnt += 1

        dest = ":".join(f"{b:02x}" for b in hdr[0:6])
        src  = ":".join(f"{b:02x}" for b in hdr[6:12])
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
            # Pre-seed optional columns so DictWriter always has them
            "order_id": "",
            "price": "",
            "volume": "",
        }
        if fields:
            row["order_id"] = fields["order_id"]
            row["price"]    = fields["price"]
            row["volume"]   = fields["volume"]
            if msg_type == ord('P'):
                p_cnt += 1
                if fields["price"] < args.threshold:
                    decisions.append({
                        "frame_index": idx,
                        "order_id": fields["order_id"],
                        "price": fields["price"],
                        "volume": fields["volume"],
                        "decision": "BUY"
                    })
        parsed_rows.append(row)

    # Fieldnames: stable superset
    fieldnames = ["frame_index","offset","dest","src","ethertype","crc_ok","msg_type",
                  "order_id","price","volume"]

    # Write CSVs
    with open(args.out_parsed, "w", newline="") as f:
        w = csv.DictWriter(f, fieldnames=fieldnames, extrasaction="ignore")
        w.writeheader()
        w.writerows(parsed_rows)

    if decisions:
        with open(args.out_decisions, "w", newline="") as f:
            w = csv.DictWriter(f, fieldnames=list(decisions[0].keys()))
            w.writeheader()
            w.writerows(decisions)

    print(f"Wrote {args.out_parsed} with {len(parsed_rows)} frames.")
    print(f"Wrote {args.out_decisions} with {len(decisions)} decisions.")
    print(f"CRC ok {crc_ok_cnt}/{frames}  |  P messages {p_cnt}  |  threshold {args.threshold}")

if __name__ == "__main__":
    main()

#!/usr/bin/env python3
"""
reference_parser.py
Parse messages/packets.bin (as produced by pcap_to_packets.py or generate_packets.py),
verify CRC, and decode a subset of ITCH messages for cross-checking against FPGA logs.
"""

import struct
import csv

PREAMBLE = bytes([0x55] * 7 + [0xD5])

def crc32_ieee8023(data: bytes) -> int:
    crc = 0xFFFFFFFF
    for b in data:
        crc ^= b
        for _ in range(8):
            if (crc & 1) != 0:
                crc = (crc >> 1) ^ 0xEDB88320
            else:
                crc >>= 1
    return crc ^ 0xFFFFFFFF

def iter_frames(blob: bytes):
    """Yield (offset, header, payload, fcs_bytes, crc_ok)."""
    i = 0
    n = len(blob)
    while i < n:
        # find preamble
        if i + 8 > n:
            break
        if blob[i:i+8] != PREAMBLE:
            # try to resync: move ahead one byte
            i += 1
            continue
        start = i
        i += 8  # skip preamble/SFD

        if i + 14 > n:
            break
        header = blob[i:i+14]  # dest(6), src(6), ethertype(2)
        i += 14

        # We don't know payload length from Ethernet header.
        # We must scan until a valid FCS that matches CRC(header+payload).
        # But that's ambiguous in a concatenated stream. So we rely on the ITCH length inside payload:
        # payload starts with length(2), type(1), ... body_len = length-3.
        if i + 3 > n:
            break
        length = struct.unpack(">H", blob[i:i+2])[0]
        body_len = length - 1  # includes type → body = length-1
        msg_total = 2 + 1 + body_len  # len(2)+type(1)+body
        payload_end = i + msg_total
        if payload_end + 4 > n:
            break
        payload = blob[i:payload_end]
        i = payload_end

        fcs_bytes = blob[i:i+4]
        i += 4

        # Verify CRC over header+payload
        calc = crc32_ieee8023(header + payload)
        recv = int.from_bytes(fcs_bytes, "little")  # big-endian, to match writer
        yield start, header, payload, fcs_bytes, (calc == recv)

def parse_itch_payload(payload: bytes):
    length = struct.unpack(">H", payload[0:2])[0]
    msg_type = payload[2]
    body = payload[3: 2 + 1 + (length - 1)]  # everything after type
    if msg_type == ord('P'):  # ITCH 5.0 'P' Trade (non-cross)
        # Offsets after TYPE (cnt==0 is first byte after TYPE):
        # 10..17: Order Ref (8) -> order_id
        # 19..22: Shares     (4) -> volume
        # 31..34: Price      (4) -> price
        if len(body) < 35:  # need at least 35 bytes after TYPE
            return msg_type, None
        order_id = int.from_bytes(body[10:18], "big")
        volume   = int.from_bytes(body[19:23], "big")
        price    = int.from_bytes(body[31:35], "big")
        return msg_type, {"order_id": order_id, "price": price, "volume": volume}
    else:
        return msg_type, None

def main():
    with open("messages/packets.bin", "rb") as f:
        blob = f.read()

    parsed_rows = []
    decisions = []
    THRESHOLD = 20_000

    for idx, (off, hdr, payload, fcs, ok) in enumerate(iter_frames(blob)):
        dest = hdr[0:6].hex(":")
        src  = hdr[6:12].hex(":")
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
        }
        if fields:
            row.update(fields)
            # Optional decision rule (match your RTL)
            if msg_type == ord('P') and fields["price"] < THRESHOLD:
                decisions.append({
                    "frame_index": idx,
                    "order_id": fields["order_id"],
                    "price": fields["price"],
                    "volume": fields["volume"],
                    "decision": "BUY"
                })
        parsed_rows.append(row)

    with open("reference_parsed.csv", "w", newline="") as f:
        w = csv.DictWriter(f, fieldnames=list(parsed_rows[0].keys()))
        w.writeheader()
        w.writerows(parsed_rows)

    if decisions:
        with open("reference_decisions.csv", "w", newline="") as f:
            w = csv.DictWriter(f, fieldnames=list(decisions[0].keys()))
            w.writeheader()
            w.writerows(decisions)

    print(f"Wrote reference_parsed.csv with {len(parsed_rows)} frames.")
    print(f"Wrote reference_decisions.csv with {len(decisions)} decisions.")

if __name__ == "__main__":
    main()
#!/usr/bin/env python3
import struct, os

ETH_PREAMBLE = b'\x55' * 7 + b'\xD5'
DEST_MAC     = b'\xFF\xFF\xFF\xFF\xFF\xFF'
SRC_MAC      = b'\x00\x11\x22\x33\x44\x55'
ETH_TYPE     = b'\x08\x00'  # IPv4

def crc32_lsbf(crc, data_byte):
    c = crc ^ data_byte
    for _ in range(8):
        if c & 1:
            c = (c >> 1) ^ 0xEDB88320
        else:
            c >>= 1
    return c & 0xFFFFFFFF

def compute_fcs(data: bytes) -> int:
    c = 0xFFFFFFFF
    for b in data:
        c = crc32_lsbf(c, b)
    return c ^ 0xFFFFFFFF

def make_itch_trade(order_id, price, volume):
    length = 2 + 1 + 8 + 4 + 4
    return struct.pack('>H B Q I I',
                       length,
                       ord('T'),
                       order_id,
                       price,
                       volume)

def build_frame(order_id, price, volume):
    payload = make_itch_trade(order_id, price, volume)
    frame   = ETH_PREAMBLE + DEST_MAC + SRC_MAC + ETH_TYPE + payload

    crc_input = frame[len(ETH_PREAMBLE):]
    fcs       = compute_fcs(crc_input)
    return frame + struct.pack('>I', fcs)

if __name__ == "__main__":
    # 1 frame → 7+1 + 14 + 19 + 4 = 45 bytes
    frames = [ build_frame(order_id=1, price=10000, volume=1000) ]
    all_bytes = b''.join(frames)

    out_dir = os.path.dirname(os.path.realpath(__file__))
    with open(os.path.join(out_dir, 'packets.bin'), 'wb') as f:
        f.write(all_bytes)
    with open(os.path.join(out_dir, 'sample.mem'), 'w') as m:
        for byte in all_bytes:
            m.write(f"{byte:02X}\n")
    print("Wrote packets.bin and sample.mem")
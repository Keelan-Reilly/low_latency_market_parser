# tools/crc_debug.py
import sys
from pathlib import Path
from zlib import crc32

def crc32_eth(b):
    # Ethernet FCS via zlib
    return crc32(b) & 0xFFFFFFFF

p = Path(sys.argv[1] if len(sys.argv) > 1 else "messages/packets.bin")
data = p.read_bytes()

# naive frame splitter using preamble 7x55 + D5 (works with your generator)
PREAMBLE = bytes([0x55]*7 + [0xD5])
i = 0; ok=0; bad=0
while True:
    j = data.find(PREAMBLE, i)
    if j < 0: break
    k = data.find(PREAMBLE, j+8)
    frame = data[j+8:k] if k!=-1 else data[j+8:]
    if len(frame) < 14+4: break
    body, fcs_bytes = frame[:-4], frame[-4:]
    want = crc32_eth(body)             # numeric
    got_le = int.from_bytes(fcs_bytes, "little")
    got_be = int.from_bytes(fcs_bytes, "big")
    if want == got_le: ok+=1
    else: bad+=1
    i = j+8
print("OK", ok, "BAD", bad)
#!/usr/bin/env python3
# Robust UART decoder for 'uart_tx_bytes.sv' (4 bytes, each with start/stop)
# Decodes to bytes first, then groups 4 bytes => 32-bit little-endian words.

CLK_HZ = 100_000_000
BAUD   = 115_200
BIT    = int(round(CLK_HZ / BAUD))  # ~868 clock cycles per bit

s = [int(x.strip()) for x in open("sim/output_capture.txt")]
N = len(s)

def sample(i):
    return 1 if i < 0 or i >= N else s[i]

def find_start(i):
    # find 1->0 edge with mid-start confirmed low
    while i + BIT < N:
        if sample(i - 1) == 1 and sample(i) == 0 and sample(i + BIT//2) == 0:
            return i
        i += 1
    return None

def decode_byte(start_idx):
    # start_idx points to the falling edge of the START bit
    b = 0
    for k in range(8):
        mid = start_idx + int((1.5 + k) * BIT)  # sample mid-bit (LSB first)
        b |= (sample(mid) & 1) << k
    # check stop bit
    stop_mid = start_idx + int(9.5 * BIT)
    if sample(stop_mid) != 1:
        return None
    # return byte and index just after this frame (10 bits)
    return b, start_idx + int(10 * BIT)

# 1) Decode the entire capture into bytes
i = 0
bytes_out = []
while True:
    st = find_start(i)
    if st is None:
        break
    dec = decode_byte(st)
    if dec is None:
        # we saw a false edge; move a bit and keep searching
        i = st + BIT // 2
        continue
    b, next_i = dec
    bytes_out.append(b)
    # Try to find the next start near the expected location; if not found,
    # the general loop's find_start() will pick it up anyway.
    i = next_i - BIT  # keep a little overlap to tolerate drift

# 2) Group bytes into 32-bit little-endian words (lowest byte first)
words = []
for k in range(0, len(bytes_out) // 4 * 4, 4):
    w = (bytes_out[k]
         | (bytes_out[k+1] << 8)
         | (bytes_out[k+2] << 16)
         | (bytes_out[k+3] << 24))
    words.append(w)

for w in words:
    print(f"0x{w:08X} {w}")
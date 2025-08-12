#!/usr/bin/env python3
import sys, struct, os

# usage:  gzcat file.gz | python3 tools/itch_head.py 200
# writes messages/nasdaq_itch_sample.bin

N = int(sys.argv[1]) if len(sys.argv) > 1 else 10000
os.makedirs("messages", exist_ok=True)
out = open("messages/nasdaq_itch_sample.bin", "wb")

data = sys.stdin.buffer.read()
i = 0
pos = 0
total = len(data)

while pos + 2 <= total and i < N:
    ln = int.from_bytes(data[pos:pos+2], "big")
    end = pos + 2 + ln
    if ln < 1 or end > total:
        break
    out.write(data[pos:end])
    pos = end
    i += 1

out.close()
print(f"Wrote first {i} messages -> messages/nasdaq_itch_sample.bin")
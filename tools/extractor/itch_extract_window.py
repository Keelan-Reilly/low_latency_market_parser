#!/usr/bin/env python3
import sys, struct, os

src = sys.argv[1]
start_idx = int(sys.argv[2])     # index of first message to include
count = int(sys.argv[3])         # how many messages to copy
dst = sys.argv[4]

os.makedirs(os.path.dirname(dst) or ".", exist_ok=True)

b = open(src, "rb").read()
pos = 0; n = len(b); idx = 0

# advance to start_idx
while pos + 2 <= n and idx < start_idx:
    ln = int.from_bytes(b[pos:pos+2], "big")
    end = pos + 2 + ln
    if ln < 1 or end > n: break
    pos = end; idx += 1

# copy 'count' messages
out = open(dst, "wb")
copied = 0
while pos + 2 <= n and copied < count:
    ln = int.from_bytes(b[pos:pos+2], "big")
    end = pos + 2 + ln
    if ln < 1 or end > n: break
    out.write(b[pos:end])
    pos = end; copied += 1
out.close()

print(f"wrote {copied} msgs -> {dst}")
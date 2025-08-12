#!/usr/bin/env python3
import sys, collections

path = sys.argv[1] if len(sys.argv) > 1 else "messages/nasdaq_itch_sample.bin"

with open(path, "rb") as f:
    b = f.read()

n = len(b)
pos = 0
idx = 0
hist = collections.Counter()
first_P = None

while pos + 3 <= n:  # need at least len(2) + type(1)
    ln = int.from_bytes(b[pos:pos+2], "big")
    end = pos + 2 + ln
    if ln < 1 or end > n:
        break  # malformed or truncated

    t = b[pos + 2]
    if t == ord('P'):
        hist['P'] += 1
        if first_P is None:
            first_P = idx

    pos = end
    idx += 1

print(f"total_messages: {idx}")
print(f"P_count: {hist['P']}")
print(f"first_P_index: {first_P}")
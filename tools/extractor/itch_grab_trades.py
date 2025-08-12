#!/usr/bin/env python3
import sys, struct, argparse, os
ap = argparse.ArgumentParser()
ap.add_argument("--window", type=int, default=200)
ap.add_argument("--out", default="messages/nasdaq_itch_Tsample.bin")
args = ap.parse_args()
os.makedirs(os.path.dirname(args.out) or ".", exist_ok=True)

buf = bytearray(); have_p = False; wrote = 0
CHUNK = 1<<20
with open(args.out, "wb") as out:
    while True:
        chunk = sys.stdin.buffer.read(CHUNK)
        if not chunk and not buf: break
        buf += chunk
        while True:
            if len(buf) < 3: break
            ln = int.from_bytes(buf[0:2], "big"); end = 2 + ln
            if ln < 1 or len(buf) < end: break
            t = buf[2]
            if have_p:
                out.write(buf[:end]); wrote += 1
                if wrote >= args.window:
                    print(f"wrote {wrote} msgs -> {args.out}"); sys.exit(0)
            elif t == ord('P'):  # first trade seen
                have_p = True
                out.write(buf[:end]); wrote = 1
            del buf[:end]
        if not chunk: break
print(f"done; wrote {wrote} msgs -> {args.out}")
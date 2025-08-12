#!/usr/bin/env python3 need fix
"""
analyse_latencies.py — read latencies.csv, recompute wrap-safe stage & total latencies,
print summary stats, and plot histograms/CDF.

Expected CSV header (from your C++ logger):
    ingress,parser,logic,decision,parser_lat,logic_lat,total_lat

Only the 4 timestamp columns are required; precomputed *_lat columns are ignored.
"""

import argparse
import os
import sys
import pandas as pd
import matplotlib.pyplot as plt

DEFAULT_LAT_FILE = "sim/latencies.csv"
DEFAULT_CLK_HZ = 100_000_000  # 100 MHz

def load_latencies_csv(path: str) -> pd.DataFrame:
    if not os.path.isfile(path):
        print(f"Error: '{path}' not found.", file=sys.stderr)
        sys.exit(1)

    # Try with header row first; if that fails, fall back to no header.
    try:
        df = pd.read_csv(path)
    except Exception:
        df = pd.read_csv(
            path,
            header=None,
            names=[
                "ingress","parser","logic","decision",
                "parser_lat","logic_lat","total_lat"
            ],
        )

    # Ensure required timestamp columns exist
    required = ["ingress","parser","logic","decision"]
    missing = [c for c in required if c not in df.columns]
    if missing:
        # maybe it was header=None but fewer cols; try to coerce by position
        if len(df.columns) >= 4:
            df.columns = required + list(df.columns[4:])
            missing = [c for c in required if c not in df.columns]
        if missing:
            raise SystemExit(f"CSV is missing required timestamp columns: {missing}")

    # Drop any NA rows that snuck in
    df = df.dropna(subset=required)
    # Force uint32 semantics for safety
    for c in required:
        df[c] = df[c].astype("uint32")

    return df

def wrap_delta(a: int, b: int) -> int:
    """Compute (b - a) mod 2^32 for uint32 cycle counters."""
    return ((int(b) - int(a)) + (1 << 32)) % (1 << 32)

def recompute_deltas(df: pd.DataFrame) -> pd.DataFrame:
    df = df.copy()
    df["parser_lat_c"] = [wrap_delta(a, b) for a, b in zip(df["ingress"], df["parser"])]
    df["logic_lat_c"]  = [wrap_delta(a, b) for a, b in zip(df["parser"],  df["logic"])]
    df["total_lat_c"]  = [wrap_delta(a, b) for a, b in zip(df["ingress"], df["decision"])]
    return df

def print_stats(series: pd.Series, clk_hz: float, title: str):
    s = series.astype("uint64")  # avoid pandas int overflow on quantiles
    def q(p): return int(s.quantile(p))
    stats = {
        "count": int(s.count()),
        "min":   int(s.min()) if len(s) else 0,
        "p50":   q(0.50) if len(s) else 0,
        "p90":   q(0.90) if len(s) else 0,
        "p99":   q(0.99) if len(s) else 0,
        "max":   int(s.max()) if len(s) else 0,
        "mean":  float(s.mean()) if len(s) else 0.0,
    }
    # Print cycles
    print(f"{title} (cycles): "
          f"count={stats['count']} min={stats['min']} p50={stats['p50']} "
          f"p90={stats['p90']} p99={stats['p99']} max={stats['max']} "
          f"mean={stats['mean']:.2f}")
    # Print microseconds
    to_us = lambda x: x / clk_hz * 1e6
    print(f"{title} (µs):     "
          f"min={to_us(stats['min']):.2f} p50={to_us(stats['p50']):.2f} "
          f"p90={to_us(stats['p90']):.2f} p99={to_us(stats['p99']):.2f} "
          f"max={to_us(stats['max']):.2f} mean={to_us(stats['mean']):.2f}")

def plot_hist(series: pd.Series, title: str, xlabel: str = "Cycles", save_path: str | None = None):
    plt.figure(figsize=(8, 4))
    plt.hist(series, bins=50)
    plt.xlabel(xlabel)
    plt.ylabel("Count")
    plt.title(title)
    plt.grid(True, linestyle="--", alpha=0.5)
    plt.tight_layout()
    if save_path:
        plt.savefig(save_path, dpi=120)
    else:
        plt.show()

def plot_cdf(series: pd.Series, title: str, xlabel: str = "Cycles", save_path: str | None = None):
    plt.figure(figsize=(8, 4))
    plt.hist(series, bins=200, cumulative=True, density=True)
    plt.xlabel(xlabel)
    plt.ylabel("CDF")
    plt.title(title)
    plt.grid(True, linestyle="--", alpha=0.5)
    plt.tight_layout()
    if save_path:
        plt.savefig(save_path, dpi=120)
    else:
        plt.show()

def main():
    ap = argparse.ArgumentParser(description="Analyse FPGA pipeline latencies")
    ap.add_argument("--file", "-f", default=DEFAULT_LAT_FILE, help="Path to latencies CSV")
    ap.add_argument("--clk-hz", type=float, default=DEFAULT_CLK_HZ, help="Clock frequency in Hz")
    ap.add_argument("--out-clean", default=None,
                    help="Optional path to write a cleaned CSV with recomputed *_lat_c")
    ap.add_argument("--save-plots", default=None,
                    help="Directory to save plots instead of showing (created if missing)")
    args = ap.parse_args()

    df = load_latencies_csv(args.file)
    df = recompute_deltas(df)

    # Print stats
    print_stats(df["parser_lat_c"], args.clk_hz, "Parser latency")
    print_stats(df["logic_lat_c"],  args.clk_hz, "Logic latency")
    print_stats(df["total_lat_c"],  args.clk_hz, "Total latency")

    # Optional: write cleaned CSV (timestamps + recomputed latencies only)
    if args.out_clean:
        cols = ["ingress","parser","logic","decision","parser_lat_c","logic_lat_c","total_lat_c"]
        df[cols].to_csv(args.out_clean, index=False)
        print(f"Wrote cleaned CSV → {args.out_clean}")

    # Plots
    save = args.save_plots
    if save:
        os.makedirs(save, exist_ok=True)
        plot_hist(df["parser_lat_c"], "Parser Latency (cycles)",
                  save_path=os.path.join(save, "hist_parser_cycles.png"))
        plot_hist(df["logic_lat_c"],  "Logic Latency (cycles)",
                  save_path=os.path.join(save, "hist_logic_cycles.png"))
        plot_hist(df["total_lat_c"],  "End-to-End Latency (cycles)",
                  save_path=os.path.join(save, "hist_total_cycles.png"))
        plot_cdf(df["total_lat_c"],   "End-to-End Latency CDF (cycles)",
                 save_path=os.path.join(save, "cdf_total_cycles.png"))
        print(f"Saved plots to: {save}")
    else:
        plot_hist(df["parser_lat_c"], "Parser Latency (cycles)")
        plot_hist(df["logic_lat_c"],  "Logic Latency (cycles)")
        plot_hist(df["total_lat_c"],  "End-to-End Latency (cycles)")
        plot_cdf(df["total_lat_c"],   "End-to-End Latency CDF (cycles)")

if __name__ == "__main__":
    main()
#!/usr/bin/env python3
"""
Analyse FPGA pipeline latencies from latencies.csv.

Reads ingress/parser/logic/decision timestamps, recomputes stage latencies
modulo 2^32 (wrap-safe), prints summary stats, and optionally plots histograms/CDFs.
"""

import argparse
import os
import sys
import pandas as pd
import matplotlib.pyplot as plt

# Defaults — tweak as needed
DEFAULT_LAT_FILE = "sim/latencies.csv"
DEFAULT_CLK_HZ = 250_000_000  # FPGA clock frequency (Hz)

def load_latencies_csv(path: str) -> pd.DataFrame:
    """
    Load the latency CSV.
    Handles both header/no-header cases, checks required columns exist,
    and coerces timestamp columns to uint32.
    """
    if not os.path.isfile(path):
        print(f"Error: '{path}' not found.", file=sys.stderr)
        sys.exit(1)

    try:
        # Attempt read with header row
        df = pd.read_csv(path)
    except Exception:
        # Fallback: assign default column names
        df = pd.read_csv(
            path,
            header=None,
            names=["ingress","parser","logic","decision","parser_lat","logic_lat","total_lat"],
        )

    # Ensure timestamp columns are present
    required = ["ingress","parser","logic","decision"]
    missing = [c for c in required if c not in df.columns]
    if missing:
        if len(df.columns) >= 4:
            df.columns = required + list(df.columns[4:])
            missing = [c for c in required if c not in df.columns]
        if missing:
            raise SystemExit(f"CSV missing required timestamp columns: {missing}")

    df = df.dropna(subset=required)  # drop any NA rows
    for c in required:
        df[c] = df[c].astype("uint32")
    return df

def wrap_delta(a: int, b: int) -> int:
    """Compute (b - a) mod 2^32 for wrap-around-safe cycle diffs."""
    return ((int(b) - int(a)) + (1 << 32)) % (1 << 32)

def recompute_deltas(df: pd.DataFrame) -> pd.DataFrame:
    """
    Compute fresh parser/logic/total latencies from timestamp columns,
    ignoring any *_lat columns in the CSV.
    """
    df = df.copy()
    df["parser_lat_c"] = [wrap_delta(a, b) for a, b in zip(df["ingress"], df["parser"])]
    df["logic_lat_c"]  = [wrap_delta(a, b) for a, b in zip(df["parser"],  df["logic"])]
    df["total_lat_c"]  = [wrap_delta(a, b) for a, b in zip(df["ingress"], df["decision"])]
    return df

def print_stats(series: pd.Series, clk_hz: float, title: str):
    """Print latency distribution stats in both cycles and microseconds."""
    s = series.astype("uint64")  # avoid overflow for quantiles
    q = lambda p: int(s.quantile(p)) if len(s) else 0
    stats = {
        "count": int(s.count()),
        "min":   int(s.min()) if len(s) else 0,
        "p50":   q(0.50),
        "p90":   q(0.90),
        "p99":   q(0.99),
        "max":   int(s.max()) if len(s) else 0,
        "mean":  float(s.mean()) if len(s) else 0.0,
    }
    # Cycles
    print(f"{title} (cycles): count={stats['count']} min={stats['min']} "
          f"p50={stats['p50']} p90={stats['p90']} p99={stats['p99']} "
          f"max={stats['max']} mean={stats['mean']:.2f}")
    # Microseconds
    to_us = lambda x: x / clk_hz * 1e6
    print(f"{title} (µs):     min={to_us(stats['min']):.2f} "
          f"p50={to_us(stats['p50']):.2f} p90={to_us(stats['p90']):.2f} "
          f"p99={to_us(stats['p99']):.2f} max={to_us(stats['max']):.2f} "
          f"mean={to_us(stats['mean']):.2f}")

def plot_hist(series: pd.Series, title: str, xlabel: str = "Cycles", save_path: str | None = None):
    """Plot a histogram of latency values."""
    plt.figure(figsize=(8, 4))
    plt.hist(series, bins=50)
    plt.xlabel(xlabel)
    plt.ylabel("Count")
    plt.title(title)
    plt.grid(True, linestyle="--", alpha=0.5)
    plt.tight_layout()
    plt.savefig(save_path, dpi=120) if save_path else plt.show()

def plot_cdf(series: pd.Series, title: str, xlabel: str = "Cycles", save_path: str | None = None):
    """Plot the cumulative distribution function (CDF) of latency values."""
    plt.figure(figsize=(8, 4))
    plt.hist(series, bins=200, cumulative=True, density=True)
    plt.xlabel(xlabel)
    plt.ylabel("CDF")
    plt.title(title)
    plt.grid(True, linestyle="--", alpha=0.5)
    plt.tight_layout()
    plt.savefig(save_path, dpi=120) if save_path else plt.show()

def main():
    ap = argparse.ArgumentParser(description="Analyse FPGA pipeline latencies")
    ap.add_argument("--file", "-f", default=DEFAULT_LAT_FILE, help="Path to latencies CSV")
    ap.add_argument("--clk-hz", type=float, default=DEFAULT_CLK_HZ, help="Clock frequency in Hz")
    ap.add_argument("--out-clean", help="Write cleaned CSV with recomputed *_lat_c")
    ap.add_argument("--save-plots", help="Directory to save plots instead of showing")
    args = ap.parse_args()

    df = load_latencies_csv(args.file)
    df = recompute_deltas(df)

    # Print per-stage + total stats
    print_stats(df["parser_lat_c"], args.clk_hz, "Parser latency")
    print_stats(df["logic_lat_c"],  args.clk_hz, "Logic latency")
    print_stats(df["total_lat_c"],  args.clk_hz, "Total latency")

    # Optionally save cleaned CSV
    if args.out_clean:
        cols = ["ingress","parser","logic","decision","parser_lat_c","logic_lat_c","total_lat_c"]
        df[cols].to_csv(args.out_clean, index=False)
        print(f"Wrote cleaned CSV → {args.out_clean}")

    # Plot histograms and CDFs
    if args.save_plots:
        os.makedirs(args.save_plots, exist_ok=True)
        plot_hist(df["parser_lat_c"], "Parser Latency (cycles)",
                  save_path=os.path.join(args.save_plots, "hist_parser_cycles.png"))
        plot_hist(df["logic_lat_c"], "Logic Latency (cycles)",
                  save_path=os.path.join(args.save_plots, "hist_logic_cycles.png"))
        plot_hist(df["total_lat_c"], "End-to-End Latency (cycles)",
                  save_path=os.path.join(args.save_plots, "hist_total_cycles.png"))
        plot_cdf(df["total_lat_c"],  "End-to-End Latency CDF (cycles)",
                 save_path=os.path.join(args.save_plots, "cdf_total_cycles.png"))
        print(f"Saved plots to: {args.save_plots}")
    else:
        plot_hist(df["parser_lat_c"], "Parser Latency (cycles)")
        plot_hist(df["logic_lat_c"],  "Logic Latency (cycles)")
        plot_hist(df["total_lat_c"],  "End-to-End Latency (cycles)")
        plot_cdf(df["total_lat_c"],   "End-to-End Latency CDF (cycles)")

if __name__ == "__main__":
    main()

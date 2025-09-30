import serial
import time
import matplotlib.pyplot as plt
from collections import deque
from datetime import datetime
import csv
import argparse
import sys

"""
MPU6050 live plot from Arduino serial.
Arduino must print: millis,mag,rms
Example line: 1234,0.0456,0.0238
"""

def parse_csv(line: str):
    parts = line.strip().split(",")
    if len(parts) != 3:
        return None
    try:
        ms = int(parts[0])
        mag = float(parts[1])
        rms = float(parts[2])
        return ms, mag, rms
    except:
        return None

def main():
    port = "COM3"
    baud = 115200

    try:
        ser = serial.Serial(port, baud, timeout=1)
    except Exception as e:
        print(f"Could not open {port}: {e}")
        sys.exit(1)

    time.sleep(2)  # let Arduino reset

    stamp = datetime.now().strftime("%Y%m%d_%H%M%S")
    csv_name = f"vibration_{stamp}.csv"
    png_name = f"vibration_{stamp}.png"

    ts = deque(maxlen=1200)
    mags = deque(maxlen=1200)
    rmss = deque(maxlen=1200)

    csv_file = open(csv_name, "w", newline="")
    writer = csv.writer(csv_file)
    writer.writerow(["t_ms", "mag_g", "rms_g"])

    plt.figure(figsize=(9, 5))
    plt.title("MPU6050 Vibration (mag & rms)")
    plt.xlabel("Time (s)")
    plt.ylabel("Acceleration (g)")
    (line_mag,) = plt.plot([], [], label="mag")
    (line_rms,) = plt.plot([], [], label="rms")
    plt.legend()
    plt.grid(True)

    t0_ms = None

    print(f"Reading from {port} @ {baud}. Press Ctrl+C to stop.")
    try:
        while True:
            raw = ser.readline().decode(errors="ignore")
            rec = parse_csv(raw)
            if rec is None:
                continue

            ms, mag, rms = rec
            writer.writerow([ms, mag, rms])

            if t0_ms is None:
                t0_ms = ms
            t = (ms - t0_ms) / 1000.0

            ts.append(t); mags.append(mag); rmss.append(rms)

            line_mag.set_data(ts, mags)
            line_rms.set_data(ts, rmss)

            if len(ts) > 1:
                plt.xlim(ts[0], ts[-1])

            ymin = min(min(mags), min(rmss)) if mags and rmss else -0.1
            ymax = max(max(mags), max(rmss)) if mags and rmss else 0.1
            pad = max(0.1, 0.2 * (ymax - ymin))
            plt.ylim(ymin - pad, ymax + pad)

            plt.pause(0.001)

    except KeyboardInterrupt:
        print("\nStopping…")
    finally:
        ser.close()
        csv_file.close()
        plt.savefig(png_name, dpi=150, bbox_inches="tight")
        print(f"Saved CSV: {csv_name}")
        print(f"Saved PNG: {png_name}")

if __name__ == "__main__":
    main()

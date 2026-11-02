#!/usr/bin/env python3

import argparse
import math
import struct
from pathlib import Path


def decode_pcm16le(data):
    if len(data) % 2:
        raise ValueError("PCM data must contain complete 16-bit samples.")

    return [sample[0] for sample in struct.iter_unpack("<h", data)]


def analyze_pcm(samples, sample_rate):
    if not samples:
        raise ValueError("PCM file contains no samples.")
    if sample_rate <= 0:
        raise ValueError("Sample rate must be greater than zero.")

    peak = max(abs(sample) for sample in samples)
    mean = sum(samples) / len(samples)
    rms = math.sqrt(sum(sample * sample for sample in samples) / len(samples))

    return {
        "sample_count": len(samples),
        "duration_seconds": len(samples) / sample_rate,
        "peak": peak,
        "rms": rms,
        "mean": mean,
        "clipped_samples": sum(abs(sample) >= 32760 for sample in samples),
    }


def main():
    parser = argparse.ArgumentParser(
        description="Inspect raw signed 16-bit little-endian mono PCM audio."
    )
    parser.add_argument("file", type=Path)
    parser.add_argument("--sample-rate", type=int, default=16000)
    args = parser.parse_args()

    try:
        samples = decode_pcm16le(args.file.read_bytes())
        result = analyze_pcm(samples, args.sample_rate)
    except (OSError, ValueError) as error:
        parser.error(str(error))

    print(f"File: {args.file}")
    print(f"Sample rate: {args.sample_rate} Hz")
    print(f"Samples: {result['sample_count']}")
    print(f"Duration: {result['duration_seconds']:.3f} s")
    print(f"Peak amplitude: {result['peak']}")
    print(f"RMS amplitude: {result['rms']:.2f}")
    print(f"Mean/DC offset: {result['mean']:.2f}")
    print(f"Near-full-scale samples: {result['clipped_samples']}")


if __name__ == "__main__":
    main()

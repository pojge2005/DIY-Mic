# DIY-Mic Tests and Diagnostics

This folder contains host-side tests and diagnostic tools. These tests do not replace microphone hardware validation.

## Structure

```text
tests/
├── README.md
├── test_pcm_inspect.py
└── tools/
    └── pcm_inspect.py
```

## Run unit tests

From the repository root:

```bash
python3 -m unittest discover -s tests -p 'test_*.py' -v
```

The test suite uses Python's standard library only.

## Inspect raw PCM

```bash
python3 tests/tools/pcm_inspect.py path/to/capture.pcm --sample-rate 16000
```

Supported input:

- Raw signed 16-bit PCM.
- Little-endian byte order.
- Mono samples.
- No WAV header.
- Sample rate supplied by the user; defaults to 16 kHz.

The utility reports sample count, duration, peak amplitude, RMS amplitude, mean/DC offset, and near-full-scale sample count.

## Important limitations

- It does not parse the DIY-Mic WebSocket protocol.
- It does not extract audio from firmware logs or packet captures.
- It does not prove that the microphone's I²S sample alignment is correct.
- It does not measure end-to-end wireless latency.
- It does not measure SNR or classify noise sources.
- The PCM format must match the actual capture file. Confirm sample rate, bit depth, channel count, and byte order before interpreting results.

Add future tests for packet framing, sequence loss, jitter buffering, latency, and receiver reconnection after the common protocol has been specified.


## ESP32-S3 BLE tests

- [ESP32-S3 BLE test guide](../ESP32-S3/tests/README.md)
- [ESP32-S3 command reference](../ESP32-S3/docs/COMMAND_REFERENCE.md)
- [ESP32-S3 board and GPIO configuration](../ESP32-S3/docs/HARDWARE_CONFIGURATION.md)

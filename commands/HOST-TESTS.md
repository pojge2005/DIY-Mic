# Host Test Commands

Run the following commands from the repository root unless otherwise stated.

## 1. Run Python unit tests

```bash
python3 -m unittest discover -s tests -p 'test_*.py' -v
```

- **Purpose:** discover and run repository tests matching `test_*.py`.
- **Use case:** verify PCM decoding and basic audio-metric helper behavior after changing host-side code.
- **Dependency:** Python standard library only, according to the current test documentation.
- **Evidence:** preserve the complete test summary and any traceback.

## 2. Inspect raw PCM

```bash
python3 tests/tools/pcm_inspect.py capture.pcm --sample-rate 16000
```

- **Purpose:** inspect raw signed 16-bit little-endian mono PCM.
- **Use case:** report sample count, duration, peak amplitude, RMS amplitude, mean/DC offset, and near-full-scale sample count.
- **Input requirements:** raw PCM without a WAV header; mono; signed 16-bit little-endian; sample rate must match the capture.
- **Limitation:** this utility does not decode the DIY-Mic WebSocket protocol, recover audio from logs/packet captures, verify I²S alignment, or measure end-to-end latency/SNR.

Replace `capture.pcm` and `16000` with the actual file and sample rate.

## 3. ESP32-S3 BLE host test

Follow [ESP32-S3 Command Guide](ESP32-S3.md). It creates an isolated Python virtual environment, installs Bleak, and runs `ESP32-S3/tests/tools/ble_notify_test.py`.

## 4. Test result policy

A passing host-side unit test does not prove microphone hardware operation. Keep software tests, BLE tests, I²S tests, and end-to-end playback tests as separate result categories.

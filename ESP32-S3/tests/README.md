# ESP32-S3 Host-side BLE Tests

This folder contains host-side BLE diagnostics. Run commands from the repository root.

## Requirements

- Ubuntu with BlueZ.
- Working Bluetooth adapter.
- ESP32-S3 powered and advertising as `DIY-Mic-S3`.
- Python 3.10 or newer.
- Observed peripheral address: `30:ED:A0:A8:A4:F0`.

## Install

```bash
python3 -m venv .venv
source .venv/bin/activate
python3 -m pip install -r ESP32-S3/tests/tools/requirements.txt
```

| Command | Purpose |
|---|---|
| `python3 -m venv .venv` | Create isolated Python environment |
| `source .venv/bin/activate` | Activate the environment |
| `python3 -m pip install -r ESP32-S3/tests/tools/requirements.txt` | Install Bleak |

## Run BLE test

```bash
python3 ESP32-S3/tests/tools/ble_notify_test.py --address 30:ED:A0:A8:A4:F0 --listen-seconds 10
```

- `--address`: BLE MAC address of the peripheral.
- `--listen-seconds`: notification listening duration.
- The script reads Status, subscribes to Status and Audio when supported, writes ASCII `PING` to Control, and prints notifications as hex and ASCII.

The script does not send an undocumented audio-start command. If audio is disabled in firmware, no Audio notifications may arrive even if subscription succeeds.

## Command library

- [ESP32-S3 command guide](../../commands/ESP32-S3.md)
- [Project command index](../../commands/README.md)
- [Terminal log archive](../../commands/logs/README.md)

## Interactive BlueZ commands

Follow [Command Reference](../docs/COMMAND_REFERENCE.md) for discovery, GATT inspection, Status read, PING/PONG, and Audio notification subscription.

## Evidence

Copy full command output into [BLE Test Report](../docs/BLE_TEST_REPORT.md). Record date, board/firmware revision, address, command, characteristic UUID, output, and result. Do not mark expected behavior as PASS without observed output.


## INMP441 I²S hardware diagnostic

The ESP32-S3 INMP441 diagnostic is currently an experimental firmware test, separate from the host-side BLE utility. The supplied 2026-11-09 serial output is archived in [the I²S test report](../docs/I2S_TEST_REPORT.md) and [the terminal log](../../commands/logs/2026-11-09_esp32-s3_inmp441-i2s-diagnostic.log).

Current result:
- I²S driver initialization: PASS.
- Stable non-zero capture: NOT VERIFIED.
- Raw 24-bit alignment and sample conversion: NOT VERIFIED.
- Clean PCM audio: NOT VERIFIED.
- Physical GPIO mapping and microphone supply: pending verification.

Do not use the current experimental capture as an audio-streaming source. Do not mark I²S capture as PASS until the raw sample format, selected channel, physical wiring, and controlled speech response are verified. The temporary diagnostic sketch is not treated as production firmware.

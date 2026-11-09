# DIY-Mic — ESP32-S3 BLE Bring-up

This is the isolated ESP32-S3 development track at the repository root. It does not replace or modify the ESP8266 or ESP32-C3 history.

## Hardware baseline

- SoC: ESP32-S3, QFN56, silicon revision v0.2.
- Flash: 16 MB.
- PSRAM: 8 MB embedded, AP_3v3.
- Crystal: 40 MHz.
- BLE MAC observed: `30:ED:A0:A8:A4:F0`.
- Project target: N16R8.
- Microphone: INMP441 I²S MEMS breakout.
- Exact carrier-board manufacturer/model and PCB revision: not yet identified.

GPIO4=BCLK, GPIO5=WS/LRCLK, GPIO6=SD/DOUT is provisional only. Verify it against the physical board pinout before wiring permanently.

See [Board and GPIO Configuration](docs/HARDWARE_CONFIGURATION.md), [ESP32-S3 Command Guide](../commands/ESP32-S3.md), and the [project-wide Command Library](../commands/README.md). The board-specific [Command Reference](docs/COMMAND_REFERENCE.md) remains the detailed BLE procedure.

## Structure

```text
ESP32-S3/
├── README.md
├── AGENTS.md
├── docs/
│   ├── ARCHITECTURE.md
│   ├── BLE_GATT_SPECIFICATION.md
│   ├── BLE_TEST_REPORT.md
│   ├── COMMAND_REFERENCE.md
│   ├── DEVELOPMENT_LOG.md
│   ├── HARDWARE_CONFIGURATION.md
│   ├── I2S_TEST_REPORT.md
│   └── KNOWN_ISSUES.md
└── tests/
    ├── README.md
    └── tools/
        ├── ble_notify_test.py
        └── requirements.txt
```

## BLE status

| Test | Status |
|---|---|
| BLE discovery | PASS (reported) |
| BLE connection | PASS |
| GATT discovery | PASS (reported) |
| Status read | PASS — CONNECTED |
| Control write / PING-PONG | PENDING |
| Audio notifications | PENDING |
| Audio playback | NOT TESTED |

The recorded Status read was `43 4f 4e 4e 45 43 54 45 44` (ASCII `CONNECTED`).

## I²S microphone status

| Test | Status |
|---|---|
| I²S driver initialization | PASS |
| Non-zero raw data | Intermittently observed |
| Stable capture | FAIL / NOT VERIFIED |
| 24-bit alignment and `raw >> 8` conversion | NOT VERIFIED |
| Clean PCM audio | NOT VERIFIED |
| Physical GPIO and supply verification | BLOCKED |

The 2026-11-09 diagnostic showed zero-data intervals, intermittent non-zero words, and repeated values at the candidate 24-bit limits. Do not treat the current capture as valid PCM or integrate it into BLE audio yet. See [INMP441 I²S Diagnostic Report](docs/I2S_TEST_REPORT.md) and the [supplied serial output](../commands/logs/2026-11-09_esp32-s3_inmp441-i2s-diagnostic.log).

## Command documentation

- [ESP32-S3 terminal commands, purpose, and use cases](../commands/ESP32-S3.md)
- [Project-wide command index](../commands/README.md)
- [Terminal log archive and capture rules](../commands/logs/README.md)

## Run the Python BLE test utility

From the repository root:

```bash
python3 -m venv .venv
source .venv/bin/activate
python3 -m pip install -r ESP32-S3/tests/tools/requirements.txt
python3 ESP32-S3/tests/tools/ble_notify_test.py --address 30:ED:A0:A8:A4:F0 --listen-seconds 10
```

The utility reads Status, subscribes to Status and Audio when supported, writes PING to Control, and prints received data. It does not send an undocumented audio-start command.

## Firmware status

This track currently documents BLE bring-up and host-side test tools. It is not a complete microphone firmware release. See the command reference for PlatformIO build, upload, and serial-monitor commands.

## Reports

- [BLE Test Report](docs/BLE_TEST_REPORT.md)
- [INMP441 I²S Diagnostic Report](docs/I2S_TEST_REPORT.md)
- [GATT Specification](docs/BLE_GATT_SPECIFICATION.md)
- [Development Log](docs/DEVELOPMENT_LOG.md)
- [Known Issues](docs/KNOWN_ISSUES.md)

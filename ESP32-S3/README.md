# DIY-Mic — ESP32-S3 BLE Bring-up

This directory contains the isolated ESP32-S3 development track. It is located at the repository root so board-specific work is not mixed into the historical ESP8266 or ESP32-C3 directories.

## Hardware

- MCU: ESP32-S3 N16R8 (reported board/module configuration; exact board revision still needs recording)
- Microphone: INMP441 I²S MEMS microphone
- Current focus: BLE GATT discovery, connection, status/control characteristics, and notification testing

## Directory layout

```text
ESP32-S3/
├── README.md
├── AGENTS.md
├── docs/
│   ├── ARCHITECTURE.md
│   ├── BLE_GATT_SPECIFICATION.md
│   ├── BLE_TEST_REPORT.md
│   ├── HARDWARE_CONFIGURATION.md
│   ├── DEVELOPMENT_LOG.md
│   └── KNOWN_ISSUES.md
└── tests/
    ├── README.md
    └── tools/
        ├── ble_notify_test.py
        └── requirements.txt
```

Firmware implementation will be added in this board-specific directory only after the BLE bring-up baseline and hardware details are reviewed. No existing firmware is moved, deleted, or overwritten by this change.

## Current BLE evidence

| Check | Result |
|---|---|
| BLE advertising / device discovery | Reported PASS |
| BLE connection from Ubuntu | PASS |
| GATT service discovery | PASS |
| Status characteristic read | PASS — returned ASCII `CONNECTED` |
| Control characteristic write / PING-PONG | PENDING in the available test log |
| Audio characteristic notifications | PENDING in the available test log |

See [BLE Test Report](docs/BLE_TEST_REPORT.md) and [GATT Specification](docs/BLE_GATT_SPECIFICATION.md).

## Host test setup

```bash
cd ESP32-S3/tests/tools
python3 -m pip install -r requirements.txt
python3 ble_notify_test.py --help
```

Do not mark a test as PASS until its output has been recorded in the test report.

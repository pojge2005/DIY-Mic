# ESP32-S3 Host-side BLE Tests

## Requirements

- Python 3.10 or newer
- Bluetooth adapter supported by BlueZ
- ESP32-S3 peripheral powered and advertising
- BLE client access on Ubuntu

## Install

```bash
python3 -m pip install -r tools/requirements.txt
```

## Run

```bash
python3 tools/ble_notify_test.py --address 30:ED:A0:A8:A4:F1
```

The address is an example from the recorded test session. Replace it if the peripheral address changes.

The script connects, subscribes to Status and Audio notifications, reads Status, sends ASCII `PING` to Control, and listens for notifications. It reports received data as hex and printable ASCII where possible.

A script run is not itself proof of success; copy the actual output into [BLE Test Report](../docs/BLE_TEST_REPORT.md).

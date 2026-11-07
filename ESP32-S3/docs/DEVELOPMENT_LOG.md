# ESP32-S3 Development Log

## 2026-11-06 — Chip identification and BLE baseline

Reported chip information:
- ESP32-S3 QFN56, silicon revision v0.2.
- 16 MB flash, quad mode.
- 8 MB embedded PSRAM, AP_3v3.
- 40 MHz crystal.
- BLE address: `30:ED:A0:A8:A4:F0`.
- Project target: N16R8.

The exact carrier-board manufacturer, product name, and PCB revision remain unidentified.

BLE evidence:
- Discovery: PASS (reported).
- Ubuntu BLE connection: PASS.
- GATT service discovery: PASS (reported).
- Status read: PASS.
- Status payload: `43 4f 4e 4e 45 43 54 45 44` (`CONNECTED`).

Observed BlueZ paths:
- Status: `service000e/char000f`.
- Control: `service000e/char0012`.
- Device path prefix: `/org/bluez/hci0/dev_30_ED_A0_A8_A4_F0/`.

Control write, PING/PONG, and Audio notifications remain pending. Audio streaming was disabled during the earlier control-channel test.

Provisional INMP441 GPIO proposal:
- GPIO4 = BCLK.
- GPIO5 = WS/LRCLK.
- GPIO6 = SD/DOUT.

The mapping is not physically verified. The project-wide command library is under [commands/](../../commands/README.md), with [ESP32-S3 command procedures](../../commands/ESP32-S3.md) and the [terminal log archive](../../commands/logs/README.md).

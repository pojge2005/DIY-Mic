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


## 2026-11-09 — INMP441 I²S diagnostic

A temporary diagnostic was run on the reported ESP32-S3 N16R8 + INMP441 setup. The serial output is archived in [the supplied I²S diagnostic log](../../commands/logs/2026-11-09_esp32-s3_inmp441-i2s-diagnostic.log), and the interpretation is recorded in the [I²S test report](I2S_TEST_REPORT.md).

Observed configuration:
- I²S0 master RX.
- 16 kHz sample rate.
- 32-bit I²S slots.
- `I2S_CHANNEL_FMT_RIGHT_LEFT`.
- GPIO4=BCLK, GPIO5=WS/LRCLK, GPIO6=SD/DOUT (still provisional).
- Statistics calculated from `raw >> 8`; this conversion is not validated.

Observed results:
- I²S driver initialization: PASS.
- Non-zero raw words: observed intermittently.
- Slot A and Slot B statistics alternated between non-zero data and zero-data windows.
- Repeated extrema near the candidate signed 24-bit limits triggered clipping warnings.
- Raw words included non-zero low bytes, so the assumed 24-bit alignment was not established.
- The serial monitor disconnected with `Errno 5` and reconnected; the cause was not established.

Conclusion: stable, correctly aligned, unclipped PCM has not been demonstrated. Do not mark microphone capture as PASS or proceed to BLE audio integration. Exact carrier-board identity, GPIO mapping, physical wiring, microphone supply voltage, and controlled quiet-versus-speech response remain unverified.

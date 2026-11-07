# ESP32-S3 Hardware Configuration

## Current target

- MCU/module: ESP32-S3 N16R8 (reported)
- Microphone: INMP441 I²S MEMS breakout
- Development host: Ubuntu

## Details still required

The available BLE log does not specify the exact development board manufacturer/model or PCB revision. Record the exact board marking before finalizing the hardware baseline.

| Item | Status |
|---|---|
| Exact ESP32-S3 board model / revision | PENDING |
| Flash / PSRAM configuration confirmation | N16R8 reported; verify against board marking |
| INMP441 BCLK pin | PENDING |
| INMP441 WS/LRCLK pin | PENDING |
| INMP441 SD/DOUT pin | PENDING |
| INMP441 L/R selection | PENDING |
| Microphone supply voltage and grounding | PENDING |
| Power source and current measurements | PENDING |
| Antenna / enclosure constraints | PENDING |

Do not reuse ESP32-C3 GPIO assignments. ESP32-S3 pin allocation must be based on the exact board pinout and checked against USB, flash/PSRAM, boot-strapping, and peripheral constraints.

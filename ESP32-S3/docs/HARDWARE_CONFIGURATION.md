# ESP32-S3 Board and GPIO Configuration

## Confirmed chip/module information

Reported by the ESP32-S3 identification session on 2026-11-06:

| Property | Reported value |
|---|---|
| SoC | ESP32-S3 |
| Package | QFN56 |
| Silicon revision | v0.2 |
| Flash | 16 MB, quad mode |
| PSRAM | 8 MB embedded PSRAM, AP_3v3 |
| Crystal | 40 MHz |
| BLE MAC observed | `30:ED:A0:A8:A4:F0` |
| Project memory target | N16R8 |

## Physical board identity limitation

The exact carrier/development-board manufacturer, product name, and PCB revision have not been identified from the available evidence. Do not describe the physical board as an official Espressif DevKitC-1 or RYMCU board until its PCB silkscreen, label, or schematic confirms it.

PlatformIO previously displayed candidates named Espressif ESP32-S3-DevKitC-1-N8 and RYMCU ESP32-S3-DevKitC-1-N8R2. These candidate names do not prove that either board matches the user's N16R8 hardware. Verify the physical board before selecting a final PlatformIO board definition.

## Microphone

- Module: INMP441 I²S MEMS breakout.
- Signals: BCLK/SCK, WS/LRCLK, SD/DOUT, 3V3, GND.
- Confirm the breakout's permitted supply voltage before connecting power. Do not assume a 5 V input is safe.

## Provisional GPIO allocation

These pins were proposed in the earlier design discussion. They are not yet verified against the physical carrier-board pinout.

| INMP441 pin | ESP32-S3 GPIO | Signal | Status |
|---|---:|---|---|
| SCK / BCLK | GPIO4 | I²S bit clock | PROVISIONAL |
| WS / LRCLK | GPIO5 | I²S word select | PROVISIONAL |
| SD / DOUT | GPIO6 | I²S data input | PROVISIONAL |
| L/R | GND | Left-channel selection | Verify breakout |
| VDD | 3V3 | Microphone supply | Verify board rail |
| GND | GND | Common ground | Required |

Do not treat GPIO4/5/6 as final until the board pinout is checked and I²S capture succeeds. Do not copy ESP32-C3 GPIO assignments into this ESP32-S3 design.

## GPIO validation checklist

1. Read the exact board name and revision printed on the PCB.
2. Compare the board pin labels with its schematic/pinout.
3. Check GPIO4, GPIO5, and GPIO6 availability and board-level use.
4. Check boot-strapping, USB, flash, PSRAM, and onboard peripheral constraints.
5. Confirm the microphone breakout supply range and existing decoupling.
6. Record a wiring photograph and final pin table.
7. Measure 3.3 V at microphone VDD-to-GND before enabling I²S.
8. Verify changing sample data while speaking and quiet data while silent.

## PlatformIO checks

Run in the Ubuntu terminal:

```bash
pio --version
pio boards esp32-s3
pio project config
pio device list
```

- `pio --version`: records PlatformIO Core version.
- `pio boards esp32-s3`: lists ESP32-S3 board definitions.
- `pio project config`: prints resolved project configuration.
- `pio device list`: lists serial ports visible to PlatformIO.

The final `platformio.ini` must match the verified flash size, flash mode, PSRAM type, framework, upload speed, and serial port. Do not use an N8/N8R2 preset without verifying its memory settings.

## Board information still required

| Field | Status |
|---|---|
| Manufacturer | Not identified |
| Exact board/product name | Not identified |
| PCB revision | Not identified |
| PCB photo / silkscreen evidence | Not recorded |
| Final GPIO allocation | Pending physical validation |
| INMP441 wiring test | Pending |

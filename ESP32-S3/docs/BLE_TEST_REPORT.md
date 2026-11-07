# BLE Test Report — ESP32-S3

## Test environment

- Host: Ubuntu with BlueZ command-line BLE tools.
- Peripheral: DIY-Mic-S3.
- BLE MAC observed: `30:ED:A0:A8:A4:F0`.
- Chip: ESP32-S3 QFN56, revision v0.2.
- Memory reported: 16 MB flash and 8 MB embedded PSRAM (AP_3v3).
- Crystal: 40 MHz.
- Chip identification date: 2026-11-06; exact BLE test timestamp not recorded.

## Confirmed results

| Test | Result | Evidence |
|---|---|---|
| BLE discovery | PASS (reported) | Peripheral discovered by Ubuntu |
| BLE connection | PASS | Host connected to DIY-Mic-S3 |
| GATT service discovery | PASS (reported) | Custom service and characteristics accessible |
| Status characteristic read | PASS | `43 4f 4e 4e 45 43 54 45 44` = `CONNECTED` |

## Pending tests

| Test | Result | Required evidence |
|---|---|---|
| Control write | PENDING | BlueZ write result and no ATT error |
| PING/PONG | PENDING | Actual PONG response and response characteristic |
| Status notifications | PENDING | `notify on` result and captured notification if supported |
| Audio subscription | PENDING | Audio characteristic `notify on` result |
| Audio payload delivery | PENDING | Captured notifications with timestamps and lengths |
| Audio playback | NOT TESTED | Decoded PCM capture and receiver playback |

## BlueZ object paths observed

| Characteristic | Object path |
|---|---|
| Status | `/org/bluez/hci0/dev_30_ED_A0_A8_A4_F0/service000e/char000f` |
| Control | `/org/bluez/hci0/dev_30_ED_A0_A8_A4_F0/service000e/char0012` |
| Audio | Not recorded; resolve by Audio UUID after `list-attributes` |

Object paths may change after reconnecting. Resolve the current path from the live GATT list and match by UUID.

## Interpretation

The Status read proves the host could connect and read the Status characteristic. It does not prove Control writes, PING/PONG, Audio notifications, audio capture, or playback.

Audio streaming was disabled during the earlier control-channel test. The audio-start command is not established in the available source evidence.

## Next test sequence

1. Follow [Command Reference](COMMAND_REFERENCE.md).
2. Read Status and save the output.
3. Enable Status notifications only if supported by its GATT properties.
4. Write ASCII PING (`50 49 4e 47`) to Control.
5. Capture PONG and identify its response characteristic.
6. Identify Audio by UUID and enable notifications.
7. Confirm the audio-start command from firmware source before starting a stream.
8. Capture notification payloads, lengths, and timestamps.
9. Save a raw capture and document PCM format before playback tests.

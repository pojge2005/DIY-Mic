# Development History

## 2026-11 — ESP32-S3 BLE Bring-up Baseline

- Created the isolated root-level `ESP32-S3/` development track.
- Recorded the reported ESP32-S3 N16R8 + INMP441 hardware target.
- Recorded BLE discovery, connection, GATT discovery, and Status read as passed based on the supplied test log.
- Status characteristic returned `43 4f 4e 4e 45 43 54 45 44` (`CONNECTED`).
- Kept Control PING/PONG and Audio notifications pending because the supplied log did not include successful results.
- Added a host-side Bleak test utility and its dependency file.
- Preserved existing ESP8266 and ESP32-C3 implementation directories without modification.

## Historical baseline

The ESP8266 V0.5 Wi-Fi microphone prototype remains the owner-reported working reference described in the root README and test records. ESP32-C3 work remains available in its existing board-specific directory.


## 2026-11-07 — ESP32-S3 Hardware and Command Documentation

- Recorded reported ESP32-S3 QFN56 revision v0.2, 16 MB flash, 8 MB embedded PSRAM (AP_3v3), 40 MHz crystal, and BLE MAC.
- Documented GPIO4/5/6 as a provisional INMP441 mapping, not a physically verified allocation.
- Recorded that the exact carrier-board manufacturer/model and PCB revision remain unknown.
- Added command-by-command PlatformIO, BlueZ `bluetoothctl`, and Python BLE test instructions with each command's purpose.
- Added known BlueZ object paths for Status and Control from the supplied test notes.
- Kept Control PING/PONG and Audio notification results pending actual output.

## 2026-11-07 — Central Command and Log Library

- Added the root-level `commands/` index and platform-specific command guides for ESP32-S3, ESP32-C3, and ESP8266.
- Added Git and host-test command guides.
- Added a dated terminal-log archive with naming, capture, metadata, and evidence rules.
- Archived the supplied ESP32-S3 Status-read output without inventing a full terminal transcript.
- Linked the command library from the project README, test guides, status, roadmap, and BLE report.



## 2026-11-09 — ESP32-S3 INMP441 I²S diagnostic

- Added an I²S diagnostic report and archived the serial output supplied during the session.
- Recorded I²S driver initialization as PASS.
- Recorded intermittent non-zero raw data, zero-data windows, and clipping warnings in channel statistics.
- Recorded that raw sample alignment and the `raw >> 8` conversion are not verified.
- Kept microphone capture acceptance FAIL / NOT VERIFIED; no valid PCM or acoustic response was established.
- Kept GPIO4/5/6 provisional because the exact carrier-board pinout and physical wiring have not been verified.
- Did not change the historical ESP8266 or ESP32-C3 implementation or claim BLE audio streaming.

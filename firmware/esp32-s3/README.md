# DIY-Mic — ESP32-S3 Bring-up

**Status:** Next hardware platform selected at the ESP32-S3 family level.  
**Exact board/module:** Not yet recorded.  
**Firmware status:** Not started.

Before creating the S3 PlatformIO project, record the exact board name/revision and verify:
- SoC/module variant.
- Flash capacity and whether PSRAM is fitted.
- USB interface and serial/JTAG routing.
- Board-specific GPIO availability and strapping pins.
- Correct PlatformIO board ID and framework version.
- INMP441 wiring after the board pinout is verified.

Bring-up sequence:
1. Record the physical board and module markings.
2. Create a serial-only PlatformIO baseline.
3. Verify build, upload, USB serial, reset behavior, and stable heap.
4. Run an isolated Wi-Fi SoftAP beacon test and verify SSID visibility from Ubuntu and Android.
5. Validate INMP441 I²S capture.
6. Only then integrate HTTP/WebSocket and audio streaming.

Do not copy ESP32-C3 GPIO assignments, flash settings, USB settings, or PlatformIO board IDs into this project without checking the exact S3 board.

The ESP32-C3 experiment is closed and preserved under ../esp32-c3/ARCHIVE.md.

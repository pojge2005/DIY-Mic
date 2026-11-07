# ESP32-S3 Development Rules

- Keep all ESP32-S3-specific files under the repository-root `ESP32-S3/` directory.
- Do not modify or relocate the historical `firmware/esp8266/` or `firmware/esp32-c3/` trees.
- Do not copy ESP32-C3 pin assignments or PlatformIO settings into this target without checking the ESP32-S3 board documentation.
- Keep BLE control/status and audio transport claims separate.
- Record observed test output and date; use PASS, FAIL, or PENDING.
- Never mark PING/PONG or audio notifications as passed without captured evidence.
- Keep firmware work separate from host-side BLE test utilities.
- Use small, direct modules and avoid adding dependencies without a clear requirement.

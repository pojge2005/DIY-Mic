# ESP32-S3 Known Issues and Open Questions

## Hardware identity

- ESP32-S3 QFN56 silicon revision v0.2 is reported.
- 16 MB flash, 8 MB embedded PSRAM (AP_3v3), and 40 MHz crystal are reported.
- Exact carrier-board manufacturer, product name, and PCB revision are unknown.
- PlatformIO N8/N8R2 candidates must not be assumed to match the N16R8 target.

## GPIO and microphone

- GPIO4=BCLK, GPIO5=WS/LRCLK, GPIO6=SD/DOUT is provisional.
- Physical board pinout has not been checked.
- INMP441 supply, breakout decoupling, L/R selection, and final wiring need confirmation.
- I²S capture is not evidenced in the BLE report.

## BLE

- Control write and PING/PONG are not confirmed.
- Status notification capability must be read from live GATT properties.
- Audio subscription and payload delivery are not confirmed.
- Audio-start command is not recorded; do not guess one.
- Audio format, MTU, throughput, latency, packet loss, and power are unmeasured.
- Android and PC audio playback are not established.

See [Command Reference](COMMAND_REFERENCE.md) for command execution and evidence collection.

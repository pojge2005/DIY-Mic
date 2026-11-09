# ESP32-S3 Known Issues and Open Questions

## Hardware identity

- ESP32-S3 QFN56 silicon revision v0.2 is reported.
- 16 MB flash, 8 MB embedded PSRAM (AP_3v3), and 40 MHz crystal are reported.
- Exact carrier-board manufacturer, product name, and PCB revision are unknown.
- PlatformIO N8/N8R2 candidates must not be assumed to match the N16R8 target.

## GPIO and microphone

- GPIO4=BCLK, GPIO5=WS/LRCLK, GPIO6=SD/DOUT is provisional.
- Physical board pinout has not been checked.
- INMP441 supply voltage at the module, breakout decoupling, L/R selection, and final wiring need physical confirmation.
- The 2026-11-09 I²S diagnostic initialized the driver but observed intermittent zero-data windows and intermittent non-zero words.
- Even/odd slot statistics alternated between active and zero-data periods; slot-to-channel mapping is not confirmed.
- Several raw words had non-zero least-significant bytes, so the assumed 24-bit left-aligned format and `raw >> 8` conversion are not verified.
- Repeated values near signed 24-bit extrema triggered clipping warnings; actual microphone clipping versus invalid data interpretation is unresolved.
- Stable, clean PCM audio and a controlled quiet-versus-speech response have not been demonstrated.
- See [INMP441 I²S Diagnostic Report](I2S_TEST_REPORT.md) and [supplied serial log](../../commands/logs/2026-11-09_esp32-s3_inmp441-i2s-diagnostic.log).

## BLE

- Control write and PING/PONG are not confirmed.
- Status notification capability must be read from live GATT properties.
- Audio subscription and payload delivery are not confirmed.
- Audio-start command is not recorded; do not guess one.
- Audio format, MTU, throughput, latency, packet loss, and power are unmeasured.
- Android and PC audio playback are not established.

See [ESP32-S3 Command Guide](../../commands/ESP32-S3.md), [Command Reference](COMMAND_REFERENCE.md), and [terminal log archive](../../commands/logs/README.md) for command execution and evidence collection.

# Roadmap

The roadmap tracks prototype milestones. Completion is based on recorded tests, not assumptions.

| Version | Focus | Status |
|---|---|---|
| V0.1 | Initial microphone test | Historical |
| V0.2 | Signal diagnostics | Historical |
| V0.3 | Raw I²S diagnostics | Historical |
| V0.4 | Channel and sample investigation | Historical |
| V0.5 | Live Android Wi-Fi audio prototype on ESP8266 | Owner-reported working |
| V0.6 | Noise and audio-quality diagnosis | Next |
| V0.7 | Stream reliability, jitter, and latency | Planned |
| V0.8 | Ubuntu receiver and PipeWire virtual microphone | Planned |
| V0.9 | Range and power optimization | Planned |
| V1.0 | Complete ESP8266 Wi-Fi microphone prototype | Planned |
| V1.1 | ESP32-C3 Mini hardware evaluation and I²S port | Future |
| V1.2 | ESP32-C3 Wi-Fi streaming and receiver validation | Future |
| V2.0 | Stable dual-platform firmware architecture and documented hardware | Future |

## V0.6 — Audio Quality

- Run a quiet-room noise test.
- Compare power sources.
- Record the noise character and severity.
- Verify channel selection and PCM sample extraction.

## V0.7 — Stream Reliability

- Add packet sequence tracking.
- Detect missing or out-of-order packets.
- Evaluate receiver buffering.
- Measure end-to-end latency.
- Run a 10-minute continuous stream test.

## V0.8 — Ubuntu Receiver

- Implement a Linux receiver for the Wi-Fi stream.
- Validate audio playback on Ubuntu.
- Integrate a PipeWire virtual microphone.
- Test compatibility with common desktop communication applications.

## V0.9 — Range and Power

- Measure stable range under repeatable conditions.
- Record current consumption.
- Evaluate power-source and battery options.
- Optimize Wi-Fi and audio settings based on measurements.

## V1.0 — ESP8266 Prototype Completion

- Consolidate verified ESP8266 firmware and receiver code.
- Document reproducible wiring and setup.
- Record measured audio, range, latency, and power results.
- Prepare final assembly documentation.

## V1.1 — ESP32-C3 Mini Evaluation

- Select and document the exact ESP32-C3 Mini board.
- Verify its pinout, power design, and I²S GPIO assignments.
- Capture INMP441 samples using the supported ESP32-C3 I²S driver.
- Validate channel selection, sample alignment, and sample rate.

## V1.2 — ESP32-C3 Streaming Port

- Port Wi-Fi access point and WebSocket transport.
- Reuse the documented PCM frame format where practical.
- Verify Android playback.
- Compare noise, latency, stability, range, and current consumption against ESP8266.

## V2.0 — Platform Consolidation

- Select the preferred hardware based on measured results.
- Keep platform-specific I²S and networking code separate from shared audio-format logic.
- Publish reproducible firmware, receiver, wiring, and test instructions.

## Scope Notes

- ESP8266 remains the current working prototype platform.
- ESP32-C3 Mini is a future target; no migration is complete yet.
- ESP32-C3 has an I²S peripheral, but ESP8266 low-level I²S code is not directly portable.
- ESP8266 does not provide Bluetooth. ESP32-C3 provides BLE capability, but the current audio transport remains Wi-Fi unless a separate transport design is validated.

See [System Architecture](ARCHITECTURE.md) and [ESP32-C3 Migration Plan](ESP32-C3-MIGRATION.md).

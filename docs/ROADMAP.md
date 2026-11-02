# Roadmap

The roadmap tracks prototype milestones. Completion should be based on recorded tests rather than assumptions.

| Version | Focus | Status |
|---|---|---|
| V0.1 | Initial microphone test | Historical |
| V0.2 | Signal diagnostics | Historical |
| V0.3 | Raw I²S diagnostics | Historical |
| V0.4 | Channel and sample investigation | Historical |
| V0.5 | Live Android Wi-Fi audio prototype | Owner-reported working |
| V0.6 | Noise and audio-quality diagnosis | Next |
| V0.7 | Stream reliability, jitter, and latency | Planned |
| V0.8 | Ubuntu receiver and PipeWire virtual microphone | Planned |
| V0.9 | Range and power optimization | Planned |
| V1.0 | Complete Wi-Fi microphone prototype | Planned |

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

## V1.0 — Prototype Completion

- Consolidate verified firmware and receiver code.
- Document reproducible wiring and setup.
- Record measured audio, range, latency, and power results.
- Prepare final assembly documentation.

## Scope Note

The current NodeMCU ESP8266 design uses Wi-Fi. ESP8266 does not provide Bluetooth support, so a Bluetooth receiver would require different hardware.

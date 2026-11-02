# Roadmap

This roadmap describes the intended development of DIY-Mic. Status is updated as implementation and testing are completed.

| Version | Milestone | Platform / focus | Status |
|---|---|---|---|
| V0.1 | Initial microphone test | ESP8266 + INMP441 | Historical |
| V0.2 | Signal diagnostics | ESP8266 | Historical |
| V0.3 | Raw I²S diagnostics | ESP8266 | Historical |
| V0.4 | Channel and sample investigation | ESP8266 | Historical |
| V0.5 | Live Android Wi-Fi audio | ESP8266 + webpage + WebSocket | Owner-reported working |
| V0.6 | Noise and audio-quality diagnosis | ESP8266 | Next |
| V0.7 | Buffering, packet handling and latency | ESP8266 | Planned |
| V0.8 | Ubuntu Wi-Fi receiver and PipeWire virtual microphone | Linux receiver | Planned |
| V0.9 | Range, current and battery measurements | ESP8266 | Planned |
| V1.0 | Documented ESP8266 reference prototype | ESP8266 | Planned |
| V1.1 | I²S and power bring-up | ESP32-C3 Super Mini | Future |
| V1.2 | Zero-PCB/perfboard microphone assembly | ESP32-C3 Super Mini + INMP441 | Future |
| V1.3 | Wi-Fi audio port and Android/PC validation | ESP32-C3 | Future |
| V1.4 | Windows receiver feasibility | Windows software | Future |
| V1.5 | USB receiver dongle proof of concept | ESP32-S3 or suitable USB-capable hardware | Future |
| V1.6 | BLE and dedicated low-power audio evaluation | Wireless comparison | Future |
| V1.7 | Power, battery and enclosure prototype | Selected platform | Future |
| V2.0 | Compact DIY-Mic build documentation and release | Validated transmitter + receiver options | Future |

## V0.6 — Audio Quality

- Record quiet-room noise with no speech.
- Compare clean USB power sources.
- Record whether the noise is hiss, hum, buzz, or crackle.
- Verify I²S channel selection and PCM sample extraction.

## V0.7 — Stream Reliability and Common Protocol

- Recover and preserve the exact working firmware and receiver webpage.
- Document the actual PCM format, sample rate, byte order, packet size, and WebSocket framing.
- Add packet sequence tracking.
- Detect missing, duplicate, or out-of-order frames.
- Evaluate receiver buffering.
- Measure end-to-end latency.
- Run a 30-minute continuous stream test.

## V0.8 — Ubuntu Wi-Fi Receiver

- Implement a Linux receiver for the existing Wi-Fi audio stream.
- Validate desktop playback.
- Integrate a PipeWire virtual microphone.
- Test with desktop communication and recording applications.
- Keep speaker playback available independently of virtual microphone integration.

## V0.9–V1.0 — ESP8266 Reference

- Measure range at controlled distances, including the 10–20 m product target.
- Test line-of-sight and indoor obstacle conditions.
- Measure current consumption during idle and streaming.
- Record battery-runtime estimates from measured operating current.
- Consolidate verified firmware and receiver source.
- Document reproducible wiring and setup.

## V1.1–V1.3 — ESP32-C3 Super Mini

- Identify exact board revision and pinout.
- Verify power and INMP441 wiring.
- Bring up I²S capture and PCM format.
- Assemble on zero PCB/perfboard.
- Port Wi-Fi AP and WebSocket streaming.
- Repeat Android playback, PC playback, and reliability tests.
- Keep the ESP8266 reference available until the ESP32-C3 passes the same tests.

## V1.4 — Windows Receiver Feasibility

- Reuse the documented common audio protocol.
- Implement desktop playback.
- Evaluate a virtual audio input path.
- Document installation, permissions, firewall, and reconnection behaviour.
- Do not claim system microphone support until tested with real applications.

## V1.5 — USB Receiver Dongle Proof of Concept

- Evaluate ESP32-S3 and other suitable USB device-capable hardware.
- Verify USB Audio Class enumeration.
- Receive the wireless audio stream and present it to the PC as a USB microphone.
- Test host compatibility, latency, buffering, and reliability.
- Keep this as an optional receiver path until the hardware and software are validated.

## V1.6 — Wireless Comparison

- Test BLE for setup and control.
- Investigate whether custom BLE data transport can meet audio throughput and latency needs.
- Evaluate dedicated low-power audio modules and their matched receivers.
- Compare quality, latency, range, current, cost, size, and receiver usability.
- Select a transport based on measurements.

**Platform note:** ESP32-C3 supports Bluetooth LE, not Bluetooth Classic. BLE is not automatically compatible with standard Bluetooth audio profiles.

## V1.7–V2.0 — Power and Compact Product

- Evaluate USB-powered, built-in rechargeable, and replaceable battery arrangements.
- Select battery, regulator, charging and protection components from measured requirements.
- Optimize microphone and antenna placement.
- Build a small enclosure.
- Consider a custom PCB after zero-PCB validation.
- Publish source, wiring, BOM, build instructions, and test results.

## Receiver Architecture Reference

See [Receiver Options and Architecture](RECEIVER-OPTIONS-AND-ARCHITECTURE.md) for the browser receiver, native Wi-Fi PC receiver, USB dongle options, audio decoding possibilities, proposed repository structure, and acceptance criteria.

## Completion Policy

A milestone is complete only when the relevant source, measurements, and test evidence are recorded. Planned or experimental features must not be described as working.

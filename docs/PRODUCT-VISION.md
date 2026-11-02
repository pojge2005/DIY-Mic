# DIY-Mic Product Vision

## Goal

Build a tiny, practical DIY wireless microphone that can be assembled from accessible components, tested on a simple prototype board, and improved through measured engineering iterations.

The project begins as a working wireless audio experiment and gradually becomes a compact microphone system with documented hardware, firmware, receiver, and power design.

## Product Direction

- Small physical size.
- Clear and stable voice capture.
- Low and predictable audio latency.
- Useful operating range for the intended use.
- Practical battery life.
- Affordable, available components.
- Simple setup and receiver experience.
- Reproducible DIY assembly instructions.

These are design goals, not verified product specifications.

## Development Strategy

### Phase 1 — Working Wi-Fi Prototype

Current platform: NodeMCU ESP8266 + INMP441.

The ESP8266 hosts a Wi-Fi access point. A phone connects to it, opens the local webpage at `http://192.168.4.1`, and receives live PCM audio through WebSocket for browser playback.

Status: owner-reported live Android playback working at V0.5.

### Phase 2 — Small ESP32-C3 Prototype

Target platform: ESP32-C3 Super Mini + INMP441.

Build the first compact circuit on zero PCB/perfboard. Validate power, I²S, sample format, Wi-Fi streaming, sound quality, and stability. Keep the working ESP8266 prototype as a reference until the new build passes the same tests.

### Phase 3 — Wireless Technology Evaluation

Compare:
- Wi-Fi streaming for flexible phone and PC network receivers.
- BLE for setup, control, and a measured custom audio-data experiment.
- Dedicated low-power audio transmitter/receiver modules.
- Other Bluetooth audio-capable platforms if standard headset compatibility is required.

ESP32-C3 supports Bluetooth LE, not Bluetooth Classic. A standard Bluetooth audio experience may require different hardware and a different receiver design.

### Phase 4 — Power and Miniaturization

Measure current in real listening/streaming operation. Select the battery, regulator, charging/protection circuit, microphone placement, antenna, and enclosure only after power and RF testing.

Start with zero PCB/perfboard. Move to a custom PCB only when the circuit is stable and component placement can be justified.

### Phase 5 — Complete DIY-Mic Build

Publish:
- Verified firmware source and build instructions.
- Receiver source and setup instructions.
- Wiring diagram and bill of materials.
- Power and battery design.
- Assembly and enclosure guidance.
- Audio, latency, range, and runtime test results.
- Known limitations and revision history.

## Engineering Decision Rules

Choose the wireless transport based on measured audio quality, latency, range, power consumption, receiver compatibility, cost, and complexity. Do not select BLE or another module merely because it is described as low power.

Keep current implementation, experiments, and future ideas clearly separated in the repository. Update the documentation after each meaningful build or test session.

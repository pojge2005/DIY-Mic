# DIY-Mic

A DIY wireless microphone prototype using an INMP441 I²S MEMS microphone and a Wi-Fi-enabled microcontroller.

**Current hardware:** NodeMCU ESP8266  
**Future hardware target:** ESP32-C3 Mini  
**Current milestone:** V0.5 — Android live playback reported working by the project owner.

## Current Prototype

```text
INMP441 -> ESP8266 I²S -> PCM audio
        -> Wi-Fi access point + WebSocket
        -> Android browser -> speaker/headphones
```

Connect the Android phone to the ESP8266 access point and open `http://192.168.4.1`. The browser receives audio over WebSocket on port 81 and plays it through the Web Audio API.

## Architecture

See [System Architecture](docs/ARCHITECTURE.md) for data-flow diagrams and the current receiver design.

## Hardware

- NodeMCU ESP8266
- INMP441 I²S MEMS microphone

See [Hardware and Wiring](docs/HARDWARE.md).

## Current Test Snapshot

| Parameter | Owner-reported result |
|---|---|
| Voice clarity | Clear |
| Background noise | Medium |
| Delay | Low (subjective, not measured) |
| Stability | Stable |
| Distance | 2 m tested |

These are prototype observations, not laboratory measurements. See [Test Results](docs/TEST_RESULTS.md).

## Future Development

The next hardware platform under consideration is ESP32-C3 Mini. The migration plan covers I²S capture, PCM format validation, Wi-Fi/WebSocket porting, receiver compatibility, and comparative testing.

See [ESP32-C3 Migration Plan](docs/ESP32-C3-MIGRATION.md).

## Documentation

- [Hardware and Wiring](docs/HARDWARE.md)
- [System Architecture](docs/ARCHITECTURE.md)
- [Project Status](docs/PROJECT_STATUS.md)
- [Experiment Log](docs/EXPERIMENT_LOG.md)
- [Test Results](docs/TEST_RESULTS.md)
- [Roadmap](docs/ROADMAP.md)
- [ESP32-C3 Migration Plan](docs/ESP32-C3-MIGRATION.md)

## Source Code Status

The repository documentation is published. The exact V0.5 firmware and Android receiver source have not yet been added because the working source files were not present in the repository or available in the prior shared project material. The repository will distinguish tested firmware from diagnostic examples and experimental code.

## Current Limitations

- Background noise requires diagnosis.
- Latency, packet loss, jitter, SNR, power consumption, and maximum range have not been measured.
- Ubuntu/PipeWire receiver support is not yet validated.
- ESP8266 firmware is not directly portable to ESP32-C3.

## License

See [LICENSE](LICENSE).

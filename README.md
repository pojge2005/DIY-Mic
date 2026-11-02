# DIY-Mic

A DIY wireless microphone prototype built with an ESP8266 NodeMCU and an INMP441 I²S MEMS microphone. The current prototype streams live audio over Wi-Fi to an Android browser.

## Current Prototype

**Status:** V0.5 — live Android audio playback reported working by the project owner.

### Hardware

- NodeMCU ESP8266
- INMP441 I²S MEMS microphone

### Architecture

```text
INMP441 -> ESP8266 I²S -> PCM audio
        -> ESP8266 Wi-Fi access point + WebSocket
        -> Android browser -> phone speaker/headphones
```

The ESP8266 hosts its own Wi-Fi access point. Connect the Android phone to that network and open:

```text
http://192.168.4.1
```

The webpage receives PCM audio over WebSocket (port 81) and plays it through the browser's Web Audio API.

## Current Test Snapshot

| Parameter | Owner-reported result |
|---|---|
| Voice clarity | Clear |
| Background noise | Medium |
| Delay | Low (subjective; not instrument-measured) |
| Stability | Stable |
| Distance | 2 m tested |

These are prototype observations, not laboratory measurements. See [test results](docs/TEST_RESULTS.md) for limitations and next tests.

## Documentation

- [Hardware and wiring](docs/HARDWARE.md)
- [Project status](docs/PROJECT_STATUS.md)
- [Experiment log](docs/EXPERIMENT_LOG.md)
- [Test results](docs/TEST_RESULTS.md)
- [Roadmap](docs/ROADMAP.md)

## Current Limitations

- Background noise requires further diagnosis.
- Latency, packet loss, jitter, SNR, power consumption, and maximum range have not been measured.
- Ubuntu/PipeWire virtual microphone support is not yet validated.
- ESP8266 provides Wi-Fi, not Bluetooth.

## Development Environment

The prototype was developed using PlatformIO on Ubuntu. The project notes record ESP8266 Arduino core 3.1.2 and the NodeMCU v2 PlatformIO board configuration.

Firmware source and build verification are maintained separately; the documentation does not claim that unverified code has been compiled or tested.

## License

See [LICENSE](LICENSE).

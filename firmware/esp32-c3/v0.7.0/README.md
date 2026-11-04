# DIY-Mic V0.7.0 — Wi-Fi Audio Streaming Baseline

**Status:** Documentation baseline; no firmware implementation included  
**Target board:** ESP32-C3 Super Mini (4 MB flash recorded; verify exact board)  
**Microphone:** INMP441 I²S MEMS breakout  
**Primary link:** ESP32-C3 Wi-Fi SoftAP + WebSocket  
**Receiver:** Android/browser and Ubuntu/PC browser  
**Optional future link:** BLE for control/discovery only, if needed

## Purpose

V0.7.0 defines the product requirements, hardware baseline, system architecture, WebSocket audio protocol, receiver behavior, development roadmap and verification criteria before firmware coding begins.

The main use case is live wireless microphone audio streamed from the ESP32-C3 to a phone or computer over a direct local Wi-Fi connection. The ESP32-C3 runs a Wi-Fi access point; the receiver joins that network and connects to the audio WebSocket endpoint. An internet connection or external router is not required for the local audio path.

Live audio playback is the confirmed core receiver function. Waveform, spectrum/FFT and additional visual meters remain optional receiver enhancements until explicitly approved.

## Status labels

- **Confirmed:** Explicitly stated by the user or recorded as the selected project direction.
- **Proposed:** Engineering starting point; requires validation.
- **Unverified:** Must be checked on the physical board or measured.
- **Optional:** Not a release requirement unless separately approved.

## Documents

| File | Purpose |
|---|---|
| [Product requirements](docs/PRODUCT_REQUIREMENTS.md) | Core user experience and priorities |
| [System architecture](docs/SYSTEM_ARCHITECTURE.md) | ESP32-C3, SoftAP, WebSocket and receiver |
| [Audio pipeline](docs/AUDIO_PIPELINE.md) | I²S capture, PCM and buffering |
| [Wi-Fi/WebSocket protocol](docs/WIFI_WEBSOCKET_PROTOCOL.md) | Audio frame and control protocol proposal |
| [Web receiver](docs/WEB_RECEIVER.md) | Browser connection and live playback |
| [Firmware architecture](docs/FIRMWARE_ARCHITECTURE.md) | Proposed source modules |
| [Roadmap](docs/ROADMAP.md) | Phases and exit criteria |
| [Test plan](docs/TEST_PLAN.md) | Bring-up, throughput, latency and reliability |
| [Architecture decisions](docs/DECISIONS.md) | Decisions and rationale |
| [Open items](docs/OPEN_ITEMS.md) | Questions to close before implementation |
| [Board configuration](hardware/BOARD_CONFIGURATION.md) | MCU and pin baseline |
| [Wiring and BOM](hardware/WIRING_AND_BOM.md) | INMP441 wiring and minimum parts |
| [PlatformIO baseline](development/PLATFORMIO_BASELINE.md) | Toolchain checks |
| [Coding rules](AGENTS.md) | Firmware implementation standards |

## Existing project references

The repository-level documents remain the historical project record:
- `docs/PRODUCT-VISION.md`
- `docs/HARDWARE.md`
- `docs/ESP32-C3-MINI-CIRCUIT.md`
- `docs/ESP32-C3-MIGRATION.md`
- `docs/RECEIVER-OPTIONS-AND-ARCHITECTURE.md`
- `docs/TEST_RESULTS.md`
- `docs/EXPERIMENT_LOG.md`

The BLE draft is retained as an optional future reference only. It is not the V0.7.0 primary transport.

## Non-goals for this commit

- No `platformio.ini` implementation.
- No C/C++ firmware source.
- No receiver application source.
- No claim that streaming throughput, latency or range has passed testing.
- No battery/charger design.
- No changes to V0.5 or V0.6 source.
- No mandatory waveform/FFT dashboard requirement yet.

## Entry condition for coding

Review [OPEN_ITEMS.md](docs/OPEN_ITEMS.md), verify the physical wiring and target receiver, then approve the protocol and test plan. Only then create the clean PlatformIO project.
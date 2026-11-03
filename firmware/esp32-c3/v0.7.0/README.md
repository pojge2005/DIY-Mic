# DIY-Mic V0.7.0 — Bluetooth-First Architecture Baseline

**Status:** Documentation baseline; no firmware implementation included  
**Target board:** ESP32-C3 Super Mini  
**Microphone:** INMP441 I²S MEMS  
**Primary link:** Bluetooth Low Energy (BLE)  
**Receiver:** Browser-based dashboard with live listening and visualization  
**Optional link:** Local Wi-Fi, not internet-dependent

## Purpose

V0.7.0 establishes the engineering requirements, hardware baseline, system architecture, protocol proposal, development plan, and verification criteria before firmware coding begins.

The required user experience is both:
1. Live microphone listening on a connected phone or laptop.
2. A web dashboard showing waveform, frequency spectrum, RMS/peak levels, and connection/stream diagnostics.

The ESP32-C3 supports BLE, not Bluetooth Classic. This project will use a custom BLE GATT data service; it will not claim A2DP, Bluetooth Classic headset, or Bluetooth LE Audio compatibility.

## Important status labels

- **Confirmed:** Explicitly selected or recorded in project history.
- **Proposed:** Engineering starting point; requires validation.
- **Unverified:** Must be checked on the physical board or measured.
- **Deferred:** Deliberately excluded from the first implementation.

## Documents

| File | Purpose |
|---|---|
| [Product requirements](docs/PRODUCT_REQUIREMENTS.md) | User experience and measurable requirements |
| [System architecture](docs/SYSTEM_ARCHITECTURE.md) | Device, BLE, receiver and optional Wi-Fi boundaries |
| [Audio pipeline](docs/AUDIO_PIPELINE.md) | I²S capture, PCM, buffering, playback and FFT |
| [BLE protocol draft](docs/BLE_PROTOCOL_DRAFT.md) | GATT services, packet framing and telemetry |
| [Web receiver](docs/WEB_RECEIVER.md) | Browser compatibility, Web Bluetooth and Web Audio |
| [Firmware architecture](docs/FIRMWARE_ARCHITECTURE.md) | Proposed modules and coding boundaries |
| [Roadmap](docs/ROADMAP.md) | Phases and exit criteria |
| [Test plan](docs/TEST_PLAN.md) | Bring-up, throughput, latency, quality and reliability |
| [Architecture decisions](docs/DECISIONS.md) | Decisions and rationale |
| [Open items](docs/OPEN_ITEMS.md) | Questions that must be closed before implementation |
| [Board configuration](hardware/BOARD_CONFIGURATION.md) | MCU and development baseline |
| [Wiring and BOM](hardware/WIRING_AND_BOM.md) | Microphone wiring and minimum parts |
| [PlatformIO baseline](development/PLATFORMIO_BASELINE.md) | Toolchain notes and pre-coding checks |
| [Coding rules](AGENTS.md) | Implementation standards for later firmware work |

## Existing project references

The repository-level documents remain the historical project record:
- `docs/PRODUCT-VISION.md`
- `docs/HARDWARE.md`
- `docs/ESP32-C3-MINI-CIRCUIT.md`
- `docs/ESP32-C3-MIGRATION.md`
- `docs/RECEIVER-OPTIONS-AND-ARCHITECTURE.md`
- `docs/TEST_RESULTS.md`
- `docs/EXPERIMENT_LOG.md`

Some existing documents describe Wi-Fi as the first ESP32-C3 transport. That was the earlier exploration direction. The current V0.7.0 requirement supersedes that transport priority: BLE is primary; Wi-Fi is optional. The older documents are not silently rewritten by this version baseline.

## Non-goals for this commit

- No `platformio.ini` project implementation.
- No C/C++ source or BLE firmware.
- No browser application source.
- No claim that BLE live audio has passed a throughput or latency test.
- No battery/charger circuit design.
- No changes to ESP8266 V0.5 or ESP32-C3 V0.6 source.

## Entry condition for coding

Do not begin implementation until the open items in [OPEN_ITEMS.md](docs/OPEN_ITEMS.md) are reviewed, the exact board and microphone breakout are confirmed, and the staged test plan is accepted.

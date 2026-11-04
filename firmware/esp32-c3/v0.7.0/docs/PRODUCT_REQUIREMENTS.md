# Product Requirements — DIY-Mic V0.7.0

## Product objective

Build a compact wireless microphone around the ESP32-C3 Super Mini and INMP441. The ESP32-C3 creates a local Wi-Fi access point. A phone or computer joins that network and receives live audio through a WebSocket connection.

The audio path must work without an external Wi-Fi router or internet connection.

## User-facing requirements

| ID | Requirement | Priority |
|---|---|---|
| PR-01 | ESP32-C3 provides a local Wi-Fi access point | Must |
| PR-02 | Receiver joins the microphone's local Wi-Fi network | Must |
| PR-03 | Live microphone audio streams over WebSocket | Must |
| PR-04 | Receiver plays incoming audio through the phone/PC output | Must |
| PR-05 | Start, stop and connection status are available | Must |
| PR-06 | Reconnect and clear error reporting are supported | Must |
| PR-07 | Android/browser receiver is supported as an initial target | Initial target |
| PR-08 | Ubuntu/PC browser receiver is supported as an initial target | Initial target |
| PR-09 | Internet access is not required for local streaming | Must |
| PR-10 | Waveform and spectrum/FFT visualization | Optional; not confirmed |
| PR-11 | RMS/peak meters and additional diagnostics | Optional enhancement |
| PR-12 | BLE discovery/control | Deferred; not primary transport |

## Initial engineering targets (proposed, not achieved specifications)

- Mono speech audio.
- 16 kHz, signed 16-bit PCM as the first transport benchmark.
- 10 ms logical audio frames as a starting point.
- Measure end-to-end latency and set acceptance threshold after first end-to-end tests.
- Initial continuous-stream test: 30 minutes.
- Initial range tests at 2, 5, 10, 15 and 20 metres, recording line-of-sight and indoor-obstacle conditions.

The audio format and timing values are engineering starting points. They must be validated against measured audio quality, throughput, memory use and latency.

## Explicit exclusions for initial baseline

- Bluetooth Classic / A2DP.
- BLE audio streaming as primary transport.
- Cloud streaming or account login.
- Multi-microphone and stereo capture.
- Battery-powered operation during first bring-up.
- OLED, buttons and non-audio sensors in the first hardware revision.
- Guaranteed system-microphone integration on every OS.

## Acceptance principle

The first functional milestone is reliable local Wi-Fi audio playback on a target receiver. Visualizations are optional and must not delay the core streaming path.
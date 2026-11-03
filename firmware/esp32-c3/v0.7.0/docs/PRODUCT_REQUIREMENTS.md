# Product Requirements — DIY-Mic V0.7.0

## Product objective

Build a compact wireless microphone around ESP32-C3 Super Mini and INMP441. A phone or laptop connects directly to the microphone over Bluetooth LE. A browser-based receiver provides live listening and audio visualization.

The system must not depend on an internet connection or an external Wi-Fi router for normal operation.

## User-facing requirements

| ID | Requirement | Priority |
|---|---|---|
| PR-01 | Connect to the microphone directly using BLE | Must |
| PR-02 | Play live microphone audio through the receiver device's normal audio output | Must |
| PR-03 | Display a live waveform | Must |
| PR-04 | Display a frequency spectrum using FFT | Must |
| PR-05 | Display RMS and peak signal levels | Must |
| PR-06 | Display BLE connection and audio-stream status | Must |
| PR-07 | Provide connect, disconnect, start, stop and mute controls | Must |
| PR-08 | Work without internet after the receiver page is loaded | Must |
| PR-09 | Support Android Chrome as the first mobile target | Initial target |
| PR-10 | Support Chromium-based browser on Ubuntu desktop | Initial target |
| PR-11 | Keep optional local Wi-Fi mode available for later evaluation | Should |
| PR-12 | Provide reconnect and clear error reporting | Must |

## Initial engineering targets (not achieved specifications)

- Mono speech audio.
- 16 kHz, signed 16-bit PCM as the first BLE throughput benchmark.
- 10 ms logical audio frames as a starting point.
- Target end-to-end latency below 100 ms, subject to measurement and user acceptance.
- Initial continuous-stream test: 30 minutes.
- Initial range test points: 2, 5, 10, 15 and 20 metres, recording line-of-sight and indoor-obstacle conditions.

These values are proposed test targets. They are not verified V0.7.0 capabilities.

## Explicit exclusions

- Bluetooth Classic / A2DP.
- Bluetooth LE Audio / LC3.
- Cloud streaming or internet account.
- Multi-microphone support.
- Stereo capture.
- Battery-powered operation in the first bring-up.
- OLED, buttons, sensors or other non-audio peripherals in the first hardware revision.
- Plug-and-play system microphone integration on every operating system.

## Acceptance principle

Live listening and visualization are both required. A telemetry-only BLE prototype is an intermediate test, not a completed V0.7.0 product experience.

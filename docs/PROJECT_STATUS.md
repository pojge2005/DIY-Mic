# Project Status

## Current Milestone: V0.5

The project has reached a working live-audio prototype according to the owner's Android test.

### Current Architecture

```text
INMP441 microphone
    -> ESP8266 I²S input
    -> PCM sample stream
    -> ESP8266 Wi-Fi access point
    -> WebSocket server (port 81)
    -> Android browser Web Audio API
    -> phone speaker or headphones
```

The ESP8266 serves the receiver webpage over HTTP at `192.168.4.1`. The phone connects directly to the ESP8266 access point; an external router or internet connection is not required.

### Owner-Reported Test Results

- Voice clarity: clear
- Background noise: medium
- Delay: low (subjective)
- Stability: stable
- Distance: 2 m

These results are observations from a prototype test. They have not yet been supported by instrumented latency, packet-loss, or noise measurements.

### Repository Tooling Added

- VS Code extension recommendations for PlatformIO and Python.
- Ubuntu / VS Code / PlatformIO setup and command guide.
- Minimal ESP8266 PlatformIO serial bring-up project.
- Python raw PCM inspection utility.
- Python unit tests for PCM decoding and basic signal metrics.

The host-side Python unit tests have been run successfully. The ESP8266 serial bring-up firmware has not yet been built or tested on physical hardware as part of this repository update.

## 2026-11-04 Hardware Bring-up — ESP32-C3 Closed

The ESP32-C3 Super Mini workstream is closed for the current iteration and preserved as an archive. Serial-only diagnostics passed during the captured test window. The INMP441 I²S diagnostic produced sample data near the configured 16 kHz rate, but sample alignment and acoustic quality were not fully validated.

The Wi-Fi SoftAP diagnostic compiled and uploaded successfully. Runtime status reported AP mode and 192.168.4.1, but repeated Ubuntu scans did not detect the configured SSID. No client joined, so HTTP connectivity and WebSocket audio streaming were not verified. The cause of the SSID discovery failure was not isolated; this is a failed acceptance result, not a confirmed silicon defect.

See [ESP32-C3 session report](ESP32-C3-SESSION-2026-11-04.md), [C3 archive](../firmware/esp32-c3/ARCHIVE.md), and the raw console logs under ../../logs/2026-11-04/.

## Next Hardware Target — ESP32-S3

The project owner selected the ESP32-S3 family as the next development target. The exact board/module, flash capacity, PSRAM configuration, USB routing, board ID, and GPIO mapping have not yet been recorded. Identify the physical board before creating its PlatformIO configuration or wiring the INMP441.

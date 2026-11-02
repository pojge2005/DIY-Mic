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

### Known Engineering Gaps

- Import and review the exact owner-tested V0.5 firmware and webpage source.
- Identify and reduce the source of background noise.
- Verify sample alignment, channel selection, and effective sample rate.
- Measure end-to-end latency and stream continuity.
- Test sustained operation.
- Develop and validate an Ubuntu receiver and PipeWire virtual microphone.
- Measure range and power consumption.

### Firmware Verification Status

The architecture and implementation approach are documented, but the repository does not yet contain the verified V0.5 streaming firmware. The serial bring-up project is a separate toolchain smoke test and must not be confused with the live microphone implementation.

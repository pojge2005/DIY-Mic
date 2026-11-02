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

### Known Engineering Gaps

- Identify and reduce the source of background noise.
- Verify sample alignment, channel selection, and effective sample rate.
- Measure end-to-end latency and stream continuity.
- Test sustained operation.
- Develop and validate an Ubuntu receiver and PipeWire virtual microphone.
- Measure range and power consumption.

### Firmware Verification Status

The architecture and implementation approach are documented, but the documentation package does not establish a verified firmware build. Compile and hardware-test results should be recorded when available.

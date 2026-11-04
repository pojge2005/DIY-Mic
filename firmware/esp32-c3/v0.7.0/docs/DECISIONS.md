# Architecture Decision Records

## ADR-001 — Wi-Fi SoftAP is the primary connection

**Status:** Accepted project direction.

**Decision:** ESP32-C3 starts a local Wi-Fi access point. Phone/PC receivers join it and receive audio through WebSocket.

**Reason:** This is the recorded V0.7 direction for wireless audio streaming and browser/PC receiver access without an external router or internet connection.

**Consequence:** WebSocket/TCP buffering, SoftAP behavior, phone network switching and sustained audio throughput must be tested on actual target devices.

## ADR-002 — Live audio playback is the core receiver feature

**Status:** Accepted.

**Decision:** Receiver must play incoming microphone audio.

**Consequence:** Audio buffering and playback are the first receiver implementation goals.

## ADR-003 — Visualization is optional

**Status:** Not confirmed as a requirement.

**Decision:** Waveform, FFT/spectrum and RMS/peak displays are optional enhancements, not mandatory V0.7.0 acceptance criteria.

**Consequence:** Do not delay core streaming to implement visualizations.

## ADR-004 — Browser/PC receiver targets

**Status:** Initial targets recorded; exact browser versions remain open.

**Decision:** Android/browser and Ubuntu/PC browser are initial receiver targets.

**Consequence:** Test actual device/browser compatibility and local network behavior.

## ADR-005 — Start with uncompressed PCM

**Status:** Proposed baseline.

**Decision:** First benchmark mono 16 kHz signed 16-bit PCM using 10 ms logical frames.

**Reason:** Simple to inspect and debug; raw payload is 256 kbit/s.

**Consequence:** Measure throughput, latency, memory use and audio quality before freezing the format.

## ADR-006 — Minimal hardware first

**Status:** Accepted.

**Decision:** ESP32-C3 Super Mini + INMP441, USB powered during bring-up. No display, buttons, sensors or battery system in the first hardware revision.

**Consequence:** Validate core capture and streaming before adding peripherals.

## ADR-007 — BLE is not the primary audio transport

**Status:** Deferred.

**Decision:** Do not build the first audio stream around BLE. Retain BLE only as a possible later discovery/control option if needed.
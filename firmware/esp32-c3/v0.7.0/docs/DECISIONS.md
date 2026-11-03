# Architecture Decision Records

## ADR-001 — BLE is the primary connection

**Status:** Accepted as the V0.7.0 product direction.

**Decision:** Use Bluetooth Low Energy as the normal connection between the ESP32-C3 microphone and receiver.

**Reason:** The user wants direct device-to-device operation that does not depend on internet or a router. BLE discovery/control and audio-data transport will be evaluated on the target devices.

**Consequence:** Custom GATT audio data transport must be benchmarked. This is not Bluetooth Classic, A2DP or LE Audio.

## ADR-002 — Both playback and visualization are required

**Status:** Accepted.

**Decision:** The receiver must play live audio and display waveform, frequency spectrum, RMS/peak and stream status concurrently.

**Consequence:** Audio playback and visualization require separate processing paths so UI/FFT work cannot block audio rendering.

## ADR-003 — Browser receiver is the initial receiver target

**Status:** Accepted for initial investigation.

**Decision:** Use Web Bluetooth and Web Audio APIs for Android Chrome and Chromium-based Ubuntu desktop as initial targets.

**Consequence:** Browser support must be checked at runtime. Safari and Firefox compatibility is not assumed. A native receiver may be needed for unsupported platforms.

## ADR-004 — Wi-Fi is optional, not primary

**Status:** Accepted.

**Decision:** Do not require Wi-Fi for normal operation. Preserve local Wi-Fi SoftAP as a possible fallback/high-bandwidth comparison.

**Reason:** The normal use case should remain direct and independent of external internet access. SoftAP itself does not require internet, but Wi-Fi is not the primary user-selected transport.

**Consequence:** Keep Wi-Fi disabled in the first BLE implementation. Evaluate coexistence and performance only in a later isolated test.

## ADR-005 — Start with uncompressed PCM

**Status:** Proposed baseline.

**Decision:** First benchmark mono 16 kHz, signed 16-bit PCM, using 10 ms logical frames.

**Reason:** Simple to inspect and debug. The payload rate is 256 kbit/s before overhead.

**Consequence:** Actual BLE throughput must be measured. If inadequate, evaluate IMA ADPCM before adopting a more complex codec.

## ADR-006 — Minimal hardware first

**Status:** Accepted.

**Decision:** ESP32-C3 Super Mini + INMP441 + verified local decoupling only. USB-powered during bring-up. No display, buttons, sensors or battery system in the first revision.

**Consequence:** Validate the core audio path before expanding hardware.

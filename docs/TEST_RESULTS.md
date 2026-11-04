# Test Results

## V0.5 — Android Live Audio Test

**Test date:** 2026-11-02  
**Platform:** Android browser connected to the ESP8266 access point

| Parameter | Owner-reported observation |
|---|---|
| Voice clarity | Clear |
| Background noise | Medium |
| Delay | Low |
| Stability | Stable |
| Distance | 2 m |

## Interpretation

The owner reports that the live audio path is functional on Android. Background noise is the main reported audio-quality issue.

The delay result is subjective; no end-to-end latency measurement has been recorded. The 2 m result is a tested distance, not a verified maximum range.

## Not Yet Measured

- Noise floor and signal-to-noise ratio (SNR)
- End-to-end latency in milliseconds
- Packet loss and jitter
- Maximum stable operating range
- Current consumption and battery runtime
- Long-duration reliability

## Recommended Follow-Up Tests

1. Quiet-room noise test: stream for 15 seconds without speaking.
2. Speech test: speak at approximately 20 cm from the microphone.
3. Power test: repeat using another clean USB power source.
4. Reliability test: stream continuously for 10 minutes.
5. Record audio observations and firmware version for each test.

Do not treat unmeasured values as verified specifications.


## 2026-11-04 — ESP32-C3 Bring-up

**Disposition:** C3 workstream closed and archived after Wi-Fi SoftAP discovery failed.

| Test | Result | Recorded evidence |
|---|---|---|
| Serial-only baseline | PASS (observed window) | 115200 baud; heartbeat 11–63 s; free heap 310,948 bytes |
| INMP441 I²S capture | Provisional | 16,000–16,016 Hz reported; RMS 413.7–8,226.0; peak up to 32,758; clipped count 0 in captured windows |
| Wi-Fi SoftAP build/upload | PASS | Build succeeded; upload hash verified |
| AP runtime API/status | Reported active | Wi-Fi mode 2; IP 192.168.4.1; heap about 229,092 bytes |
| Ubuntu SSID discovery | FAIL | Repeated scans did not list DIY-Mic-Setup |
| Client association | Not achieved | AP clients remained 0 |
| HTTP/health endpoint | Not verified | No client connection |
| WebSocket/audio stream | Not tested | Not implemented in this diagnostic |

The C3 SoftAP root cause was not isolated. Do not classify this as a confirmed silicon defect. Full measurements and command transcripts are in [the session report](ESP32-C3-SESSION-2026-11-04.md) and ../../logs/2026-11-04/.

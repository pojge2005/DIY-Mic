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

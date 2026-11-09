# Test Results

The project-wide [command library](../commands/README.md) documents how to run host tests and save terminal evidence. ESP32-S3 BLE results are tracked separately in [the BLE test report](../ESP32-S3/docs/BLE_TEST_REPORT.md).



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


## ESP32-S3 — INMP441 I²S diagnostic

**Test date:** 2026-11-09 (exact capture time not supplied)  
**Platform:** reported ESP32-S3 N16R8 + INMP441, Ubuntu serial monitor

| Check | Result |
|---|---|
| I²S driver initialization | PASS |
| Intermittent non-zero raw words | Observed |
| Stable capture | FAIL / NOT VERIFIED |
| Raw sample alignment | NOT VERIFIED |
| Clean PCM audio | NOT VERIFIED |
| Physical GPIO and supply validation | BLOCKED |

The supplied output showed intermittent zero-data windows, non-zero raw words with inconsistent low-byte patterns, and repeated clipping warnings after the candidate sample shift. The evidence does not establish whether the warnings are actual microphone clipping or an I²S data-format/electrical issue.

See [ESP32-S3 I²S Test Report](../ESP32-S3/docs/I2S_TEST_REPORT.md) and [supplied serial log](../commands/logs/2026-11-09_esp32-s3_inmp441-i2s-diagnostic.log). This result is separate from the historical ESP8266 V0.5 Android test.

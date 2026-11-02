# Experiment Log

This log records known development findings. Dates are retained where available; undocumented test details are not inferred.

## I²S Investigation

The installed ESP8266 Arduino core's I²S implementation was inspected, including:

- `core_esp8266_i2s.h`
- `core_esp8266_i2s.cpp`
- `libraries/I2S/src/I2S.h`
- `libraries/I2S/src/I2S.cpp`
- The ESP8266 `I2SInput` example

### Findings

- The low-level `i2s_set_bits(24)` call is used to configure 24-bit input before `i2s_rxtx_begin`.
- The installed `I2SClass::begin()` implementation does not itself call `i2s_set_bits(bitsPerSample)`.
- `i2s_read_sample(int16_t *left, int16_t *right, bool blocking)` returns the low and high 16-bit halves of a 32-bit DMA word.
- A 32-bit word can be reconstructed from the halves as:

```cpp
uint32_t raw = ((uint32_t)(uint16_t)high << 16) | (uint16_t)low;
```

- Observed microphone words appeared to have the lower 8 bits unused.
- Preliminary diagnostics showed one word in each pair mostly zero or near-zero, while the other varied. The active-word interpretation needs repeatable validation.
- The L/R pin is connected to GND for left-channel selection.

## V0.5 Live Streaming Test — 2026-11-02

The owner reported successful Android browser playback.

| Parameter | Result |
|---|---|
| Voice clarity | Clear |
| Background noise | Medium |
| Delay | Low |
| Stability | Stable |
| Distance | 2 m |

The delay rating is subjective and the 2 m result is the tested distance, not the maximum operating range.

## Next Controlled Experiment

1. Keep the microphone stationary in a quiet room.
2. Keep the phone at least 1 m away.
3. Stream for 15 seconds without speaking.
4. Record whether the background sound is hiss, hum, buzz, or crackle.
5. Repeat with a different clean USB power source.
6. Record the results before changing firmware.

A separate speech test at approximately 20 cm should be recorded for comparison.

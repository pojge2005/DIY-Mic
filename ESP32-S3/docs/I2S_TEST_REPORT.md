# INMP441 I²S Diagnostic Report — ESP32-S3

## Test metadata

- Test date: 2026-11-09 (exact capture time not supplied).
- Host: Ubuntu.
- Serial port: `/dev/ttyACM0`.
- Serial monitor: 115200 baud.
- Target: reported ESP32-S3 N16R8 + INMP441 breakout.
- Carrier-board manufacturer, model, and PCB revision: not identified.
- Firmware source revision: temporary diagnostic sketch supplied during the engineering session; no firmware commit SHA was recorded.
- GPIO proposal used by the test: GPIO4=BCLK, GPIO5=WS/LRCLK, GPIO6=SD/DOUT. This mapping remains provisional.

The supplied serial transcript is archived in [the I²S diagnostic log](../../commands/logs/2026-11-09_esp32-s3_inmp441-i2s-diagnostic.log).

## Test configuration

The temporary diagnostic used the legacy ESP-IDF I²S driver with:

| Parameter | Configuration |
|---|---|
| I²S port | I2S_NUM_0 |
| Mode | Master + RX |
| Sample rate | 16,000 Hz |
| Slot width | 32 bits |
| Channel format | RIGHT_LEFT |
| Communication format | Standard I²S |
| DMA buffers | 8 |
| DMA buffer length | 256 words |
| Raw buffer | 256 x 32-bit words |
| Candidate sample extraction | `raw >> 8` |
| Slot reporting | Even-indexed words = Slot A; odd-indexed words = Slot B |

Slot A and Slot B are diagnostic index labels. Their physical left/right mapping was not established by this test.

## Observed results

| Check | Result | Evidence / interpretation |
|---|---|---|
| I²S driver initialization | PASS | Serial output reports `I2S initialization: PASS`. |
| Read path returns data | PARTIAL | Read statistics count samples; non-zero raw words appear intermittently. |
| Stable non-zero capture | FAIL | Reports alternate between non-zero data and windows where one or both slots are entirely zero. |
| Raw 24-bit alignment | NOT VERIFIED | Several raw words have non-zero least-significant bytes, so the assumed left-aligned 24-bit representation is not established. |
| `raw >> 8` conversion | NOT VERIFIED | Conversion was used for statistics but cannot be accepted until alignment is confirmed. |
| Clipping-free PCM | FAIL / NOT ESTABLISHED | Repeated extrema reach approximately -8,388,608 and +8,388,607 after shifting. These may reflect real saturation or invalid sample interpretation; the log does not distinguish them. |
| Acoustic response | NOT VERIFIED | No controlled quiet-versus-speech comparison is documented in this transcript. |
| Physical wiring and supply | BLOCKED | No board/module photographs, verified carrier-board pinout, or measured microphone supply voltage were supplied. |

## Representative raw samples

The diagnostic captured the following words:

```text
WORD[221] 0x00000007 | SHIFTED: 0
WORD[222] 0xFFFFFFFE | SHIFTED: -1
WORD[223] 0xFDFFFBF7 | SHIFTED: -131077
WORD[224] 0xFFFFFFFE | SHIFTED: -1
WORD[225] 0xBFFF5D58 | SHIFTED: -4194467
WORD[226] 0x00000000 | SHIFTED: 0
WORD[227] 0x00000007 | SHIFTED: 0
WORD[228] 0xFFFFFFFE | SHIFTED: -1
WORD[229] 0xEABAF6A8 | SHIFTED: -1393930
WORD[230] 0x00000000 | SHIFTED: 0
WORD[231] 0x00000005 | SHIFTED: 0
WORD[232] 0xFFFFFFFE | SHIFTED: -1
WORD[233] 0xAAEADEB0 | SHIFTED: -5575970
WORD[234] 0x00000000 | SHIFTED: 0
WORD[235] 0x00000005 | SHIFTED: 0
WORD[236] 0xFFFFFFFE | SHIFTED: -1
WORD[237] 0xAAAAAAA8 | SHIFTED: -5592406
WORD[238] 0x00000000 | SHIFTED: 0
WORD[239] 0x00000005 | SHIFTED: 0
WORD[240] 0xFFFFFFFE | SHIFTED: -1
WORD[241] 0xAAAAAAA8 | SHIFTED: -5592406
```

The low byte is not consistently `0x00`. This is evidence that the assumed sample alignment needs further investigation; it is not sufficient by itself to identify the root cause.

## Channel statistics observed

The supplied output includes these distinct conditions:

- Initial report: both slots zero.
- A later report: Slot A RMS 9,171.39; Slot B RMS 147,090.09.
- Subsequent reports: both slots show large extrema near the signed 24-bit limits.
- Other reports: Slot B is entirely zero while Slot A remains active.
- At least one report shows both slots entirely zero again.
- Serial monitor reported `Disconnected ([Errno 5] Input/output error)` followed by reconnection. The cause of this host-side serial disconnect is not established.

Even/odd slot statistics are not proof that both physical I²S channels contain valid microphone audio.

## Result

**Overall microphone capture acceptance: FAIL / NOT VERIFIED.**

The I²S driver initializes and intermittent non-zero digital words are observed. The current evidence does not establish stable, correctly aligned, unclipped PCM audio or a verified physical microphone connection.

Do not mark I²S microphone capture as PASS. Do not integrate this capture path into BLE audio streaming yet.

## Next actions

1. Identify the exact ESP32-S3 carrier-board model and PCB revision from its markings.
2. Verify GPIO4, GPIO5, and GPIO6 against that board's pinout before treating the mapping as final.
3. Inspect and record the physical INMP441 wiring, including L/R selection and common ground.
4. Measure VDD-to-GND directly at the microphone breakout and confirm it is within the breakout/microphone specification.
5. Repeat capture after hardware verification, preserving raw words and separate slot statistics.
6. Establish sample alignment and channel selection before accepting `raw >> 8` or converting to signed 16-bit PCM.
7. Run controlled quiet-room and speech tests; compare measured signal behavior rather than relying only on MIN/MAX.

## Scope limitation

This report covers only the supplied ESP32-S3 I²S diagnostic output. It does not change the historical ESP8266 V0.5 test result, and it does not establish BLE audio notifications, throughput, latency, Android playback, or PC playback.

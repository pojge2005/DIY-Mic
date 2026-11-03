# Audio Pipeline

## Capture path

1. INMP441 produces digital I²S audio.
2. ESP32-C3 I²S RX reads DMA samples.
3. Firmware validates channel slot and bit alignment.
4. Samples are converted to the selected transport representation.
5. Fixed-size frames are assembled with sequence and timing metadata.
6. Frames enter a bounded transport queue.
7. BLE task transmits queued frames without blocking I²S capture.

## Proposed first benchmark format

| Parameter | Initial value | Status |
|---|---:|---|
| Channels | Mono | Proposed |
| Sample rate | 16,000 samples/s | Proposed benchmark |
| Transport sample format | Signed 16-bit PCM | Proposed benchmark |
| Byte order | Little-endian | Proposed |
| Logical frame duration | 10 ms | Proposed |
| Samples per frame | 160 | Derived |
| PCM bytes per frame | 320 | Derived |

Calculation: 16,000 samples/s × 0.010 s × 2 bytes = 320 bytes per logical frame. BLE notifications may carry less than 320 bytes; frame fragmentation/reassembly is therefore required unless a negotiated payload supports the full frame.

## Data-rate estimates

| Format | Uncompressed mono payload rate |
|---|---:|
| 16 kHz × 16-bit | 256 kbit/s |
| 16 kHz × 24-bit | 384 kbit/s |
| 24 kHz × 16-bit | 384 kbit/s |
| 32 kHz × 16-bit | 512 kbit/s |
| 44.1 kHz × 16-bit | 705.6 kbit/s |
| 48 kHz × 16-bit | 768 kbit/s |

These are payload rates before protocol overhead, fragmentation and retransmission effects.

## Receiver path

BLE notifications → packet validation → sequence tracking → frame reassembly → jitter buffer → AudioWorklet → audio output.

The receiver must handle missing, late, duplicate and malformed fragments. It must count underruns and conceal or mute missing intervals rather than allowing corrupted packets into the audio renderer.

## Visualization

The browser should calculate waveform and FFT from received PCM. Use a suitable window function and FFT size, and label the frequency axis correctly for the active sample rate. RMS and peak can be calculated over short analysis windows. The ESP32 may report lightweight diagnostic RMS/peak separately, but the browser should not need duplicate FFT processing on the MCU.

## Buffering and latency

Use a bounded jitter buffer. The initial buffer depth is a measurement parameter, not a fixed specification. Measure microphone-to-output latency and adjust frame duration, connection interval and buffer depth based on dropouts and responsiveness.

## Compression

Do not introduce compression in the first baseline. If raw PCM cannot meet the measured BLE throughput target, evaluate IMA ADPCM as the first lower-complexity candidate. Evaluate Opus or dedicated audio hardware only if the measured requirements justify their implementation cost.

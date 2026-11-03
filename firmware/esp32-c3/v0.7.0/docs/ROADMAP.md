# DIY-Mic V0.7.0 Roadmap

This roadmap uses the selected ESP32-C3 Wi-Fi SoftAP + WebSocket direction. V0.5/V0.6 remain historical and untouched.

| Phase | Deliverable | Exit condition |
|---|---|---|
| 0 | Documentation and hardware audit | Board, mic, wiring and receiver decisions reviewed |
| 1 | Clean PlatformIO board baseline | Build and serial diagnostics pass |
| 2 | I²S-only capture | Stable samples; channel, alignment and rate verified |
| 3 | PCM and buffering | Correct PCM and bounded queues |
| 4 | Wi-Fi SoftAP | Phone/PC can join and maintain local connection |
| 5 | WebSocket control | Receiver connects and start/stop/status work |
| 6 | Audio streaming | Sustained binary PCM stream without unacceptable loss |
| 7 | Browser playback | Live audio plays with measured latency |
| 8 | Reliability | 30-minute stream and reconnect tests pass |
| 9 | Optional visualization | Waveform/FFT/meters, only if approved |
| 10 | Power and physical prototype | Current measured and assembly documented |

## Phase 0 — Before coding

- Review the existing repository documentation and V0.6 logs.
- Confirm ESP32-C3 Super Mini and INMP441 breakout details.
- Physically verify the proposed GPIO wiring.
- Confirm Android and Ubuntu/PC receiver targets.
- Decide where the receiver page will be hosted.
- Approve the first audio benchmark and acceptance criteria.

## Phase 1 — Board baseline

Create a clean PlatformIO project, confirm board/framework versions, print chip and reset diagnostics, and verify USB CDC. Do not enable I²S or Wi-Fi yet.

## Phase 2 — I²S capture

Use the verified pin map. Capture silence and speech. Verify channel slot, sample alignment and effective sample rate. Record DC offset, RMS, peak and DMA errors.

## Phase 3 — PCM and buffering

Start with proposed mono 16 kHz signed 16-bit PCM. Assemble 10 ms logical frames. Verify sequence and sample counts. Test queue-full behavior and capture continuity.

## Phase 4–5 — Network baseline

Start SoftAP and verify phone/PC connectivity. Implement minimal WebSocket control. Verify status, start, stop and disconnect/reconnect before sending audio.

## Phase 6–7 — Streaming and playback

Send binary audio frames. Add receiver validation and bounded jitter buffering. Play PCM through Web Audio. Measure end-to-end latency and audio artifacts.

## Phase 8 — Reliability

Run a 30-minute continuous stream. Test receiver reload, Wi-Fi disconnect/reconnect and no-client behavior. Record dropped frames, queue high-water mark, underruns and current.

## Phase 9–10 — Optional enhancements

Add waveform/FFT only if approved and only after playback is stable. Measure current in idle, capture-only, SoftAP-only and streaming modes. Assemble the compact physical prototype after jumper-wire bring-up passes.
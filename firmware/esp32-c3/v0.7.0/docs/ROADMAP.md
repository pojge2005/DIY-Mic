# DIY-Mic V0.7.0 Roadmap

This roadmap is specific to the ESP32-C3 Bluetooth-first branch. It supersedes earlier transport-priority suggestions for this version, while preserving the repository's V0.5/V0.6 history.

| Phase | Deliverable | Exit condition |
|---|---|---|
| 0 | Documentation and hardware audit | Board, mic, wiring and unresolved questions reviewed |
| 1 | PlatformIO board baseline | Clean project compiles and serial diagnostics work |
| 2 | I²S-only capture | Stable samples; bit alignment, channel and rate verified |
| 3 | PCM and frame baseline | Correct PCM files/metrics and bounded frame buffers |
| 4 | BLE discovery and control | Browser connects, reads state and sends commands |
| 5 | BLE throughput benchmark | Sustained throughput and packet behavior measured |
| 6 | BLE audio transport | PCM frames reconstructed without unacceptable loss |
| 7 | Browser audio playback | Live audio audible with measured latency |
| 8 | Browser visualization | Waveform, RMS, peak and FFT work during playback |
| 9 | Reliability and recovery | 30-minute test and reconnect test pass |
| 10 | Optional Wi-Fi comparison | Local SoftAP tested independently if BLE misses requirements |
| 11 | Power and physical prototype | Current measured; zero-PCB assembly documented |

## Phase 0 — Before coding
- Read the existing repository documents and V0.6 logs.
- Confirm exact ESP32-C3 Super Mini board revision.
- Confirm INMP441 breakout model and existing components.
- Verify GPIO wiring and USB serial behavior.
- Agree audio quality and latency acceptance targets.
- Review the open items document.

## Phase 1 — Board baseline
- Create a minimal PlatformIO project in this version folder.
- Confirm board ID, platform and framework.
- Print chip, flash, reset reason and firmware version.
- Confirm USB CDC upload and monitor.
- Do not enable audio or wireless yet.

## Phase 2 — I²S capture
- Configure the current proposed GPIO map only after physical verification.
- Capture silence and speech.
- Verify left/right slot and bit alignment.
- Measure effective sample rate and sample amplitude.
- Save test captures and analysis.

## Phase 3 — PCM and buffering
- Convert to signed 16-bit mono PCM for the initial benchmark.
- Assemble 10 ms logical frames.
- Verify sequence and sample counts.
- Test queue overflow and capture continuity.

## Phase 4 — BLE control
- Implement advertising, GATT discovery and start/stop commands.
- Test Android Chrome and Ubuntu Chromium.
- Exchange status and capability information before sending audio.

## Phase 5 — BLE benchmark
- Measure negotiated MTU, usable payload, notification throughput, packet gaps and current.
- Test multiple connection intervals and PHY options where supported.
- Benchmark actual browser/device pairs, not only ESP32-to-ESP32 examples.
- Decide whether 16 kHz / 16-bit mono PCM is feasible.

## Phase 6–8 — Audio and receiver
- Implement packet framing and fragmentation.
- Add browser jitter buffer and AudioWorklet playback.
- Add waveform and FFT from received samples.
- Tune buffering against measured latency and glitches.

## Phase 9 — Reliability
- Run 30-minute continuous streaming.
- Test disconnect/reconnect, out-of-range recovery and receiver page reload.
- Record packet loss, underruns and audio artifacts.

## Phase 10–11 — Optional comparison and prototype
- If BLE fails the accepted requirements, evaluate local Wi-Fi SoftAP as a separate direct link. Internet is not required for SoftAP.
- Compare latency, quality, range, current and usability.
- Assemble zero-PCB only after the electrical and firmware baseline is stable.

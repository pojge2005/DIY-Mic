# Verification and Test Plan

## Test rule

Record firmware commit, board revision, microphone breakout, receiver device, OS/browser version, test distance, power source and environmental conditions. Separate owner observations from instrumented measurements.

## Hardware bring-up

- Inspect exact board revision and silkscreen.
- Verify 3.3 V at the microphone supply.
- Confirm common ground and I²S pin continuity.
- Confirm USB programming and serial monitor.
- Cold boot with microphone connected.
- Check for boot failures or GPIO strapping conflicts.

## I²S and PCM
- Capture at least 10 seconds of silence and speech.
- Verify left/right slot selection.
- Verify sample alignment and signed conversion.
- Verify effective sample rate from captured samples.
- Calculate DC offset, RMS, peak and clipping.
- Check for DMA overruns and capture errors.

## BLE control
- Discover and connect from Android Chrome.
- Discover and connect from Ubuntu Chromium.
- Read device information and capabilities.
- Subscribe to telemetry.
- Send start/stop/mute commands.
- Test disconnect and reconnect.

## BLE throughput
- Record PHY, ATT MTU, data length and connection interval where available.
- Measure sustained application payload throughput, not PHY rate.
- Test packet fragmentation and reassembly.
- Record sequence gaps, duplicates, malformed frames and retransmission effects.
- Test with target phones/laptops.

## Live audio
- Begin with 16 kHz / 16-bit / mono PCM.
- Measure end-to-end latency using a repeatable acoustic or electrical method.
- Record audio dropouts, clicks, underruns and drift.
- Compare buffer depths.
- Verify listening and visualization operate simultaneously.

## Visualization
- Verify waveform amplitude and timing.
- Verify FFT frequency axis using known test tones.
- Verify RMS and peak calculations.
- Confirm analysis does not cause audio underruns.
- Confirm UI rendering does not block audio processing.

## Reliability
- 30-minute continuous stream.
- Repeated connect/disconnect.
- Receiver reload during streaming.
- Temporary radio interference and out-of-range recovery.
- Queue saturation and malformed packet handling.

## Power
- Measure idle, BLE connected, capture-only and audio-streaming current.
- Do not estimate battery runtime until a battery and regulator are selected.
- Wi-Fi current is measured only in the optional SoftAP comparison.

## Acceptance gates
- Board bring-up passes.
- I²S data is correct.
- BLE control is stable.
- Sustained throughput meets the selected audio format with margin.
- Live playback and visualization work simultaneously.
- Latency and reliability meet the agreed targets.
- All results are documented.

A phase is not complete solely because code compiles.

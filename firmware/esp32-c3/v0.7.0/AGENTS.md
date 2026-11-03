# DIY-Mic V0.7.0 Coding Rules

These rules apply when firmware implementation begins. This documentation baseline contains no firmware source.

## General
- Keep code straightforward and small.
- Use clear module boundaries; do not create empty modules.
- Avoid unnecessary frameworks, abstractions, dynamic allocation and background tasks.
- Keep audio capture, packet transport, device control and diagnostics independent.
- Use fixed-size buffers for the real-time audio path.
- Do not block the audio capture task on BLE transmission or logging.
- Do not print per-sample or per-packet debug output during normal streaming.
- Check every driver/API return value and expose actionable error states.
- Document any non-obvious timing, buffer ownership or concurrency rule.

## Audio
- Confirm actual I²S bit alignment, channel slot and sample rate using captured data.
- Keep raw microphone format separate from the transport PCM format.
- Never assume that configured sample rate equals measured effective sample rate.
- Track overruns, underruns, dropped frames and clipping.
- Use explicit signedness, bit width, endianness and sample count.

## BLE
- Use a versioned custom GATT protocol.
- Negotiate and record MTU and data length; never assume a fixed notification payload.
- Include sequence numbers and validate packet lengths.
- Keep audio data and low-rate control/telemetry logically separate.
- Do not call the custom service Bluetooth audio, A2DP or LE Audio.

## Receiver
- Keep BLE connection management separate from audio playback and visualization.
- Use a bounded jitter buffer and report underruns.
- Keep UI rendering off the audio rendering callback.
- Browser compatibility and permission failures must be visible to the user.

## Quality
- No feature is marked complete without a repeatable test result.
- Record board revision, firmware commit, receiver/browser version and test conditions.
- Do not claim latency, range, battery runtime or audio quality without measurements.

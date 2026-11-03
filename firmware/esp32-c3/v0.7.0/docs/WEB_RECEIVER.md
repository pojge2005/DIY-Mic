# Browser Receiver Architecture

## Required experience

The browser receiver must provide both live audio playback and live visualization. The dashboard is not a telemetry-only tool.

## Browser API roles

- Web Bluetooth: device discovery, GATT connection, reads, writes and notifications.
- Web Audio API: playback and analysis.
- AudioWorklet: audio rendering and processing without relying on UI frame timing.
- Canvas or equivalent rendering: waveform and frequency spectrum display.
- PWA caching: optionally cache the receiver assets for offline launch after the first successful load.

## Runtime flow

1. User opens the receiver from a secure HTTPS origin.
2. User taps Connect and selects DIY-Mic.
3. Browser requests the required BLE service.
4. Receiver discovers characteristics and subscribes to notifications.
5. User starts microphone capture.
6. Audio fragments are validated and reconstructed.
7. Reconstructed PCM enters a bounded jitter buffer.
8. AudioWorklet consumes audio for playback.
9. Analysis worker/main processing calculates waveform, RMS, peak and FFT.
10. UI displays audio and connection statistics.

## Dashboard controls

- Connect / disconnect.
- Start / stop capture.
- Mute / unmute playback.
- Playback volume.
- Waveform and spectrum display.
- RMS and peak indicators.
- BLE state, sample format and stream state.
- Received frames, missing frames, malformed packets and buffer underruns.

## Compatibility constraints

Web Bluetooth is not universally supported. The first target matrix is:
- Android: Chrome, verify on the actual phone and OS version.
- Ubuntu: Chrome or another Chromium-based browser, verify actual Web Bluetooth availability.
- Safari and Firefox: not supported by the standard Web Bluetooth API at the time of this baseline.

The receiver must detect unsupported browsers and show a clear message. Do not promise iOS Safari support through Web Bluetooth. A future native receiver may be required for unsupported platforms.

## Internet independence

The BLE audio connection itself does not require internet. The web application must be loaded from a secure origin. A PWA/service worker may cache static assets for offline use after the initial load. Device discovery and audio transfer remain local BLE operations.

## Audio implementation constraints

- Do not perform expensive drawing or FFT work inside the AudioWorklet render callback.
- Use a bounded queue between BLE event handling and audio processing.
- Prevent unbounded memory growth if notifications arrive faster than playback.
- Expose underruns, dropped frames and reconnects in the UI.
- Handle browser audio autoplay/user-gesture restrictions.
- Do not claim low latency until measured end-to-end on target devices.

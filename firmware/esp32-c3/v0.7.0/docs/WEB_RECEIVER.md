# Browser Receiver Architecture

## Required experience

The initial receiver must connect to the DIY-Mic local Wi-Fi network, open a WebSocket connection and play live audio. Visualization is optional until confirmed as a product requirement.

## Browser API roles

- Wi-Fi: user joins the ESP32-C3 SoftAP through the phone or computer network settings.
- WebSocket: receives binary audio frames and sends control messages.
- Web Audio API: schedules and plays PCM audio.
- AudioWorklet: optional robust audio rendering path if needed after the first playback prototype.
- Canvas: optional waveform and spectrum display.
- PWA caching: optional; useful if the receiver page must remain available without internet.

## Runtime flow

1. User powers the microphone.
2. ESP32-C3 starts its SoftAP.
3. User joins the DIY-Mic Wi-Fi network.
4. User opens the receiver page.
5. Receiver connects to the WebSocket endpoint.
6. User starts the stream.
7. Receiver validates frames and sequence numbers.
8. PCM enters a bounded jitter buffer.
9. Web Audio plays the audio through the selected output device.
10. Receiver displays connection and stream state.

## Receiver controls

- Connect / disconnect.
- Start / stop stream.
- Mute / unmute playback.
- Playback volume.
- Connection and stream status.
- Received frames, missing frames and buffer underruns.
- Optional waveform, spectrum, RMS and peak.

## Hosting decision

The receiver UI may be served directly by the ESP32-C3 or hosted separately and opened while connected to the SoftAP. This must be decided before implementation. If served from the ESP32, keep assets small and account for available flash. If hosted separately, confirm that the browser can still reach the ESP32 WebSocket endpoint while connected to its AP.

## Internet and phone behavior

The local audio data path does not require internet. Some phones may warn that the Wi-Fi network has no internet and may switch back to mobile data or another network. Test the target Android device and document the steps to remain connected to the local device.

## Playback constraints

- Handle browser audio autoplay restrictions with a user gesture.
- Bound all audio queues.
- Keep UI rendering out of the real-time audio rendering path.
- Expose reconnects, dropped frames and underruns.
- Measure actual end-to-end latency.
- Do not promise background playback or locked-screen behavior until tested on target browsers.
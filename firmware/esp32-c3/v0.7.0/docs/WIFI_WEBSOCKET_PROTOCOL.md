# Wi-Fi and WebSocket Protocol — Draft 0.1

**Status:** Proposed protocol; endpoint, frame header and network settings are not frozen.

## Connection model

1. ESP32-C3 starts a Wi-Fi SoftAP.
2. Receiver joins the SoftAP using configured credentials.
3. Receiver connects to the documented WebSocket endpoint.
4. Receiver requests or negotiates the audio format.
5. ESP32-C3 starts I²S capture and sends binary audio frames.
6. Receiver validates frames, buffers audio and plays it.
7. Receiver sends stop/mute/control messages as defined by the final protocol.

The SoftAP IP address, port, URL path and credential setup must be selected and documented before implementation.

## Proposed initial audio format

| Parameter | Initial value | Status |
|---|---:|---|
| Channels | Mono | Proposed |
| Sample rate | 16,000 samples/s | Proposed benchmark |
| Transport sample format | Signed 16-bit PCM | Proposed benchmark |
| Byte order | Little-endian | Proposed |
| Logical frame duration | 10 ms | Proposed |
| Samples per frame | 160 | Derived |
| PCM bytes per frame | 320 | Derived |

Raw payload rate is 256 kbit/s before WebSocket/TCP/IP overhead. This should be a modest starting point for local Wi-Fi, but it must still be benchmarked on the actual system.

## Binary audio frame

The final frame should contain:
- Protocol version.
- Frame sequence number.
- Sample counter or timestamp.
- Sample rate or negotiated format identifier.
- Sample count and payload length.
- Audio payload.

Define field widths, endianness and timestamp units before coding. Reject malformed or unsupported frames.

## Control messages

The protocol should support GET_STATUS, START_STREAM, STOP_STREAM, optional SET_AUDIO_FORMAT, playback mute and PING/PONG or equivalent connection health check.

Use a simple versioned JSON control message initially if no performance reason requires binary control messages. Audio data must remain binary.

## Buffering and backpressure

- I²S capture must never block while waiting for WebSocket writes.
- Use bounded queues and fixed-size audio buffers.
- Count dropped frames and queue high-water marks.
- Define behavior when no client is connected.
- Avoid unbounded buffering when the receiver is slow.
- Send sequence numbers so the receiver can detect gaps.

## Security and configuration

- Do not hard-code production credentials in public source.
- Provide a configurable AP SSID and password.
- Document whether the AP is open or WPA2 protected; WPA2 is preferred.
- Validate control messages and document the local network trust boundary.

## Open decisions

- SoftAP SSID/password configuration and provisioning.
- Static IP and WebSocket port/path.
- Whether the ESP32 serves the receiver web page or the page is hosted separately.
- Frame header layout and control schema.
- Reconnect and multiple-client policy.
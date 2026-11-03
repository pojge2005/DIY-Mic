# BLE GATT Protocol — Draft 0.1

**Status:** Proposal only. UUIDs and binary layout are not frozen.

## GATT service model

Use one custom primary service with logically separate characteristics.

| Characteristic | Direction | Properties | Purpose |
|---|---|---|---|
| Device Information | Read | Read | Firmware version, hardware ID and capabilities |
| Audio Control | Both | Read, Write, Write Without Response as appropriate | Start, stop, mute and audio configuration |
| Audio Data | Device → receiver | Notify | Fragmented audio frame payload |
| Telemetry | Device → receiver | Notify, Read | Capture state, buffer health, counters and signal metrics |

Use the standard Bluetooth Device Information Service where appropriate rather than duplicating standard fields. Custom UUID allocation must be completed before implementation.

## Connection sequence

1. Advertise a stable DIY-Mic service identifier.
2. Browser scans and user selects the device.
3. Connect and discover services/characteristics.
4. Read protocol version and supported capabilities.
5. Subscribe to telemetry.
6. Negotiate audio format and start command.
7. Subscribe to audio notifications.
8. Send START command.
9. Receive and reassemble frames.
10. Send STOP or disconnect cleanly.

The exact ordering of subscription and START must prevent initial frames from being lost.

## Logical audio frame fields

The protocol must carry enough information to detect corruption and recover frame boundaries. Proposed logical fields:

| Field | Purpose |
|---|---|
| Protocol version | Format compatibility |
| Frame sequence | Detect missing or duplicate frames |
| Timestamp or sample counter | Preserve audio timing |
| Sample format | Signed PCM width and encoding |
| Sample rate | Audio clock |
| Channel count | Mono/stereo |
| Sample count | Number of samples represented |
| Frame payload length | Validate received data |
| Fragment index/count | Reassemble BLE-sized fragments |
| Audio payload | PCM samples |

A compact binary header should be designed after the effective notification payload and MTU negotiation are known. Do not commit a byte layout in this draft.

## Fragmentation

A 10 ms frame at the proposed 16 kHz / 16-bit / mono setting contains 320 payload bytes, which may exceed a single notification payload. Fragmentation must include frame sequence, fragment index and fragment count or an equivalent unambiguous framing method.

Never assume the negotiated ATT MTU or usable notification payload. Read and record the negotiated values on both sides where available.

## Telemetry

Suggested low-rate fields:
- Device state and uptime.
- Audio capture state.
- Active sample rate and sample format.
- BLE connection and negotiated MTU.
- Frames generated, transmitted and dropped.
- Audio queue high-water mark.
- I²S read errors and overruns.
- RMS and peak values.
- Battery voltage only if a real voltage-sensing circuit is later added.

## Protocol requirements

- Version every protocol revision.
- Define integer widths, signedness, byte order and units.
- Validate payload length before accessing fields.
- Detect sequence gaps and duplicates.
- Define behavior for unsupported versions and formats.
- Keep telemetry low-rate; do not mix debug text into binary audio notifications.
- Avoid unnecessary encryption claims; BLE link security and application-level authentication requirements must be documented separately.

## Open protocol decisions

UUIDs, exact header, timestamp units, MTU strategy, connection parameters, maximum supported sample rate and reconnection behavior remain open until the prototype benchmark is complete.

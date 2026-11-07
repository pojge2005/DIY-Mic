# BLE GATT Specification — ESP32-S3

## UUID base

All characteristics observed in the current test use:

`7b3a000X-6d7b-4f21-9a11-6e4d594d4943`

## Service and characteristics

| Attribute | UUID | Intended use | Current evidence |
|---|---|---|---|
| Primary service | `7b3a0001-6d7b-4f21-9a11-6e4d594d4943` | DIY-Mic custom BLE service | Service discovery reported PASS |
| Status | `7b3a0002-6d7b-4f21-9a11-6e4d594d4943` | Device / connection status | Read returned `CONNECTED` |
| Control | `7b3a0003-6d7b-4f21-9a11-6e4d594d4943` | Host-to-device commands | PING/PONG not confirmed in available report |
| Audio | `7b3a0004-6d7b-4f21-9a11-6e4d594d4943` | Device-to-host audio notifications | Notification behavior not confirmed in available report |

## Known command test

The host command `PING` is ASCII bytes:

`50 49 4e 47`

The expected response is `PONG`. This is a test expectation, not a confirmed result.

## Open protocol details

The following must be specified from firmware and measured behavior before the protocol is treated as stable:

- Characteristic properties and permissions.
- Whether Status supports read, notify, or both.
- Whether Control uses write or write-without-response.
- Whether command responses are returned through Status, Control, or a separate response characteristic.
- Audio encoding, sample rate, channel count, bit depth, byte order, framing, and sequence numbering.
- Maximum payload and negotiated ATT MTU.
- Notification interval and sustained throughput.
- Error codes and reconnect behavior.

Do not infer audio packet format from the characteristic UUID alone.

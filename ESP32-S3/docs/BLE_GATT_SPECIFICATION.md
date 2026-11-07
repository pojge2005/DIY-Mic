# BLE GATT Specification — ESP32-S3

## Peripheral

- Advertised name: `DIY-Mic-S3`.
- Observed BLE address: `30:ED:A0:A8:A4:F0`.
- Custom service UUID: `7b3a0001-6d7b-4f21-9a11-6e4d594d4943`.

## Service and characteristics

| Attribute | UUID | Intended direction | Intended use | Evidence |
|---|---|---|---|---|
| Primary service | `7b3a0001-6d7b-4f21-9a11-6e4d594d4943` | — | DIY-Mic custom service | Discovered |
| Status | `7b3a0002-6d7b-4f21-9a11-6e4d594d4943` | Device → host | Device/connection state and possible response notifications | Read returned CONNECTED |
| Control | `7b3a0003-6d7b-4f21-9a11-6e4d594d4943` | Host → device | Commands such as PING | UUID/path observed; write pending |
| Audio | `7b3a0004-6d7b-4f21-9a11-6e4d594d4943` | Device → host | Experimental audio notifications | Delivery pending |

## Known control test

- Text: `PING`
- Hex: `50 49 4e 47`
- Expected response: `PONG`

The expected response must be verified on the device. The available test output does not identify the response characteristic.

## BlueZ paths observed

| Characteristic | Object path |
|---|---|
| Status | `/org/bluez/hci0/dev_30_ED_A0_A8_A4_F0/service000e/char000f` |
| Control | `/org/bluez/hci0/dev_30_ED_A0_A8_A4_F0/service000e/char0012` |
| Audio | Resolve from current `list-attributes` output by Audio UUID |

BlueZ object paths are runtime identifiers and may change. UUIDs are the stable identifiers.

## Protocol details still to establish

- Live characteristic properties and permissions.
- Whether Status supports notifications.
- Control write type: write request or write without response.
- Exact PONG/error response characteristic.
- Exact audio start/stop command and payload.
- Audio sample rate, channels, bit depth, encoding, and byte order.
- Packet framing, sequence number, and timestamp format.
- Negotiated ATT MTU and maximum notification payload.
- Notification cadence, sustained throughput, packet loss, and reconnect behavior.

Do not infer these values from UUIDs or intended use alone.

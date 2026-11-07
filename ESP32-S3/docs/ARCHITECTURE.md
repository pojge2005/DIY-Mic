# ESP32-S3 BLE Bring-up Architecture

## Scope

This is the experimental ESP32-S3 track for DIY-Mic. It is separate from the historical ESP8266 Wi-Fi prototype and ESP32-C3 development track.

## Current test topology

```text
Ubuntu host
  └── BlueZ / BLE client
       └── ESP32-S3 BLE GATT server
            ├── Status characteristic
            ├── Control characteristic
            └── Audio characteristic
```

The INMP441 microphone is the intended audio source. The available test record confirms BLE connection and a successful status read only. It does not yet establish end-to-end audio capture or audio streaming.

## Planned data path

```text
INMP441 --I²S--> ESP32-S3
                   |
                   +-- GATT Status: connection / device state
                   +-- GATT Control: command channel
                   +-- GATT Audio: experimental notification channel
                                      |
                                      v
                                Android / PC receiver
```

The exact I²S pins, sample format, packet format, notification cadence, MTU, throughput, and receiver behavior remain to be measured and documented.

## Architecture boundaries

- Audio capture: I²S microphone acquisition.
- Control plane: BLE GATT status and command characteristics.
- Audio data plane: experimental GATT notifications; throughput and latency are unverified.
- Receiver: host-side BLE client for bring-up, followed by Android/PC receiver evaluation.
- Power: board-specific supply and current measurements are pending.

BLE connection success does not prove that BLE is suitable for continuous audio. Validate payload throughput, packet loss, latency, reconnect behavior, and power before selecting it as the product transport.

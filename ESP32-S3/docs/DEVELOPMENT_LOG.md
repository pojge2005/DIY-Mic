# ESP32-S3 Development Log

## BLE bring-up baseline

The supplied test record reports:

- BLE device discovery: PASS.
- BLE connection from Ubuntu: PASS.
- GATT service discovery: PASS.
- Status characteristic read: PASS.
- Status payload: hexadecimal `43 4f 4e 4e 45 43 54 45 44`, which decodes to `CONNECTED`.

The same record listed Control write, PING/PONG, and Audio notifications as pending. No result has been inferred for those tests.

## Repository baseline

The ESP32-S3 work is isolated in the root-level `ESP32-S3/` directory. Existing ESP8266 and ESP32-C3 development trees remain unchanged.

## Next validation steps

1. Confirm Control characteristic write behavior.
2. Confirm where and how PONG is returned.
3. Subscribe to Audio notifications and save a raw capture.
4. Identify exact ESP32-S3 board model and record INMP441 wiring.
5. Measure notification payload size, throughput, packet loss, and latency.

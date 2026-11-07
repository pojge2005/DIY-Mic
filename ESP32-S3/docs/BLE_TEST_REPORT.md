# BLE Test Report — ESP32-S3

## Test environment

- Host: Ubuntu with BlueZ command-line BLE tools
- Peripheral: DIY-Mic ESP32-S3
- Report source: recorded bring-up output supplied for this repository update
- Test date: not present in the supplied log

## Results

| Test | Result | Evidence / notes |
|---|---|---|
| BLE advertising / discovery | PASS (reported) | Device was discovered by the host |
| BLE connection | PASS | Host connected to the ESP32-S3 |
| GATT service discovery | PASS (reported) | Custom service was accessible |
| Status characteristic read | PASS | Returned bytes `43 4f 4e 4e 45 43 54 45 44`, ASCII `CONNECTED` |
| Control characteristic write | PENDING | No successful write output in the supplied report |
| PING/PONG | PENDING | Expected command is `PING`; response `PONG` not yet evidenced |
| Audio characteristic notifications | PENDING | No notification capture or audio payload evidence supplied |
| Audio playback | NOT TESTED | No receiver playback evidence supplied |

## Interpretation

The successful status read confirms that the host connected and could read the device's Status characteristic. It does not establish successful control writes or audio notifications.

## Required next evidence

1. Capture the result of writing ASCII `PING` to the Control characteristic.
2. Capture the corresponding `PONG` response, including the characteristic used to return it.
3. Subscribe to the Audio characteristic and record whether notifications arrive.
4. If notifications arrive, save a short raw capture and document payload length and timing.
5. Record firmware commit, board revision, test date, and host BLE tool versions.

Update this report only from observed test output. Do not change PENDING to PASS based on expected behavior.

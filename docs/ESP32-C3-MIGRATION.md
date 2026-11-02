# ESP32-C3 Super Mini and Wireless Migration Plan

## Objective

Move the current DIY-Mic prototype from NodeMCU ESP8266 to an ESP32-C3 Super Mini, retain the INMP441 I²S microphone, and build a small working prototype on zero PCB/perfboard.

After the ESP32-C3 Wi-Fi version is validated, evaluate BLE and dedicated low-power audio links. This is a future plan; the migration has not yet been completed.

## Why ESP32-C3?

The ESP32-C3 provides Wi-Fi, Bluetooth Low Energy (BLE), an I²S peripheral, and low-power operating modes. It is a practical next development board for the project. Refer to the exact board/module datasheet and pinout before wiring.

**Bluetooth limitation:** ESP32-C3 supports Bluetooth LE only. It does not support Bluetooth Classic. Do not plan on conventional A2DP headset audio directly from ESP32-C3 without changing the hardware platform.

## Target Hardware

- ESP32-C3 Super Mini development board
- INMP441 I²S MEMS microphone
- Zero PCB/perfboard for the first assembled prototype
- Appropriate 3.3 V power source and decoupling
- Battery and charging/protection hardware only after power requirements are measured and designed

The exact ESP32-C3 Super Mini board revision and pinout must be identified before finalizing GPIO assignments. Do not copy NodeMCU ESP8266 pin labels or low-level I²S code.

## Migration Stages

| Stage | Work | Exit condition |
|---|---|---|
| 1 | Identify exact ESP32-C3 Super Mini board | Board revision, module, pinout and flash documented |
| 2 | Verify microphone power and I²S wiring | Electrical connections checked |
| 3 | Create I²S-only firmware | Stable raw microphone capture |
| 4 | Validate PCM | Channel, bit alignment, sample rate and amplitude confirmed |
| 5 | Port Wi-Fi AP and WebSocket | Android receives valid audio frames |
| 6 | Build zero-PCB prototype | Stable assembled microphone prototype |
| 7 | Compare with ESP8266 | Same test procedure and measured results |
| 8 | Evaluate BLE | Data throughput, latency, phone compatibility and power measured |
| 9 | Evaluate low-power audio modules | Module and receiver feasibility documented |
| 10 | Choose wireless architecture | Decision supported by test results |

## Wireless Options

### Option A — Wi-Fi (baseline)

Keep the existing local access point + webpage + WebSocket model for the first ESP32-C3 port. It is the lowest-risk way to reuse the current Android receiver concept.

Measure:
- Average and peak current during streaming
- End-to-end latency
- Packet loss and jitter
- Stable range
- Audio quality and interruptions

### Option B — Bluetooth Low Energy

Use BLE initially for configuration, start/stop control, status, or other low-rate control functions.

A custom BLE audio-data experiment may be attempted, but it must demonstrate adequate throughput and stable real-time playback. Android browser compatibility may require a native app or a dedicated receiver rather than the current webpage.

BLE on ESP32-C3 is not Bluetooth Classic and does not by itself provide standard A2DP microphone/headset functionality.

### Option C — Dedicated low-power wireless/audio module

Evaluate a matched transmitter/receiver solution if the product needs lower power or a dedicated plug-in receiver. Check:
- Supported audio bandwidth and sample format
- Codec and end-to-end latency
- Operating range and interference behavior
- Transmit/receive current and sleep modes
- Antenna and module dimensions
- Receiver availability and interface
- Cost and documentation

Do not select a module based only on advertised range or low-power claims.

## Zero-PCB Build Plan

1. Confirm the exact ESP32-C3 Super Mini board.
2. Map safe, available GPIOs for I²S.
3. Connect the INMP441 using 3.3 V and common ground.
4. Add local supply decoupling.
5. Test I²S capture before adding wireless code.
6. Add Wi-Fi streaming after PCM is verified.
7. Assemble the working circuit on zero PCB/perfboard.
8. Check power integrity, audio noise, wiring robustness, and physical size.
9. Record photographs, wiring, and test results in the repository.

A zero-PCB build is a prototype assembly, not a manufactured PCB. A custom compact PCB may be designed after the circuit and component choices are stable.

## Battery and Low-Power Development

Do not estimate battery runtime from deep-sleep current alone. A live microphone streaming continuously must keep the microphone, MCU, and radio active. Measure average current in the actual operating mode and calculate runtime using the selected battery capacity, usable discharge range, regulator efficiency, and charging/protection losses.

Evaluate:
- Wi-Fi modem-sleep and duty-cycle opportunities where audio latency permits
- BLE connection/advertising intervals for control functions
- Microphone and regulator current
- Battery capacity, protection, charging, and safe enclosure
- Idle, listening, and reconnect power states

## Acceptance Criteria

The ESP32-C3 zero-PCB prototype is accepted when:
- I²S samples are stable and correctly interpreted.
- Wi-Fi streaming works with the Android receiver.
- A sustained stream test completes without unexplained dropouts.
- Latency, packet loss, range, and current are measured.
- Wiring and power are documented.
- The build can be reproduced from repository instructions.

BLE or a dedicated low-power transport is accepted only after separate tests show that it meets the product's audio and receiver requirements.

## References

- [ESP32-C3 Series Datasheet](https://documentation.espressif.com/esp32-c3_datasheet_en.html)
- [ESP-IDF Bluetooth LE Overview](https://docs.espressif.com/projects/esp-idf/en/latest/esp32c3/api-guides/ble/overview.html)

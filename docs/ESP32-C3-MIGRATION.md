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
- I²C GPIO expander for additional digital peripherals
- I²C ADC for analog sensors
- I²C-compatible ultrasonic sensor/interface, or a separate timing-capture helper, if an HC-SR04-style module is required
- Battery and charging/protection hardware only after power requirements are measured and designed

The exact ESP32-C3 Super Mini board revision and pinout must be identified before final wiring. Super Mini boards are sold in multiple layouts. Do not copy NodeMCU ESP8266 pin labels or low-level I²S code.

## Final ESP32-C3 GPIO Allocation

This is the project allocation for the common ESP32-C3 Super Mini layout. It is a design baseline, not a claim that every clone board exposes identical pins. Verify the silkscreen, module marking, and board schematic before soldering.

| ESP32-C3 GPIO | Assignment | Interface / notes |
|---|---|---|
| GPIO0 | I²C SDA | Shared bus for GPIO expander and external ADC |
| GPIO1 | I²C SCL | Shared bus for GPIO expander and external ADC |
| GPIO2 | Reserved | Strapping pin; do not attach a peripheral |
| GPIO3 | INMP441 SD | I²S microphone data input |
| GPIO4 | INMP441 BCLK | I²S bit clock; conflicts with external JTAG use |
| GPIO5 | INMP441 WS/LRCLK | I²S word select; conflicts with external JTAG use |
| GPIO6 | GPS UART1 RX | Connect to GPS module TX |
| GPIO7 | GPS UART1 TX | Connect to GPS module RX; optional if GPS is receive-only |
| GPIO8 | Reserved | Strapping pin; do not attach a peripheral |
| GPIO9 | Reserved | BOOT/strapping pin; preserve the onboard BOOT function |
| GPIO10 | DHT11 data | Direct GPIO; use a 3.3 V-compatible pull-up |
| GPIO11–GPIO17 | Reserved | Flash interface; do not use |
| GPIO18/GPIO19 | Native USB D-/D+ | Preserve for USB connection/debug; do not use as general GPIO |
| GPIO20 | UART0 RX | USB/UART bridge or board UART debug RX, subject to board routing |
| GPIO21 | UART0 TX | USB/UART bridge or board UART debug TX, subject to board routing |

### Peripheral expansion

The exposed GPIO count is not sufficient to connect every listed sensor directly while retaining I²S, GPS UART, USB, and UART debugging. Use the following expansion devices on the GPIO0/GPIO1 I²C bus:

| Peripheral | Connection plan |
|---|---|
| Four push buttons | MCP23017 GPIO expander inputs |
| PIR sensor | MCP23017 input, if its output timing requirements are compatible |
| IR receiver module | MCP23017 input/interrupt for ordinary demodulated remote-control signals; validate pulse capture before relying on it |
| MQ sensor analog output | ADS1115 analog input; ensure its output never exceeds the ADC input range |
| MQ sensor digital output | Optional MCP23017 input |
| LDR voltage divider | ADS1115 analog input |
| DHT11 | GPIO10 direct; do not route its timing-sensitive single-wire protocol through a slow GPIO expander |
| GPS | UART1 on GPIO6/GPIO7 |
| INMP441 | I²S on GPIO3/GPIO4/GPIO5 |
| Ultrasonic distance sensor | Prefer an I²C ultrasonic module/interface. A typical HC-SR04 needs two timing-sensitive GPIOs and a 5 V Echo level shift; it is not assigned to a strapping pin or a slow I²C GPIO expander in this allocation |

If an HC-SR04 must be retained, add a dedicated timer/capture helper or revise the allocation and give up another direct interface. Do not connect its 5 V Echo output directly to the ESP32-C3.

### Debugging and electrical constraints

- Keep USB D-/D+ (GPIO18/GPIO19) available for the board's native USB function.
- Keep UART0 debug on GPIO20/GPIO21 where the selected board routes those signals. Some boards use a USB-to-UART bridge; verify the schematic before assuming both paths are independently available.
- GPIO4/GPIO5 are usable as peripheral GPIO through the GPIO matrix, but external JTAG debugging on those pins will conflict with the microphone wiring.
- Keep GPIO2, GPIO8, and GPIO9 free because they are strapping pins. GPIO9 is also commonly connected to the BOOT button.
- Do not use GPIO11–GPIO17; these are associated with module flash.
- ESP32-C3 GPIO is 3.3 V logic. Never apply 5 V to a GPIO or ADC input.
- Use a proper divider or level shifter for any 5 V sensor output.
- Put the INMP441 supply decoupling close to the microphone breakout. Do not add capacitors to the I²S signal lines as a noise fix.
- Confirm I²C addresses and bus pull-ups. Ensure all I²C devices use compatible logic voltage and avoid multiple excessively strong pull-ups.

### I²C bus starting configuration

Use GPIO0 as SDA and GPIO1 as SCL. Start at 100 kHz while bringing up the expander and ADC, then test 400 kHz only after wiring length, pull-ups, and all devices are validated. Assign non-conflicting I²C addresses and document them in the wiring record.

### GPIO allocation acceptance checks

Before building the full prototype:

1. Confirm the exact board revision and continuity of the USB/UART connections.
2. Test USB programming/debug and UART0 logging with no peripherals attached.
3. Verify I²S capture on GPIO3/GPIO4/GPIO5.
4. Verify GPS UART1 on GPIO6/GPIO7.
5. Scan the I²C bus on GPIO0/GPIO1 and verify the expander and ADC addresses.
6. Verify DHT11 on GPIO10.
7. Test each expander input and each ADC channel independently.
8. Validate the selected ultrasonic interface, including its timing and voltage levels.
9. Run all interfaces together and check for boot failures, missed audio frames, and bus errors.

Do not mark the GPIO map as hardware-validated until these tests pass on the actual board.

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
2. Wire the INMP441 according to the GPIO table.
3. Bring up USB/UART debugging before attaching sensors.
4. Add the I²C expander and ADC, then verify each device.
5. Connect DHT11 and the selected ultrasonic interface.
6. Test I²S capture before adding wireless code.
7. Add Wi-Fi streaming after PCM is verified.
8. Assemble the working circuit on zero PCB/perfboard.
9. Check power integrity, audio noise, wiring robustness, and physical size.
10. Record photographs, wiring, and test results in the repository.

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

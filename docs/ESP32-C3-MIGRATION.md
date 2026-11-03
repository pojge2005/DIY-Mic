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

## ESP32-C3 SuperMini GPIO Allocation (Development Proposal)

This allocation targets the ESP32-C3 SuperMini with **no display**. It supports the current project microphone and the previously listed expansion peripherals: DHT11, PIR, ultrasonic distance sensor, GPS, LDR, MQ gas sensor, and four push buttons. It also preserves USB and UART debugging.

**Important:** This is a board-level design proposal, not a physically validated wiring map. Confirm the exact SuperMini revision, exposed header labels, and module schematic before soldering. GPIO numbers below are ESP32-C3 GPIO numbers, not NodeMCU labels.

### Direct GPIO map

| Function | ESP32-C3 GPIO | Connection / notes |
|---|---:|---|
| INMP441 BCLK / SCK | GPIO4 | I²S bit clock |
| INMP441 WS / LRCLK | GPIO5 | I²S word select |
| INMP441 SD | GPIO3 | I²S data input |
| INMP441 L/R | GND | Select left channel |
| I²C SDA | GPIO0 | Shared expansion bus |
| I²C SCL | GPIO1 | Shared expansion bus |
| DHT11 data | GPIO10 | 3.3 V logic; use an appropriate pull-up |
| PIR output | GPIO6 | Verify the PIR output is 3.3 V-compatible |
| Ultrasonic TRIG | GPIO7 | Trigger output |
| Ultrasonic ECHO | GPIO2 | **Only through a boot-safe 3.3 V buffer/level-shifter circuit**; see restrictions below |
| UART0 RX (debug) | GPIO20 | External UART adapter TX connects here |
| UART0 TX (debug) | GPIO21 | External UART adapter RX connects here |
| USB debugging/programming | Native USB connector | Uses the chip's USB Serial/JTAG interface; preserve the USB data path |

### I²C expansion devices

The remaining peripherals cannot all be connected directly while retaining I²S, USB, UART debugging, and safe boot pins. Use an I²C expansion bus on GPIO0/GPIO1:

| Device | Suggested interface | Example allocation |
|---|---|---|
| Four push buttons | MCP23017 GPIO expander | GPA0–GPA3; address 0x20 (A0–A2 low) |
| LDR analog output | ADS1115 external ADC | AIN0; configure address 0x49 |
| MQ sensor analog output | ADS1115 external ADC | AIN1; configure address 0x49 |
| GPS UART | SC16IS752 I²C-to-dual-UART bridge | One UART channel; select an address that does not conflict with the other bus devices |

The example addresses must be checked against the exact breakout-board address straps before assembly. Keep all I²C pull-ups at 3.3 V. The ADS1115 input must remain within its supply/input limits; add a divider or suitable analog conditioning for an MQ module whose analog output can exceed 3.3 V. MQ sensors also require their specified heater supply and warm-up time.

### Reserved pins and electrical restrictions

- GPIO2, GPIO8, and GPIO9 are ESP32-C3 strapping pins. Keep GPIO8 and GPIO9 unconnected to external loads in this design.
- GPIO2 is used only for ultrasonic ECHO with a boot-safe buffer that guarantees the required reset-time strap level and prevents the sensor from driving the pin during reset. If that circuit is not implemented and verified, leave GPIO2 unused and use a different ultrasonic interface.
- GPIO18/GPIO19 are the native USB D-/D+ signals. Do not attach external peripherals to them.
- GPIO11–GPIO17 are associated with flash connectivity on the chip/module; do not allocate them to external peripherals.
- GPIO4–GPIO7 also have JTAG multiplexed functions. This map uses them as GPIO/I²S; external JTAG debugging is therefore not part of this configuration.
- GPIO20/GPIO21 are reserved for UART0 debugging. GPS must use the I²C-to-UART bridge in this allocation; do not connect GPS directly to the debug UART.
- All ESP32-C3 GPIOs are 3.3 V logic. Never apply 5 V to a GPIO. For a typical 5 V HC-SR04 module, level-shift ECHO before it reaches GPIO2.
- Power the INMP441 from 3.3 V and connect grounds. Do not add RC filters to the digital I²S signal lines. Place local supply decoupling close to the microphone module.

### Expansion header recommendation

Expose 3V3, GND, GPIO0 (SDA), GPIO1 (SCL), and a clearly labelled I²C connector/header for add-on boards. Keep the microphone and direct timing-sensitive sensor connections short. Document the I²C address straps and analog input conditioning in the wiring diagram/BOM.

### Debug configuration

- USB: native USB Serial/JTAG for flashing and USB serial monitoring, subject to the exact board's USB routing and boot mode.
- UART: UART0 on GPIO20 (RX) and GPIO21 (TX), 3.3 V TTL only. Use a 3.3 V USB-UART adapter; do not connect RS-232 voltage levels.
- USB and UART debugging can remain available together because GPS is moved to the I²C UART bridge.

### Validation required before marking this map final for hardware

1. Record the exact board revision and confirm the GPIO labels against its schematic.
2. Verify native USB flashing/monitoring and UART0 logging independently.
3. Confirm I²S capture on GPIO4/GPIO5/GPIO3 and validate channel selection and sample alignment.
4. Test boot/reset repeatedly with the ultrasonic buffer attached to GPIO2; verify the strap level at reset.
5. Scan the I²C bus and confirm the MCP23017, ADS1115, and SC16IS752 addresses do not collide.
6. Validate analog scaling for both LDR and MQ outputs and confirm no ADC input exceeds its permitted range.
7. Test all four buttons, GPS reception, DHT11, PIR, and ultrasonic timing together.
8. Run sustained audio streaming with all expansion devices active and record noise, packet loss, latency, and current.

Do not treat the table as physically verified until these checks pass on the actual board. If the selected SuperMini revision does not expose one of the listed GPIOs, revise the map against that board's schematic before wiring.


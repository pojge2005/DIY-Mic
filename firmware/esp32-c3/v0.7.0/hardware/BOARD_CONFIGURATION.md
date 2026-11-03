# ESP32-C3 Board Configuration

## Target board

- Board family: ESP32-C3 Super Mini.
- SoC: ESP32-C3.
- Previous chip detection in project logs: ESP32-C3 revision 0.4, 4 MB flash, 40 MHz crystal, 160 MHz CPU.
- These log values describe the previously connected board and must be rechecked on the exact V0.7.0 board.

## Wireless capability

- Wi-Fi: 2.4 GHz 802.11 b/g/n.
- Bluetooth: Bluetooth LE (BLE).
- Bluetooth Classic: not supported.
- A2DP and Bluetooth LE Audio: not available as native ESP32-C3 audio profiles.

The C3 uses one 2.4 GHz radio for Wi-Fi and BLE coexistence. Keep Wi-Fi disabled in the first BLE mode. If both radios are tested together later, measure connection stability and throughput.

## Development power and serial

- Use USB-C power for first bring-up.
- Use the board's regulated 3.3 V rail for the microphone only after verifying the physical board.
- USB Serial/JTAG behavior depends on board configuration and firmware build flags.
- V0.6 logs recorded a successful build/upload using PlatformIO Espressif32 platform 6.10.0, board definition `esp32-c3-devkitm-1`, Arduino framework, C++17, and USB CDC build flags. This is historical evidence, not yet the approved V0.7.0 project configuration.

## Pin allocation proposal

| ESP32-C3 GPIO | INMP441 connection | Status |
|---:|---|---|
| GPIO3 | SD / data to MCU | Proposed; verify boot behavior |
| GPIO4 | SCK / BCLK | Proposed |
| GPIO5 | WS / LRCLK | Proposed |
| 3V3 | VDD | Verify rail |
| GND | GND | Required common ground |
| GND | L/R | Select left channel |

Do not assume every Super Mini clone has identical pin labels or regulator layout. GPIO3/4/5 are the existing repository's proposed mapping; validate on the actual board before wiring.

## Reserved and avoid-by-default pins

- GPIO2, GPIO8 and GPIO9 have strapping/board-function considerations.
- GPIO18/19 are native USB D-/D+ on the chip and should be preserved for USB where applicable.
- GPIO20/21 are UART0 RX/TX.
- GPIO11–17 are associated with flash interface functions on the chip and should not be repurposed without checking the exact module.

## Not included in first hardware revision

No OLED, push buttons, external sensors, battery charger, battery, external ADC or GPIO expander. Add hardware only after the microphone and wireless path are stable.

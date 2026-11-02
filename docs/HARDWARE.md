# Hardware and Wiring

## Components

- NodeMCU ESP8266 development board
- INMP441 I²S MEMS microphone
- Optional 100 nF decoupling capacitor placed close to the microphone supply pins

## Wiring

| INMP441 pin | NodeMCU pin | ESP8266 GPIO |
|---|---|---:|
| VDD | 3V3 | 3.3 V |
| GND | GND | GND |
| SCK / BCLK | D7 | GPIO13 |
| WS / LRCLK | D5 | GPIO14 |
| SD | D6 | GPIO12 |
| L/R | GND | Left channel selection |

**Power:** Supply the INMP441 from 3.3 V. Do not connect its VDD pin to 5 V.

## Data Path

The microphone outputs I²S digital audio. The ESP8266 reads the I²S data, converts the selected samples into PCM, and sends audio packets over a WebSocket connection.

## Board and Tooling Notes

- Board: NodeMCU ESP8266 (PlatformIO `nodemcuv2`)
- Framework: Arduino
- PlatformIO Core: 6.2.0
- ESP8266 platform: 4.2.1
- ESP8266 Arduino core: 3.1.2

The board and core versions are recorded from the development environment and should be rechecked when reproducing the build.

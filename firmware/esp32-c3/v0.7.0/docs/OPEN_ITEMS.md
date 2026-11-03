# Open Items Before Firmware Coding

## Hardware details already recorded

- ESP32-C3 SuperMini with 4 MB flash.
- INMP441 microphone breakout.
- Accepted proposed wiring:
  - INMP441 VDD → ESP32 3V3.
  - INMP441 GND → ESP32 GND.
  - SCK/BCLK → GPIO4.
  - WS/LRCLK → GPIO5.
  - SD → GPIO3.
  - L/R → GND.
- The pin mapping was accepted, but physical wiring has not been explicitly verified.

## Items to close

### Hardware
- Confirm exact SuperMini manufacturer/revision and board silkscreen.
- Check whether INMP441 breakout includes local decoupling, SD pull-down and CHIPEN support.
- Verify the actual GPIO wiring against the diagram.
- Confirm USB CDC serial behavior on the board.

### Receiver and network
- Confirm the Android phone/browser target.
- Confirm Ubuntu/PC browser target.
- Decide whether ESP32 serves the receiver page or receiver is hosted separately.
- Confirm whether Android stays connected to a no-internet SoftAP during streaming.
- Decide single-client or multi-client behavior for initial version.

### Audio
- Approve or change the proposed 16 kHz / 16-bit / mono starting format.
- Define acceptable audio quality and latency after initial measurements.
- Confirm whether waveform/FFT visualization is wanted; it is not currently a confirmed requirement.
- Confirm whether background/locked-screen playback is needed.

### Protocol and security
- Select SoftAP SSID and credential provisioning method.
- Select local IP, WebSocket port and path.
- Freeze binary frame header and control messages.
- Define disconnect and reconnect behavior.
- Require WPA2 or explicitly document a different local AP security decision.

### Toolchain
- Confirm installed PlatformIO Core version.
- Confirm ESP32 platform and Arduino core versions.
- Confirm correct PlatformIO board ID for this SuperMini revision.
- Select I²S driver API compatible with pinned framework.

## Release gate

Do not freeze the final sample rate, frame layout, buffer sizes, task priorities or network configuration until the relevant hardware and end-to-end tests pass.
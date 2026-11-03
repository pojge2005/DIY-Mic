# Open Items Before Firmware Coding

The following must be resolved or explicitly accepted as experimental before implementation.

## Hardware
- Confirm exact ESP32-C3 Super Mini manufacturer/revision and board photographs.
- Confirm the INMP441 breakout board and whether it includes local 100 nF decoupling, SD pull-down and CHIPEN wiring.
- Physically verify GPIO3 (SD), GPIO4 (BCLK), GPIO5 (WS), 3V3, GND and L/R.
- Confirm USB CDC serial behavior on the exact board.
- Confirm whether any other hardware is physically attached.

## Audio requirements
- Approve the first 16 kHz / 16-bit / mono benchmark.
- Agree a practical end-to-end latency target and acceptable audio quality.
- Decide whether speech-only bandwidth is sufficient for the first release.
- Confirm whether audio playback must work with the phone screen locked/backgrounded; browser limitations may affect this.

## Receiver
- Confirm target Android phone/browser versions.
- Confirm target Ubuntu browser.
- Decide whether a native Android application is acceptable later if Web Bluetooth browser behavior is insufficient.
- Decide whether Windows and iOS are required for V0.7.0 or deferred.

## BLE protocol
- Select service and characteristic UUIDs.
- Measure negotiated MTU and usable notification payload.
- Choose frame header and fragmentation format.
- Select connection parameters and PHY strategy based on tests.
- Define pairing/security expectations.
- Define reconnect and stream restart behavior.

## Toolchain
- Confirm installed PlatformIO version.
- Confirm ESP32 platform and Arduino core versions.
- Confirm the correct PlatformIO board ID for the Super Mini.
- Select the I²S driver API compatible with the pinned framework version.

## Release gate
Do not freeze the binary protocol, final sample rate, buffer sizes, task priorities, or Wi-Fi coexistence behavior before the relevant hardware tests.

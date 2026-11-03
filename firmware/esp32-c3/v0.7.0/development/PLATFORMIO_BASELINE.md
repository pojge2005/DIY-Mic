# PlatformIO Baseline — Pre-Implementation

## Existing development environment

The repository's development notes record Ubuntu 26.04.1 LTS, VS Code and PlatformIO. Project logs also record PlatformIO Core 6.2.0.

## Historical V0.6 build configuration

The V0.6 build logs show:
- Platform: `espressif32@6.10.0`
- Board definition: `esp32-c3-devkitm-1`
- Framework: Arduino
- C++ standard: C++17
- Monitor speed: 115200
- Upload speed: 460800
- USB CDC build flags used to resolve missing Serial declarations and enable USB serial behavior.

This configuration compiled and uploaded in the earlier experiment. It is not automatically the correct or final configuration for the exact Super Mini board.

## Before creating platformio.ini

1. Confirm PlatformIO Core version.
2. Confirm the exact board and correct PlatformIO board ID.
3. Confirm the selected Espressif32 platform and Arduino core.
4. Confirm USB CDC configuration and serial port.
5. Confirm whether the current framework uses the legacy I²S driver or the newer channel API.
6. Pin versions rather than using floating latest dependencies.
7. Build an empty serial-only project before adding microphone or BLE code.

## Expected initial build scope

The first project build should contain only:
- PlatformIO configuration.
- One minimal main source.
- Board configuration.
- Serial/chip diagnostics.

No I²S, BLE, Wi-Fi, audio processing or receiver implementation should be added until the board baseline passes.

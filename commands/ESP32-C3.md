# ESP32-C3 Command Guide

**Target:** ESP32-C3 Super Mini + INMP441 development track.

## Current command evidence

The repository history identifies the ESP32-C3 V0.7.0 development track, but this command library has not yet verified its current local `platformio.ini`, exact environment name, serial port, or successful build/upload transcript.

Do not copy ESP8266 or ESP32-S3 board settings into the ESP32-C3 project.

## Safe project inspection

From Ubuntu Terminal, first open the repository and inspect the project files:

```bash
cd ~/Projects/DIY-Mic
find firmware/esp32-c3 -maxdepth 4 -type f -print
```

**Purpose:** list the existing ESP32-C3 project files.  
**Use case:** locate the active firmware directory and its `platformio.ini` before running PlatformIO.

After locating the actual project directory, change into that directory and inspect its configuration:

```bash
pio project config
pio --version
pio device list
```

Do not run `pio run` or `pio run -t upload` until the correct project directory and environment have been identified from the actual configuration.

## Required before expanding this guide

- Confirm the active ESP32-C3 project path and environment name.
- Record PlatformIO Core and Espressif platform versions.
- Record the board identifier and flash configuration.
- Capture the exact build command and output.
- Capture the upload command and serial monitor output.
- Verify the GPIO map against the actual ESP32-C3 Super Mini revision.

Once these details are available, add the exact commands and logs here. The ESP32-C3 implementation remains separate from the ESP32-S3 track.

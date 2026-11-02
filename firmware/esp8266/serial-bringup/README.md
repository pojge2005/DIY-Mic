# ESP8266 Serial Bring-up Test

This is a minimal PlatformIO project for checking the ESP8266 build toolchain, USB upload path, and serial monitor.

## Hardware

- NodeMCU ESP8266.
- USB data cable.
- No microphone is required for this test.

## Commands

Run from this directory:

```bash
pio run
pio run -t upload
pio device monitor --baud 115200
```

If needed, specify the serial port:

```bash
pio run -t upload --upload-port /dev/ttyACM0
pio device monitor --port /dev/ttyACM0 -b 115200
```

Expected output:

```text
DIY-Mic ESP8266 serial bring-up test
Board and serial monitor are running.
```

This project does not configure I²S, read the INMP441, stream audio, or replace the owner-tested V0.5 firmware. It must be built and tested on the target board before its status is marked verified.

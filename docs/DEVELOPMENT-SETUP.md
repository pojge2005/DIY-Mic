# DIY-Mic Development Setup

This guide records the development environment and repeatable commands used for the current ESP8266 prototype work. It is written for Ubuntu and Visual Studio Code.

## 1. Current development environment

| Component | Recorded environment |
|---|---|
| Operating system | Ubuntu 26.04.1 LTS |
| Kernel | 7.0.0-38-generic |
| Editor | Visual Studio Code |
| Embedded IDE | PlatformIO IDE extension |
| PlatformIO Core | 6.2.0 |
| ESP8266 platform | 4.2.1 |
| Arduino ESP8266 core | 3.1.2 |
| Board | NodeMCU ESP8266 / `nodemcuv2` |
| Toolchain | xtensa 2.100300.220621 |
| Microphone | INMP441 I²S MEMS |

Versions above describe the previously used development setup. Recheck installed versions before reproducing a build.

## 2. Install system tools

```bash
sudo apt update
sudo apt install -y git python3 python3-venv python3-pip curl unzip
```

Install Visual Studio Code using the official instructions:

- https://code.visualstudio.com/docs/setup/linux

Install the PlatformIO IDE extension:

1. Open VS Code.
2. Open Extensions.
3. Search for **PlatformIO IDE**.
4. Install the official PlatformIO IDE extension.
5. Reload VS Code if requested.

Optional terminal installation:

```bash
code --install-extension platformio.platformio-ide
```

Check that the command-line tools are available:

```bash
git --version
python3 --version
pio --version
```

If `pio` is not available in the terminal, open the PlatformIO terminal in VS Code or install PlatformIO Core in a Python virtual environment. Avoid installing Python packages globally into an OS-managed Python environment.

## 3. Clone and open the repository

```bash
mkdir -p ~/Projects
cd ~/Projects
git clone https://github.com/pojge2005/DIY-Mic.git
cd DIY-Mic
code .
```

To update an existing clone:

```bash
cd ~/Projects/DIY-Mic
git pull
```

## 4. ESP8266 PlatformIO project

The repository contains a minimal serial bring-up project at:

`firmware/esp8266/serial-bringup/`

Open that folder as a PlatformIO project or use the VS Code terminal:

```bash
cd ~/Projects/DIY-Mic/firmware/esp8266/serial-bringup
pio project config
pio run
```

The project uses this configuration:

```ini
[env:nodemcuv2]
platform = espressif8266@4.2.1
board = nodemcuv2
framework = arduino
monitor_speed = 115200
upload_speed = 115200
```

The serial bring-up firmware only checks compilation, upload, and serial output. It does **not** capture INMP441 audio and is not the V0.5 live streaming firmware.

## 5. Identify the serial port

Connect the NodeMCU over USB, then run:

```bash
pio device list
ls -l /dev/ttyACM* /dev/ttyUSB* 2>/dev/null
dmesg --follow
```

The previously used device was `/dev/ttyACM0`, but the port can change depending on the USB interface and connected devices.

If permission is denied, inspect the device group:

```bash
ls -l /dev/ttyACM0
groups
```

On Ubuntu systems where the serial device belongs to the `dialout` group, add the current user:

```bash
sudo usermod -aG dialout "$USER"
```

Log out and log back in for the group change to take effect. Do not run PlatformIO as root as a routine workaround.

## 6. Build, upload, and monitor

Run these commands from the folder containing `platformio.ini`:

```bash
pio run
pio run -t clean
pio run -t upload
pio device monitor --baud 115200
```

Specify the port when automatic detection does not select the correct device:

```bash
pio run -t upload --upload-port /dev/ttyACM0
pio device monitor --port /dev/ttyACM0 -b 115200
```

Expected serial output from the serial bring-up test:

```text
DIY-Mic ESP8266 serial bring-up test
```

Exit the serial monitor with `Ctrl+C`.

## 7. Run the host-side audio tests

The test utilities use only the Python standard library. No third-party Python packages are required.

From the repository root:

```bash
python3 -m unittest discover -s tests -p 'test_*.py' -v
```

Inspect a raw signed 16-bit little-endian mono PCM file:

```bash
python3 tests/tools/pcm_inspect.py capture.pcm --sample-rate 16000
```

The sample rate in this command must match the rate used to create the PCM file. The tool does not decode WebSocket packets or extract audio from a firmware stream.

## 8. VS Code workspace

Recommended extensions are listed in `.vscode/extensions.json`. Open the repository root with `code .` so that documentation, tests, firmware projects, and diagrams are visible in one workspace.

Useful VS Code actions:

- Open **Terminal → Run Task** to run the repository tasks.
- `DIY-Mic: Build ESP8266` builds the serial bring-up project.
- `DIY-Mic: Upload ESP8266` uploads it to the connected board.
- `DIY-Mic: Monitor ESP8266` opens the 115200 baud serial monitor.
- `DIY-Mic: Run Python tests` runs the host-side unit tests.
- Use Source Control to review local changes before committing.

## 9. Current hardware wiring reference

The current ESP8266 prototype uses NodeMCU ESP8266 + INMP441:

| INMP441 | NodeMCU pin | ESP8266 GPIO |
|---|---|---:|
| VDD | 3V3 | 3.3 V |
| GND | GND | GND |
| SCK / BCLK | D7 | GPIO13 |
| WS / LRCLK | D5 | GPIO14 |
| SD | D6 | GPIO12 |
| L/R | GND | Left channel |

Use 3.3 V for the INMP441. Do not connect its supply to 5 V.

See [Hardware](HARDWARE.md) and the wiring image at `hardware/diagrams/esp8266-inmp441-wiring.png`.

## 10. Known project state and limitations

- The owner reports that the ESP8266 + INMP441 + Wi-Fi/WebSocket + Android browser V0.5 prototype works.
- The exact owner-tested V0.5 firmware and webpage source have not yet been imported into this repository.
- The serial bring-up project is a toolchain test only.
- The ESP32-C3 SuperMini pin mapping is proposed and must be checked against the exact board revision.
- Do not treat the host-side PCM utility as proof of microphone hardware operation.
- Record board revision, firmware revision, sample format, power source, and test conditions for every hardware test.

## 11. Development workflow

1. Read the relevant hardware and architecture documentation.
2. Create a focused branch for each implementation change.
3. Build before uploading firmware.
4. Run host-side tests after changing test utilities or protocol code.
5. Test on hardware and record actual results separately from software test results.
6. Review `git diff` before committing.
7. Update the experiment log and test results only with observations that were actually made.

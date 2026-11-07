# ESP32-S3 Command Guide

**Target:** reported ESP32-S3 N16R8 + INMP441, advertised as `DIY-Mic-S3`.  
**Observed BLE address:** `30:ED:A0:A8:A4:F0`.  
**Host:** Ubuntu with BlueZ and PlatformIO.

The exact carrier-board model is unknown. GPIO4/5/6 is a provisional INMP441 proposal, not a verified wiring assignment.

## 1. Check PlatformIO

Run in Ubuntu Terminal from the ESP32-S3 firmware project directory (the directory containing `platformio.ini`):

| Command | Purpose | Use case |
|---|---|---|
| `pio --version` | Print PlatformIO Core version | Record toolchain version |
| `pio boards esp32-s3` | List ESP32-S3 board definitions | Identify candidate board presets; do not assume N8/N8R2 matches N16R8 |
| `pio project config` | Print resolved project configuration | Verify flash, PSRAM, framework, and build settings |
| `pio device list` | List serial devices | Identify the upload/monitor port |
| `pio run` | Compile firmware without uploading | Catch compile/configuration errors |
| `pio run -t upload` | Build and upload firmware | Flash the selected target |
| `pio device monitor -b 115200` | Open serial monitor at 115200 baud | Inspect boot and runtime logs |
| `pio run -t clean` | Remove generated build output | Clean before a diagnostic rebuild |

The repository documentation records these as useful commands. The supplied session does not prove that every command was executed successfully. Do not run build/upload commands until a matching ESP32-S3 `platformio.ini` exists and its memory settings are verified.

## 2. Start BlueZ

Run in Ubuntu Terminal:

```bash
bluetoothctl
```

The prompt changes to a Bluetooth prompt. The following commands are entered **inside `bluetoothctl`**, not in the normal shell.

| Command | Purpose | Use case |
|---|---|---|
| `power on` | Enable the host Bluetooth adapter | Before scanning |
| `agent on` | Enable BlueZ pairing/security agent | Prepare the adapter |
| `default-agent` | Set the default agent | Handle security prompts |
| `scan on` | Discover nearby devices | Find the microphone |
| `devices` | List discovered devices | Confirm the advertised peripheral |
| `connect 30:ED:A0:A8:A4:F0` | Connect to the observed device address | Establish BLE connection |
| `menu gatt` | Enter GATT menu | Inspect services/characteristics |
| `list-attributes` | List GATT object paths and attributes | Resolve current characteristic paths |
| `back` | Return to the previous menu | Leave GATT menu |
| `disconnect 30:ED:A0:A8:A4:F0` | Disconnect the peripheral | End the test |
| `quit` | Exit BlueZ CLI | Return to Ubuntu shell |

If the device address changes, use the address shown by the current scan. BlueZ object paths can change after reconnecting; resolve them again with `list-attributes`.

## 3. Read the Status characteristic

**Characteristic UUID:** `7b3a0002-6d7b-4f21-9a11-6e4d594d4943`  
**Observed path in the supplied session:**

```text
/org/bluez/hci0/dev_30_ED_A0_A8_A4_F0/service000e/char000f
```

Inside `bluetoothctl`:

```text
menu gatt
list-attributes
select-attribute /org/bluez/hci0/dev_30_ED_A0_A8_A4_F0/service000e/char000f
read
```

**Purpose:** read the peripheral's current status.  
**Use case:** confirm that the host can access the Status characteristic after connecting.

**Recorded output:**

```text
43 4f 4e 4e 45 43 54 45 44
CONNECTED
```

This is a confirmed Status read only. It does not prove Control writes or audio transport.

## 4. Test the Control characteristic

**Characteristic UUID:** `7b3a0003-6d7b-4f21-9a11-6e4d594d4943`  
**Observed path in the supplied session:**

```text
/org/bluez/hci0/dev_30_ED_A0_A8_A4_F0/service000e/char0012
```

Inside `bluetoothctl`:

```text
select-attribute /org/bluez/hci0/dev_30_ED_A0_A8_A4_F0/service000e/char0012
write 50 49 4e 47
```

**Purpose:** write ASCII `PING` to the Control characteristic.  
**Use case:** verify host-to-device command delivery.

Expected response is `PONG`, but the supplied log does not contain a successful response. Keep this test PENDING until the actual response and its characteristic are captured.

If Status supports notifications, test them separately:

```text
select-attribute /org/bluez/hci0/dev_30_ED_A0_A8_A4_F0/service000e/char000f
notify on
```

Do not assume Status supports notifications; inspect the live GATT properties. Record which characteristic returns any PONG response.

## 5. Subscribe to Audio notifications

**Audio UUID:** `7b3a0004-6d7b-4f21-9a11-6e4d594d4943`.

Inside `bluetoothctl`, find the current Audio object path with `list-attributes`, then run:

```text
select-attribute <AUDIO_CHARACTERISTIC_OBJECT_PATH>
notify on
```

**Purpose:** subscribe to device-to-host Audio notifications.  
**Use case:** check whether the peripheral sends audio data to the host.

A successful `notify on` only confirms subscription setup. It does not prove that payloads are transmitted. The earlier notes state that audio streaming was disabled during the control-channel test. The exact audio-start command is not established; do not invent or send a guessed command.

## 6. Run the Python BLE utility

Run from the repository root:

```bash
python3 -m venv .venv
source .venv/bin/activate
python3 -m pip install -r ESP32-S3/tests/tools/requirements.txt
python3 ESP32-S3/tests/tools/ble_notify_test.py --address 30:ED:A0:A8:A4:F0 --listen-seconds 10
```

| Command/option | Purpose | Use case |
|---|---|---|
| `python3 -m venv .venv` | Create isolated Python environment | Keep dependencies out of system Python |
| `source .venv/bin/activate` | Activate the environment | Use its installed packages |
| `python3 -m pip install -r .../requirements.txt` | Install Bleak | Enable Python BLE access |
| `--address` | Select peripheral address | Target the correct board |
| `--listen-seconds 10` | Set notification listening duration | Capture notifications for a bounded interval |

The script reads Status, subscribes to Status and Audio if the live properties permit it, writes `PING` to Control, and prints notifications. It does not send an undocumented audio-start command.

## 7. Save evidence

After each test, save the exact command and complete output under [commands/logs](logs/README.md). Record the date/time, board marking, firmware commit, host/tool versions, characteristic UUID, and result. Update [BLE Test Report](../ESP32-S3/docs/BLE_TEST_REPORT.md) only after reviewing the raw log.

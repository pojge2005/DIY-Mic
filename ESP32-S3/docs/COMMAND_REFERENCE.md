# ESP32-S3 Command Reference

Commands are separated by execution environment. Shell commands run in Ubuntu Terminal. BlueZ commands run inside the interactive `bluetoothctl` prompt.

## 1. PlatformIO and serial commands

Run in Ubuntu Terminal:

| Command | Purpose |
|---|---|
| `pio --version` | Show installed PlatformIO Core version |
| `pio boards esp32-s3` | List ESP32-S3 board definitions |
| `pio project config` | Print resolved PlatformIO project settings |
| `pio device list` | List connected serial devices |
| `pio run` | Compile the selected firmware environment; no upload |
| `pio run -t upload` | Build and upload firmware to the configured board |
| `pio device monitor -b 115200` | Open serial monitor at 115200 baud |
| `pio run -t clean` | Remove generated build output |

The project previously used `pio run -t upload` and `pio device monitor`. The remaining commands are documented diagnostics; this document does not claim they were already executed.

## 2. Start Bluetooth control

In Ubuntu Terminal:

```bash
bluetoothctl
```

The prompt changes to `[bluetooth]#`. Enter the following inside that prompt:

| bluetoothctl command | Purpose |
|---|---|
| `power on` | Enable Bluetooth adapter |
| `agent on` | Enable the security agent |
| `default-agent` | Set the default agent |
| `scan on` | Discover nearby BLE devices |
| `devices` | List discovered devices |
| `connect 30:ED:A0:A8:A4:F0` | Connect to the observed DIY-Mic-S3 address |
| `menu gatt` | Enter GATT attribute menu |
| `list-attributes` | List discovered services and characteristics |
| `back` | Return to previous menu |
| `disconnect 30:ED:A0:A8:A4:F0` | Disconnect peripheral |
| `quit` | Exit bluetoothctl |

The observed address is `30:ED:A0:A8:A4:F0`. If it is not found, scan again and use the address actually reported by the adapter.

## 3. Read Status

The supplied session recorded this Status object path:

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

Purpose: read the device's BLE status.

Recorded response:

```text
43 4f 4e 4e 45 43 54 45 44
CONNECTED
```

BlueZ object paths may change after reconnecting or firmware changes. Confirm the UUID in the current `list-attributes` output before selecting a path.

## 4. PING/PONG control test

The supplied session recorded this Control object path:

```text
/org/bluez/hci0/dev_30_ED_A0_A8_A4_F0/service000e/char0012
```

Select it and write PING:

```text
select-attribute /org/bluez/hci0/dev_30_ED_A0_A8_A4_F0/service000e/char0012
write 50 49 4e 47
```

Hex-to-ASCII mapping: `50=P`, `49=I`, `4e=N`, `47=G`.

Expected firmware response: `PONG`. This response is not yet confirmed by captured test output.

If Status supports notifications, select Status and enable them before writing PING:

```text
select-attribute /org/bluez/hci0/dev_30_ED_A0_A8_A4_F0/service000e/char000f
notify on
```

Then select Control and write PING. Record which characteristic returns PONG. If Status does not expose `notify`, inspect the actual GATT properties and firmware response path instead of assuming it.

## 5. Audio notification test

Find the characteristic with this UUID using `list-attributes`:

```text
7b3a0004-6d7b-4f21-9a11-6e4d594d4943
```

Select its current BlueZ object path:

```text
select-attribute <AUDIO_CHARACTERISTIC_OBJECT_PATH>
notify on
```

Purpose: subscribe to device-to-host audio notifications.

Important:
- Successful `notify on` confirms subscription setup only; it does not prove audio payloads are being sent.
- The earlier test notes state audio streaming was disabled during control-channel testing.
- The exact firmware audio-start command has not been established in the available source evidence. Do not guess a `START` command.
- Record notification timestamps, payload lengths, and bytes.
- Document sample rate, channels, bit depth, byte order, packet framing, and sequence behavior before playback.

## 6. Python BLE test utility

Run from the repository root:

```bash
python3 -m venv .venv
source .venv/bin/activate
python3 -m pip install -r ESP32-S3/tests/tools/requirements.txt
python3 ESP32-S3/tests/tools/ble_notify_test.py --address 30:ED:A0:A8:A4:F0 --listen-seconds 10
```

| Command / option | Purpose |
|---|---|
| `python3 -m venv .venv` | Create isolated Python environment |
| `source .venv/bin/activate` | Activate environment in current shell |
| `pip install -r .../requirements.txt` | Install Bleak dependency |
| `--address` | Select BLE peripheral |
| `--listen-seconds 10` | Set notification listening period |

The script reads Status, subscribes to Status and Audio when supported, writes PING to Control, and prints received data as hex and ASCII. It does not send an undocumented audio-start command.

## 7. Evidence capture

For every test, record date/time, board marking, firmware commit, host/BlueZ version, command, characteristic UUID/path, full output, and PASS/FAIL/BLOCKED result.

Do not mark expected behavior as PASS. Update `BLE_TEST_REPORT.md` only after reviewing actual command output.

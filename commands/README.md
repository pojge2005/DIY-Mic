# DIY-Mic Command Library

This folder is the central index for repeatable terminal commands used by the project. Each command guide identifies where to run a command, what it does, when to use it, and what evidence to save.

## Command guides

| Guide | Scope |
|---|---|
| [ESP32-S3](ESP32-S3.md) | PlatformIO diagnostics, BlueZ BLE discovery/GATT tests, Python BLE utility |
| [ESP8266](ESP8266.md) | PlatformIO serial bring-up and the historical Wi-Fi prototype context |
| [ESP32-C3](ESP32-C3.md) | Current command availability and safe bring-up checklist |
| [Host tests](HOST-TESTS.md) | Python unit tests and raw PCM inspection |
| [Git workflow](GIT.md) | Branch, status, diff, commit, and push commands |
| [Logs](logs/README.md) | How to capture and store terminal output |

## Execution locations

- **Ubuntu Terminal:** commands in `bash` blocks.
- **Inside `bluetoothctl`:** commands are entered only after running `bluetoothctl` in Ubuntu Terminal.
- **Repository root:** paths are relative to the top-level `DIY-Mic/` folder unless the guide says otherwise.
- **Firmware project directory:** PlatformIO commands must be run from the directory containing the relevant `platformio.ini`.

## Evidence rules

1. Copy the complete command and its output, including errors.
2. Record the date, board marking, firmware commit, host OS, and tool version.
3. Mark a result PASS only when the expected behavior appears in captured output or a measured test.
4. Use FAIL for a reproduced failure and BLOCKED when hardware, source, or prerequisites are missing.
5. Never replace an older raw log; add a new dated log file.
6. Remove passwords, access tokens, Wi-Fi credentials, and other secrets before committing logs.

The command guides distinguish commands documented for use from commands confirmed as executed. A command being listed does not mean it has already passed.

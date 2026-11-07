# Project Terminal Logs

Store raw command transcripts in this folder. Keep the original output intact except for removing secrets and personal identifiers.

## Naming convention

Use:

```text
YYYY-MM-DD_<board-or-area>_<test-name>.log
```

Examples:

- `2026-11-06_esp32-s3_ble-status-read.log`
- `2026-11-07_esp8266_serial-bringup.log`
- `2026-11-07_host_python-tests.log`

## Capture a command transcript

For shell commands, use `tee` to show output and save a copy:

```bash
command 2>&1 | tee commands/logs/YYYY-MM-DD_area_test-name.log
```

Replace `command` and the filename with the actual command and date. For multi-command sessions, group commands in a shell block or save the terminal transcript using the terminal application's export/copy feature.

For interactive `bluetoothctl` sessions, save the complete terminal output after exiting the session. Do not pipe the interactive prompt through `tee` unless the terminal behavior has been checked.

## Required log metadata

Each log should state:

- Date and local time.
- Host OS and relevant tool versions.
- Board name/marking and firmware commit, if known.
- Exact command(s), including the directory or prompt where they ran.
- Complete stdout/stderr.
- Result: PASS, FAIL, or BLOCKED.
- Short interpretation and next action.

## Result definitions

- **PASS:** observed output meets the stated test condition.
- **FAIL:** the test ran and the observed result did not meet the condition.
- **BLOCKED:** the test could not be completed because a prerequisite or required evidence is missing.
- **NOT TESTED:** no test execution has occurred.

Do not add fabricated or reconstructed terminal output. A report may summarize a raw log, but the log must represent actual captured output.

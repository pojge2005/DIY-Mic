# ESP32-S3 BLE Status Read — Supplied Session Evidence

- Date: 2026-11-06 (chip identification date; exact BLE test timestamp was not recorded).
- Peripheral name: `DIY-Mic-S3`.
- Observed BLE address in the documentation: `30:ED:A0:A8:A4:F0`.
- Host: Ubuntu / BlueZ.
- Source: supplied engineering session notes.

## Observed result

The Status characteristic read returned:

```text
43 4f 4e 4e 45 43 54 45 44
CONNECTED
```

Hex bytes decode to ASCII `CONNECTED`.

## What this proves

- The host connected to the peripheral.
- The Status characteristic was accessible for reading.
- The peripheral returned the connection-state string.

## What this does not prove

- Control characteristic write success.
- PING/PONG response.
- Status notifications.
- Audio characteristic subscription or payload delivery.
- I²S microphone capture or audio playback.

## Next recorded test

The supplied notes identify the Control characteristic path as:

```text
/org/bluez/hci0/dev_30_ED_A0_A8_A4_F0/service000e/char0012
```

The next intended command was:

```text
write 50 49 4e 47
```

This writes ASCII `PING`. The expected `PONG` response was not present in the supplied notes, so the result remains PENDING.

The supplied source file also contained a previous object path with a MAC ending in `F1`; the current documentation uses the later observed address ending in `F0`. Always resolve current object paths with `list-attributes` instead of relying on a saved path.

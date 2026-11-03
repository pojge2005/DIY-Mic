# Firmware Architecture Proposal

This is a proposed module map, not an instruction to create every file immediately. Add modules only when the corresponding phase begins.

## Proposed source layout

```text
src/
├── main.cpp
├── audio/
│   ├── microphone.h
│   └── microphone.cpp
├── bluetooth/
│   ├── ble_manager.h
│   ├── ble_manager.cpp
│   ├── ble_audio.h
│   └── ble_audio.cpp
├── streaming/
│   ├── audio_frame.h
│   ├── audio_buffer.h
│   └── audio_buffer.cpp
└── system/
    ├── diagnostics.h
    └── diagnostics.cpp

include/
├── board_config.h
└── audio_config.h
```

Wi-Fi source is deliberately absent from the first BLE implementation. Add a separate optional connectivity module only if the local Wi-Fi experiment is approved.

## Responsibilities

### main
- Initialize serial diagnostics and board services.
- Start microphone and BLE services in a defined order.
- Handle top-level device state and error reporting.

### audio/microphone
- Configure I²S RX.
- Read DMA samples into bounded buffers.
- Report capture errors and overruns.
- No BLE calls and no browser protocol details.

### streaming
- Convert samples into transport PCM.
- Assemble logical frames and sequence numbers.
- Manage bounded queues and frame ownership.
- No direct hardware pin configuration.

### bluetooth
- Advertise and manage GATT.
- Negotiate connection parameters and MTU.
- Expose control, audio and telemetry characteristics.
- Fragment and transmit frames without blocking capture.

### system
- Firmware/build identification.
- Reset reason, heap and task/queue health.
- Error counters and diagnostics.
- Avoid high-rate logging in real-time paths.

## Concurrency

The I²S capture path must not wait for BLE transmission. Use a bounded producer/consumer queue or equivalent fixed-buffer ownership model. Define what happens when the queue is full: count and drop a complete frame rather than corrupting memory or blocking capture.

Task priorities, stack sizes, core affinity and DMA buffer counts must be chosen from actual driver and timing measurements. Do not preselect them without testing.

## Framework and driver policy

Arduino framework with PlatformIO is the existing project development preference. The exact ESP32 platform, Arduino core and I²S API version must be selected and pinned after a minimal board build. Do not mix legacy I²S driver APIs and newer channel APIs without a deliberate version-specific decision.

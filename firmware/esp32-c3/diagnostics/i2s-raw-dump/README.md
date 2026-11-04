# INMP441 I²S Raw Diagnostic

Archived source from 2026-11-04. Uses ESP32-C3, GPIO4 BCLK, GPIO5 WS, GPIO3 SD, 16 kHz configured rate, 32-bit RX slots and left-channel capture.

The diagnostic emits raw words every five seconds and rate/min/max/peak/RMS/clipping counters. The I²S format/alignment and acoustic conditions were not fully validated. See the session report and raw log under logs/2026-11-04/.

# Wiring and Minimum Bill of Materials

## Minimum components

| Item | Qty | Requirement | Status |
|---|---:|---|---|
| ESP32-C3 Super Mini | 1 | Exact revision to be confirmed | Required |
| INMP441 I²S microphone breakout | 1 | Breakout revision and onboard parts to be checked | Required |
| 100 nF X7R capacitor | 0–1 | Fit close to mic VDD/GND only if not already present | Conditional |
| 100 kΩ resistor | 0–1 | SD-to-GND pull-down only if breakout does not already include it | Conditional |
| USB-C cable and suitable USB supply | 1 | Development power | Required |
| Short wires / zero PCB | As needed | Short I²S and supply connections | Required for assembly |

Optional 4.7–10 µF local capacitor should be added only if measurements show a supply transient/ripple problem. Do not add ferrite beads, RC filters or extra regulators by default.

## Proposed point-to-point wiring

| ESP32-C3 Super Mini | INMP441 | Purpose |
|---|---|---|
| 3V3 | VDD | 3.3 V supply only |
| GND | GND | Common ground |
| GPIO4 | SCK / BCLK | I²S bit clock |
| GPIO5 | WS / LRCLK | I²S word select |
| GPIO3 | SD | I²S data input |
| GND | L/R | Left channel |

If the breakout exposes CHIPEN, connect it according to its board design/datasheet. Do not assume it is unconnected or handled internally.

## Electrical constraints

- Never supply the INMP441 from 5 V.
- ESP32-C3 GPIOs are 3.3 V logic; do not apply 5 V to GPIO.
- Keep BCLK, WS, SD, power and ground short.
- Keep the microphone away from the antenna edge and switching/noisy wiring where practical.
- Do not place capacitors or analog RC filters on digital I²S lines.
- Verify the 3.3 V rail with the microphone active.

## Physical assembly

Use USB power during initial tests. Build on zero PCB/perfboard only after the wiring has passed a jumper-wire bring-up. Preserve USB access, antenna clearance and microphone acoustic access. Do not claim a 20 mm assembly target until the actual modules are measured.

## Reference documents

- Existing repository: `docs/ESP32-C3-MINI-CIRCUIT.md`
- Existing wiring image: `hardware/diagrams/esp32-c3-supermini-inmp441-wiring.png`
- Existing minimal circuit SVG: `hardware/diagrams/esp32-c3-minimal-mic.svg`

These existing circuit assets are reference designs. Physical board revision and breakout contents must be checked before treating the wiring as validated.

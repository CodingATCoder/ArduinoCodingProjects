# Four-Servo Snake Robot

Fires four servos in sequence (4 → 3 → 2 → 1) to produce a rippling,
undulating "snake" gait.

## Wiring
See [`wiring_diagram.svg`](wiring_diagram.svg).

| Component | Pin |
|---|---|
| Servo 1 (segment 1) signal | D2 |
| Servo 2 (segment 2) signal | D3 |
| Servo 3 (segment 3) signal | D4 |
| Servo 4 (segment 4) signal | D5 |

## Libraries required
- `Servo` (bundled with the Arduino IDE)

## Fixed from the original code
The original sketch called `servo3.write(-90)` and `servo1.write(-90)`.
`Servo::write()` only accepts **0–180 degrees** — a negative value is out of
range and produces undefined/unreliable servo behavior. This has been changed
to **140 degrees**, which mirrors the 40-degree position symmetrically around
the 90-degree center, so each servo now sweeps cleanly between 40° and 140°.

## Notes
- Power all 4 servos from a dedicated 5–6V supply (not the Uno's 5V pin), and
  tie the grounds together. Four servos moving together can exceed what the
  Uno's onboard regulator can supply, causing brownouts/resets.

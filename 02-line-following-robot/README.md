# Line-Following Robot (2-Servo Steering)

Reads a single IR line sensor and steers two servos in opposite directions to
follow a line: when the line is detected, one servo pair swings one way; when
it's lost, it swings the other way.

An HC-SR04 ultrasonic sensor is already wired and pin-configured (via
`Ultrasonic.h`) for a future obstacle-avoidance addition, but `getUltraSonicDistance()`
isn't called from the control loop yet — it's there for you to wire in later.

## Wiring
See [`wiring_diagram.svg`](wiring_diagram.svg).

| Component | Pin |
|---|---|
| Servo 1 (left) signal | D2 |
| Servo 2 (right) signal | D4 |
| Line sensor digital out | D3 |
| HC-SR04 Trig | D9 |
| HC-SR04 Echo | D8 |

## Files
- `line_detection1servo.ino` — main sketch
- `Ultrasonic.h` — ultrasonic distance helper (included, ready for future use)

## Libraries required
- `Servo` (bundled with the Arduino IDE)

## Notes
- Power the servos from a separate 5–6V supply if the board resets or the servos
  stutter under load — two servos can draw more current than the Uno's onboard
  regulator comfortably supplies.

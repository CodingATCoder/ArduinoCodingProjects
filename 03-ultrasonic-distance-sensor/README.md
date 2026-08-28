# Ultrasonic Distance Sensor (Serial Readout)

A minimal standalone sketch: pulses an HC-SR04 ultrasonic sensor and prints the
measured distance (in cm) to Serial Monitor roughly 5 times a second.

## Wiring
See [`wiring_diagram.svg`](wiring_diagram.svg).

| Component | Pin |
|---|---|
| HC-SR04 Trig | D9 |
| HC-SR04 Echo | D8 |
| HC-SR04 VCC / GND | 5V / GND |

## Serial
Open Serial Monitor at **115200 baud** to see live distance readings.

## Fixed from the original code
The distance formula (`speed_of_sound * duration / 2000.0`) was off by exactly
10x — a 100cm object would read as ~1000cm. Verified numerically: a 100cm-away
object produces a ~5831-microsecond echo pulse; the original formula turned
that into ~1000cm instead of ~100cm. Corrected the divisor to `20000.0`.

## Notes
- `pulseIn(8, HIGH)` has no *explicit* timeout in this sketch, so it falls back
  to Arduino's default of 1 second — it returns `0` rather than hanging forever
  if the sensor is unplugged or nothing is in range, but a shorter explicit
  timeout gives faster, more predictable readings. Consider e.g.
  `pulseIn(8, HIGH, 30000)` (30ms, ≈ 5m max range).

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

## Notes
- `pulseIn(8, HIGH)` has no timeout in this sketch, so it can block indefinitely
  if the sensor is unplugged or nothing is in range to reflect the pulse. For a
  more robust standalone sketch, consider adding a timeout, e.g.
  `pulseIn(8, HIGH, 30000)` (30ms, ≈ 5m max range).

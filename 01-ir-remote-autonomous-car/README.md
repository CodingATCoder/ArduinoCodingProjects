# IR Remote + Autonomous Obstacle-Avoidance Car

An OSOYOO V2.1 robot car controlled two ways:
1. **IR remote** — drive forward/back/left/right, MUTE toggles autonomous mode
2. **Autonomous obstacle avoidance** — a second Arduino reads 4 ultrasonic sensors
   (front/back/left/right) and streams distance readings over a serial link; this
   board steers away from obstacles automatically
3. **Serial commands** — a Raspberry Pi or PC can also drive the car by sending
   single characters (`F`/`B`/`L`/`R`/`S`) over the USB serial connection

## Wiring
See [`wiring_diagram.svg`](wiring_diagram.svg).

| Component | Pin |
|---|---|
| IR receiver signal | D8 |
| IR receiver VCC / GND | 5V / GND |
| Motor driver ENA | D2 |
| Motor driver IN1 | D3 |
| Motor driver IN2 | D4 |
| Motor driver IN3 | D5 |
| Motor driver IN4 | D6 |
| Motor driver ENB | D7 |
| Sensor Arduino link (RX) | D10 |

> **Note:** the code's `LINK_RX` is defined as pin 10. Double-check which pin your
> sensor Arduino's TX line is physically wired to, and keep the `#define` and the
> wiring in agreement.

## Libraries required
- [IRremote](https://github.com/Arminjo/IRremote) (v3.x/v4.x API — `IRremote.hpp`)
- `SoftwareSerial` (bundled with the Arduino IDE)

## Notes
- Pins 2 and 7 don't support true PWM on an Uno, so `ENA`/`ENB` effectively run the
  motors on/off rather than at a finely variable speed.
- Only `BTN_FORWARD`/`BACKWARD`/`LEFT`/`RIGHT`/`MUTE`/`PLAY`/`NEXT`/`MINUS` are
  confirmed IR codes; a `BTN_STOP` mapping is left as a `TODO` for you to fill in
  from your own remote's captured code.

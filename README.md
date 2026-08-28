# Arduino Robotics Projects

A collection of five independent Arduino projects — robot cars, servo
mechanisms, and basic sensor sketches — each in its own folder with its own
wiring diagram and README.

| # | Project | Summary |
|---|---|---|
| 1 | [IR Remote + Autonomous Car](01-ir-remote-autonomous-car/) | OSOYOO robot car driven by IR remote or autonomous ultrasonic obstacle avoidance, plus serial control from a PC/Raspberry Pi |
| 2 | [Line-Following Robot](02-line-following-robot/) | 2-servo steering robot that follows a line using a digital IR line sensor |
| 3 | [Ultrasonic Distance Sensor](03-ultrasonic-distance-sensor/) | Standalone HC-SR04 sketch that prints live distance readings to Serial |
| 4 | [Servo Snake Robot](04-servo-snake-robot/) | Four servos fired in sequence to produce a rippling, snake-like gait |
| 5 | [LDR LED Brightness Indicator](05-ldr-led-night-light/) | Photoresistor-driven LED that responds to ambient light level |

Each project folder contains:
- The Arduino sketch(es) (`.ino` / `.h`)
- `README.md` — wiring table, libraries needed, and any bugs found & fixed
- `wiring_diagram.svg` — a labeled block diagram of the Arduino-to-component wiring

## Getting started
1. Open the `.ino` file for the project you want in the [Arduino IDE](https://www.arduino.cc/en/software).
2. Install any libraries listed in that project's README (Library Manager, or
   manually for `IRremote`).
3. Wire the components as shown in that project's `wiring_diagram.svg`.
4. Select your board (Arduino Uno) and port, then Upload.

## About this repository
These sketches started as working code from individual sessions with an
OSOYOO robot-car kit and assorted sensor/servo experiments. They've been
reorganized here into one project per folder, each documented with an
accurate wiring diagram. A few genuine issues were found and fixed along the
way, called out in the relevant project's README:
- **Projects 2 & 3**: the HC-SR04 distance formula was off by exactly 10x
  (a 100cm object read as ~1000cm) — a divisor bug, corrected and verified
  numerically.
- **Project 5**: missing braces on `if`/`else` bodies meant a `digitalWrite()`
  call ran unconditionally every loop regardless of the branch taken.
- **Project 4**: an out-of-range `Servo::write(-90)` call — not undefined
  behavior as first assumed (the Servo library actually clamps negative
  values to 0), but changed to a valid angle for a symmetric sweep. See that
  project's README for exactly what was verified and why.

See each project's README for the full details and reasoning.

## License
All Rights Reserved — see [LICENSE](LICENSE). Shared publicly for portfolio purposes; please contact the author before reusing.

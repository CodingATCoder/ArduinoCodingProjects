# LDR-Controlled LED Brightness Indicator

Reads ambient light level from a photoresistor (LDR) voltage divider on `A0`
and drives an LED on `D6` based on the reading, printing `"DARK"` or
`"BRIGHT"` to Serial as it goes.

**Behavior as written:** the LED turns **ON when it's bright** and **OFF when
it's dark** (threshold: analog reading of 150) — this is a "there's enough
light" indicator, not a night light. If you want the opposite (LED ON in the
dark), swap the two `digitalWrite(6, ...)` calls in `brightness_of_LED.ino`.

## Wiring
See [`wiring_diagram.svg`](wiring_diagram.svg).

| Component | Pin |
|---|---|
| LDR divider midpoint | A0 |
| LED anode (+) | D6 |
| LED cathode (−) | GND |

Use a current-limiting resistor (e.g. 220–330Ω) in series with the LED.

## Serial
Open Serial Monitor at **115200 baud** to see `DARK`/`BRIGHT` readouts.

## Fixed from the original code
The original `if`/`else` bodies had no braces, so only the `Serial.println()`
calls were actually conditional — both `digitalWrite(6, LOW)` and
`digitalWrite(6, HIGH)` ran **unconditionally every single loop** (LOW
immediately followed by HIGH), meaning the LED effectively always ended up ON
regardless of the light level. Braces have been added so each `digitalWrite()`
only runs in its matching branch.

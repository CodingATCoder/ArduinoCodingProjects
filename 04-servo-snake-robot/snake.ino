// #AadityaTandon
// Four-Servo Snake Robot
// ------------------------
// Fires 4 servos in sequence to produce a rippling/undulating gait.
// WIRING: servo1->pin2, servo2->pin3, servo3->pin4, servo4->pin5.
// See wiring_diagram.svg.
//
// CHANGED: the original sketch called servo3.write(-90) and
// servo1.write(-90). The Arduino Servo library actually clamps
// out-of-range angle values rather than behaving unpredictably --
// its write() silently clamps negative values to 0 (see Servo.cpp:
// "if(value < 0) value = 0;") -- so -90 was not a crash or undefined
// behavior, it just always drove those two servos to 0 degrees,
// giving an asymmetric 0<->40 sweep instead of a symmetric one.
// Changed to 140 degrees, which mirrors the 40-degree position
// symmetrically around the 90-degree center, so each servo now
// sweeps cleanly between 40 and 140 degrees.

#include <Servo.h>
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
void setup() {
  // put your setup code here, to run once:
  servo1.attach(2);
  servo2.attach(3);
  servo3.attach(4);
  servo4.attach(5);
}

void loop() {
  // put your main code here, to run repeatedly:
  servo4.write(40);
  delay(100);
  servo3.write(140);
  delay(100);
  servo2.write(40);
  delay(100);
  servo1.write(140);
  delay(100);
  servo4.write(40);
  delay(100);
  servo3.write(140);
  delay(100);
  servo2.write(40);
  delay(100);
  servo1.write(140);
  delay(100);

}

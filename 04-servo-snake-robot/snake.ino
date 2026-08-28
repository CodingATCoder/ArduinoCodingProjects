// #AadityaTandon
// Four-Servo Snake Robot
// ------------------------
// Fires 4 servos in sequence to produce a rippling/undulating gait.
// WIRING: servo1->pin2, servo2->pin3, servo3->pin4, servo4->pin5.
// See wiring_diagram.svg.
//
// FIXED: the original sketch called servo3.write(-90) and
// servo1.write(-90). Servo::write() only accepts 0-180 degrees, so
// -90 was out of range and produced undefined/unreliable behavior.
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

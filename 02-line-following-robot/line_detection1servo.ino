// #AadityaTandon
// Line-Following Robot -- 2-servo steering
// -----------------------------------------
// Reads a single IR line sensor (digital output) and steers two servos
// in opposite directions depending on whether the line is detected.
// An HC-SR04 ultrasonic sensor is wired and pin-configured (via
// Ultrasonic.h) for future obstacle-avoidance, but is not yet read in
// the control loop below. See wiring_diagram.svg for full pinout.
//
// WIRING:
//   Servo 1 (left)  signal -> pin 2
//   Servo 2 (right) signal -> pin 4
//   IR line sensor digital out -> pin 3
//   HC-SR04 Trig -> pin 9, Echo -> pin 8 (wired, unused for now)

#include <Servo.h>
#include "Ultrasonic.h"
Servo servo1;
Servo servo2;
unsigned long start_time = 0;
void setup() {
  // put your setup code here, to run once:
  servo1.attach( 2 );
  servo2.attach( 4 );
  Serial.begin (115200);
  pinMode( 3, INPUT );
  pinMode( 8, INPUT );
  pinMode( 9, OUTPUT );
  delay( 1000 );
  start_time = millis();
}
void left() {
  servo1.write( 90 + 20 );
  servo2.write( 90 - 20 );
}
void loop() {
  // put your main code here, to run repeatedly:
  int value = digitalRead( 3 );
  if (value == true)
  {
    Serial.println("☾");
    servo1.write( 90 + 20 );
    servo2.write( 90 - 20 );
  }

  else
  {
    Serial.println("☼");
    servo1.write( 90 - 20 );
    servo2.write( 90 + 20 );
  }
  delay(200);

}

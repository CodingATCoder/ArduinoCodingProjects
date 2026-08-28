// #AadityaTandon
// Ultrasonic Distance Sensor -- Serial readout
// -----------------------------------------------
// Standalone HC-SR04 distance sketch. Prints distance in cm to
// Serial Monitor (115200 baud) roughly every 200ms.
// WIRING: Trig -> pin 9, Echo -> pin 8, VCC -> 5V, GND -> GND.
// See wiring_diagram.svg. (Note: pulseIn() below has no timeout, so
// it can block indefinitely with no sensor/object in range -- see
// the README for a suggested fix.)

void setup() {
  // put your setup code here, to run once:
  pinMode( 8, INPUT );
  pinMode( 9, OUTPUT );
  Serial.begin (115200 );
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite( 9, LOW );
  delayMicroseconds( 2 );
  digitalWrite( 9, HIGH );
  delayMicroseconds( 10 );
  digitalWrite( 9, LOW );

  int duration = pulseIn( 8, HIGH);

  float speed_of_sound = 343.0;

  float distance = speed_of_sound * duration / 2000.0;
  Serial.println( distance );
  delay(200);
}

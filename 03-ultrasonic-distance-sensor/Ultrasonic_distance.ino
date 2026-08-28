// #AadityaTandon
// Ultrasonic Distance Sensor -- Serial readout
// -----------------------------------------------
// Standalone HC-SR04 distance sketch. Prints distance in cm to
// Serial Monitor (115200 baud) roughly every 200ms.
// WIRING: Trig -> pin 9, Echo -> pin 8, VCC -> 5V, GND -> GND.
// See wiring_diagram.svg. (Note: pulseIn() below has no explicit
// timeout, so it falls back to Arduino's default 1-second timeout --
// it will return 0 rather than hang forever, but a shorter explicit
// timeout gives faster, more predictable readings. See the README.)

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

  // FIXED: divisor was 2000.0, which reported distances ~10x too large
  // (e.g. a 100cm object read as ~1000cm). Correct conversion from a
  // round-trip pulse duration in microseconds and a speed of sound in
  // m/s to a one-way distance in cm is duration * speed_of_sound / 20000.0.
  float distance = speed_of_sound * duration / 20000.0;
  Serial.println( distance );
  delay(200);
}

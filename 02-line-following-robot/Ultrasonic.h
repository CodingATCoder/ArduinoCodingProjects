// #AadityaTandon
// Simple HC-SR04-style ultrasonic distance helper.
// Trig -> pin 9 (OUTPUT), Echo -> pin 8 (INPUT). See wiring_diagram.svg.
// Included by line_detection1servo.ino; getUltraSonicDistance() is
// available for future obstacle-avoidance logic (not yet called from
// the main loop in this project).

float getUltraSonicDistance()
{
  digitalWrite( 9, LOW );
  delayMicroseconds( 2 );
  digitalWrite( 9, HIGH );
  delayMicroseconds( 2 );
  digitalWrite( 9, LOW );

  int duration = pulseIn( 8, HIGH, 1000 );
  if ( duration <= 0 )
    return -1;
  float speed_of_sound = 343.0;

  // FIXED: divisor was 2000.0, which reported distances ~10x too large
  // (e.g. a 100cm object read as ~1000cm). Correct conversion from a
  // round-trip pulse duration in microseconds and a speed of sound in
  // m/s to a one-way distance in cm is duration * speed_of_sound / 20000.0.
  float distance = speed_of_sound * duration / 20000.0;
  Serial.println( distance );
  return distance;
}

// #AadityaTandon
// LDR-Controlled LED Brightness Indicator
// ------------------------------------------
// Reads ambient light level from a photoresistor (LDR) voltage
// divider on A0. As originally written (DARK -> LOW, BRIGHT -> HIGH),
// the LED on D6 turns ON when it's bright and OFF when it's dark --
// i.e. this behaves as a "there's enough light" indicator, not a
// night light. If you actually want a night light (LED ON in the
// dark), swap the digitalWrite(6, ...) calls in the two branches below.
// WIRING: LDR divider midpoint -> A0, LED (+resistor) -> D6.
// See wiring_diagram.svg.
//
// FIXED: the original if/else bodies had no braces, so only the
// Serial.println() calls were actually conditional -- both
// digitalWrite(6, LOW) and digitalWrite(6, HIGH) ran unconditionally
// on every single loop (LOW immediately followed by HIGH), so the
// LED effectively stayed on regardless of brightness. Added braces
// so each digitalWrite() only runs in its matching branch.

void setup() {
  // put your setup code here, to run once:
  Serial.begin( 115200);
  pinMode(6, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int brightness = analogRead( A0 );

  delay(10);
  if ( 150 > brightness ) {
    Serial.println("DARK");
    digitalWrite(6, LOW);
  }

  if ( 150 < brightness ) {
    Serial.println("BRIGHT");
    digitalWrite(6, HIGH);
  }

  delay(100);

}

// #AadityaTandon
/*
  Osoyoo V2.1 Robot Car - IR Remote + Autonomous Driving
  --------------------------------------------------------
  Drives the car's motors via the OSOYOO Model X motor driver module.
  Two ways to control it:
    1) IR remote (forward/back/left/right, as before)
    2) Autonomous obstacle-avoidance mode using 4 ultrasonic sensors,
       toggled on/off with the MUTE button on the remote

  WIRING (as actually connected -- see wiring_diagram.svg):
    IR receiver module:
      S (signal) -> Arduino pin 8
      -  (GND)   -> GND
      +  (VCC)   -> 5V

    OSOYOO Model X motor driver:
      ENA -> D2
      IN1 -> D3
      IN2 -> D4
      IN3 -> D5
      IN4 -> D6
      ENB -> D7

    A SEPARATE Arduino now handles the 4 ultrasonic sensors (see
    sensor_arduino.ino) and sends distance readings over a serial
    link:
      Sensor Arduino pin 2 (TX) -> this board's pin 10 (RX)
      Sensor Arduino GND         -> this board's GND

    NOTE: this file's LINK_RX #define below is 10. An earlier version
    of this comment said pin 12 -- if your sensor Arduino's TX wire is
    physically connected to pin 12 instead, either move the wire to
    pin 10 or change LINK_RX to 12 so the #define and the physical
    wiring agree.

  NOTE: pins 2 and 7 don't support true PWM on an Uno, so ENA/ENB
  will run the motors at a fixed full speed rather than a variable
  one -- MOTOR_SPEED below won't finely control speed on this wiring,
  just on/off. That's fine for basic driving.

  LIBRARY:
    IRremote by shirriff / z3t0 / Armin Joachimsmeyer (v3.x/v4.x API)
    SoftwareSerial (built into the Arduino IDE, no install needed)

  REMOTE MAPPING:
    This remote's physical button layout doesn't match a generic
    numeric-keypad assumption, so buttons are now named by function
    and mapped to the ACTUAL codes captured from Serial Monitor.
    Press MUTE to toggle autonomous driving on/off. Pressing any
    drive button (forward/back/left/right) while autonomous mode is
    on immediately switches back to manual control.
*/

#include <IRremote.hpp>
#include <SoftwareSerial.h>

#define IR_RECEIVE_PIN 8

// Motor driver pins (matches actual wiring)
#define ENA 2
#define IN1 3
#define IN2 4
#define IN3 5
#define IN4 6
#define ENB 7

#define MOTOR_SPEED 150   // 0-255, raise/lower to taste

// Link to the sensor Arduino
#define LINK_RX 10  // receives from sensor Arduino's TX
#define LINK_TX 12  // not actually used, but SoftwareSerial needs a pin defined
SoftwareSerial sensorLink(LINK_RX, LINK_TX);

// Latest readings from the sensor Arduino (updated every loop)
long distFront = 999, distBack = 999, distLeft = 999, distRight = 999;

#define OBSTACLE_DISTANCE_CM 30   // how close is "too close"
#define TURN_TIME_MS 400          // how long to turn when avoiding

bool autoMode = false;

// ---- Drive buttons: fill these in as you confirm each one ----
// NOTE: only BTN_FORWARD is confirmed right now. The other four are
// deliberately left OUT of the switch below (not just set to 0)
// because a switch can't have duplicate case values -- once you
// send me each real code, uncomment the matching #define AND the
// matching case line in loop().
#define BTN_FORWARD  0xE718FF00  // confirmed: "up arrow"
#define BTN_BACKWARD 0xAD52FF00  // confirmed: "down/back"
#define BTN_LEFT     0xF708FF00  // confirmed: "left"
#define BTN_RIGHT    0xA55AFF00  // confirmed: "right"
// #define BTN_STOP     0x________FF00  // TODO: press "OK/stop", paste code here

// ---- Other buttons already confirmed from your Serial output ----
#define BTN_MUTE   0xB946FF00
#define BTN_PLAY   0xBB44FF00
#define BTN_NEXT   0xBC43FF00
#define BTN_MINUS  0xEA15FF00

void setup() {
  Serial.begin(9600);
  while (!Serial) {}

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
  motorsStop();

  sensorLink.begin(9600);

  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
  Serial.println(F("Osoyoo IR Remote Car ready."));
  Serial.println(F("Drive with: up / back / left / right"));
  Serial.println(F("Press MUTE to toggle autonomous obstacle-avoidance mode"));
}

void loop() {
  // ---- Serial commands from Raspberry Pi ----
  // Single-character commands: F=forward B=backward L=left R=right S=stop
  if (Serial.available() > 0) {
    char cmd = Serial.read();
    switch (cmd) {
      case 'F': motorsForward();  break;
      case 'B': motorsBackward(); break;
      case 'L': motorsLeft();     break;
      case 'R': motorsRight();    break;
      case 'S': motorsStop();     break;
      default: break; // ignore newlines / unknown chars
    }
  }

  // ---- IR remote ----
  if (IrReceiver.decode()) {
    uint32_t code = IrReceiver.decodedIRData.decodedRawData;

    // Skip noise/incomplete repeat frames
    if (code == 0) {
      IrReceiver.resume();
      return;
    }

    Serial.print(F("Received code: 0x"));
    Serial.println(code, HEX);

    switch (code) {
      case BTN_FORWARD:  autoMode = false; Serial.println(F("-> FORWARD"));  motorsForward();  break;
      case BTN_BACKWARD: autoMode = false; Serial.println(F("-> BACKWARD")); motorsBackward(); break;
      case BTN_LEFT:      autoMode = false; Serial.println(F("-> LEFT"));     motorsLeft();     break;
      case BTN_RIGHT:     autoMode = false; Serial.println(F("-> RIGHT"));    motorsRight();    break;
      // Once BTN_STOP is uncommented above, add its case line here too:
      // case BTN_STOP: autoMode = false; Serial.println(F("-> STOP")); motorsStop(); break;

      case BTN_MUTE:
        autoMode = !autoMode;
        motorsStop();
        Serial.print(F("-> AUTONOMOUS MODE "));
        Serial.println(autoMode ? F("ON") : F("OFF"));
        break;
      case BTN_PLAY:  Serial.println(F("-> PLAY/PAUSE")); break;
      case BTN_NEXT:  Serial.println(F("-> NEXT"));  break;
      case BTN_MINUS: Serial.println(F("-> VOL -")); break;

      case 0xFFFFFFFF:
        Serial.println(F("-> (repeat - button held down)"));
        break;
      default:
        Serial.println(F("-> Unknown button (see raw code above)"));
        break;
    }

    IrReceiver.resume();
  }

  // ---- Read latest sensor data from the sensor Arduino ----
  readSensorLink();

  // ---- Autonomous obstacle avoidance ----
  if (autoMode) {
    driveAutonomously();
  }
}

void readSensorLink() {
  // Sensor Arduino sends lines like: F35 B120 L60 R45
  if (sensorLink.available()) {
    String line = sensorLink.readStringUntil('\n');
    int fIdx = line.indexOf('F');
    int bIdx = line.indexOf('B');
    int lIdx = line.indexOf('L');
    int rIdx = line.indexOf('R');
    if (fIdx >= 0 && bIdx >= 0 && lIdx >= 0 && rIdx >= 0) {
      distFront = line.substring(fIdx + 1, bIdx).toInt();
      distBack  = line.substring(bIdx + 1, lIdx).toInt();
      distLeft  = line.substring(lIdx + 1, rIdx).toInt();
      distRight = line.substring(rIdx + 1).toInt();
    }
  }
}

void driveAutonomously() {
  if (distFront > OBSTACLE_DISTANCE_CM) {
    motorsForward();
  } else {
    // Front is blocked -- stop and figure out which way is clearer
    motorsStop();
    delay(150);

    if (distLeft < OBSTACLE_DISTANCE_CM && distRight < OBSTACLE_DISTANCE_CM) {
      // Boxed in on both sides too -- back up if there's room
      if (distBack > OBSTACLE_DISTANCE_CM) {
        motorsBackward();
        delay(TURN_TIME_MS);
      }
      motorsStop();
    } else if (distLeft > distRight) {
      motorsLeft();
      delay(TURN_TIME_MS);
      motorsStop();
    } else {
      motorsRight();
      delay(TURN_TIME_MS);
      motorsStop();
    }
  }
}

// ---- Motor control ----
// Left side: ENA / IN1 / IN2   Right side: ENB / IN3 / IN4
// If your car drives backward when you press forward (or turns the
// wrong way), swap the HIGH/LOW pair for that side below.

void motorsForward() {
  analogWrite(ENA, MOTOR_SPEED);
  analogWrite(ENB, MOTOR_SPEED);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void motorsBackward() {
  analogWrite(ENA, MOTOR_SPEED);
  analogWrite(ENB, MOTOR_SPEED);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void motorsLeft() {
  analogWrite(ENA, MOTOR_SPEED);
  analogWrite(ENB, MOTOR_SPEED);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void motorsRight() {
  analogWrite(ENA, MOTOR_SPEED);
  analogWrite(ENB, MOTOR_SPEED);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void motorsStop() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

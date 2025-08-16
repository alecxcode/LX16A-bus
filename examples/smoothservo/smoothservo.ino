#include <Arduino.h>
#include "LX16A-bus.h"
#include "smoothservo.h"

LX16A motor1(1, Serial);
LX16A motor2(2, Serial);

SmoothServo smove1(motor1);
SmoothServo smove2(motor2);

void setup() {
  Serial.begin(115200);
  motor1.initialize();
  motor1.enableTorque();
  motor2.initialize();
  motor2.enableTorque();
  motor1.setServoMode();
  motor2.setServoMode();
}

unsigned long msini = millis();
unsigned long ms = millis();
float targetAngle1 = 120.0;
float targetAngle2 = 120.0;
bool movingFwd1 = true;
bool movingFwd2 = true;

void loop() {
  ms = millis();
  smove1.update(ms);
  smove2.update(ms);
  if (!smove1.isRunning()) {
    smove1.start(targetAngle1);
    targetAngle1 = (targetAngle1 == 0.0 || targetAngle1 == 240.0) ? 120.0 : (movingFwd1) ? 240.0 : 0.0;
    movingFwd1 = (targetAngle1 == 120.0) ? movingFwd1 : !movingFwd1;
  }
  if (!smove2.isRunning() && ms-msini > 500) {
    smove2.start(targetAngle2);
    targetAngle2 = (targetAngle2 == 0.0 || targetAngle2 == 240.0) ? 120.0 : (movingFwd2) ? 240.0 : 0.0;
    movingFwd2 = (targetAngle2 == 120.0) ? movingFwd2 : !movingFwd2;
  }
}

#include <Arduino.h>
#include "LX16A-bus.h"

LX16A motor1(1, Serial);
LX16A motor2(2, Serial);

void setup() {
  Serial.begin(115200);
  motor1.initialize();
  motor1.enableTorque();
  motor2.initialize();
  motor2.enableTorque();
  motor1.setServoMode();
  motor2.setServoMode();
}

void loop() {
  float angle = motor1.getPhysicalAngle();
  delay(50);
  Serial.print("angle: ");
  Serial.println(angle);
  motor1.move(240);
  delay(1000);
  motor2.move(240);
  delay(2000);
  angle = motor1.getPhysicalAngle();
  delay(50);
  Serial.print("angle: ");
  Serial.println(angle);
  motor1.move(0);
  delay(1000);
  motor2.move(0);
  delay(2000);
}

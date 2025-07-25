#include <Arduino.h>
#include "LX16A-bus.h"
#include "smoothmotor.h"

LX16A motor1(1, Serial);
LX16A motor2(2, Serial);

// Smooth motor mode operation:
SmoothMotor smotor1;
SmoothMotor smotor2;

void setup() {
  Serial.begin(115200);
  motor1.initialize();
  motor1.enableTorque();
  motor2.initialize();
  motor2.enableTorque();
  motor1.setMotorMode(0);
  motor2.setMotorMode(0);

  Serial.print("Motor Mode: ");
  Serial.print(motor1.isMotorMode() ? "true " : "false ");
  Serial.println(motor2.isMotorMode() ? "true " : "false ");
  smotor1.start(motor1, 1000);
  smotor2.start(motor2, 1000);
}

unsigned long msini = millis();
unsigned long ms = millis();
int16_t speed = 1000;

void loop() {
  ms = millis();

  smotor1.update(ms);
  smotor2.update(ms);

  if (ms - msini > 2000) {
    smotor1.stop();
    smotor2.stop();
  }

  if (!smotor1.isRunning() && !smotor2.isRunning()) {
    delay(2000);
    msini = millis();
    speed = -speed;
    smotor1.start(motor1, speed);
    smotor2.start(motor2, speed);
  }
}

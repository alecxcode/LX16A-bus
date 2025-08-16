// Smooth Bus Servos
#include <Arduino.h>
#include "LX16A-bus.h"
#include "sineosc.h"

LX16A motor1(1, Serial);
LX16A motor2(2, Serial);

SineOscillator osc1(motor1);
SineOscillator osc2(motor2);

void setup() {
  Serial.begin(115200);
  motor1.initialize();
  motor1.enableTorque();
  motor2.initialize();
  motor2.enableTorque();
  motor1.setServoMode();
  motor2.setServoMode();
  motor1.move(0, 2000);
  motor2.move(0, 2000);
  delay(3000);
}

unsigned long ms = millis();
float oscangle = 240.0;

void loop() {
  ms = millis();
  osc1.update(ms);
  osc2.update(ms);
  if (!osc1.isRunning() && !osc2.isRunning()) {
    osc1.start(oscangle, 2);
    osc2.start(oscangle, 2);
    oscangle -= 90.0;
    if (oscangle <= 0.0) {
      oscangle = 240.0;
    }
  }
}

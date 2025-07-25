#include <Arduino.h>
#include "LX16A-bus.h"

LX16A motor(1, Serial);

void setup() {
  Serial.begin(115200);
  motor.initialize();
  motor.setID(11);
}

void loop() {
  Serial.println("Setup complete");
  delay(1000);
}

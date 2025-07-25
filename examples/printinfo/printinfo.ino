#include <Arduino.h>
#include "LX16A-bus.h"

LX16A motor(1, Serial);

void printSlowly(const char* text, unsigned int delayMs = 30);
void printNixRobot();

void setup() {
  Serial.begin(115200);
  motor.initialize();
  motor.enableTorque();
  printNixRobot();
}

unsigned long msini = 0;
bool ledon = false;

void loop() {
  int vin = motor.getVin();
  delay(50);
  int temp = motor.getTemp();
  delay(50);
  printSlowly("\n=== ServoMotor Readings ===");
  Serial.print("Motor Mode: ");
  Serial.println(motor.isMotorMode() ? "on" : "off");
  delay(50);
  Serial.print("Torque: ");
  Serial.println(motor.isTorqueEnabled() ? "on" : "off");
  delay(50);
  Serial.print("LED: ");
  Serial.println(motor.isLedPowerOn() ? "on" : "off");
  delay(50);
  Serial.print("Voltage [mV]: ");
  Serial.println(vin);
  Serial.print("Temperature [deg.C]: ");
  Serial.println(temp);
  if (millis() - msini >= 6000) {
    ledon = !ledon;
    if (ledon) {
      motor.ledPowerOn();
    } else {
      motor.ledPowerOff();
    }
    msini = millis();
  }
  delay(5500);
}

void printSlowly(const char* text, unsigned int delayMs) {
  while (*text) {
    Serial.print(*text++);
    delay(delayMs);
  }
  Serial.println();
}

void printNixRobot() {
  Serial.println();
  Serial.println("          *NIX "); delay(80);
  Serial.println("       _--------_"); delay(80);
  Serial.println("      |[0]    [0]|"); delay(80);
  Serial.println("      |    ..    |"); delay(80);
  Serial.println("       \\__====__/"); delay(80);
  Serial.println("          |  |"); delay(80);
  Serial.println("         :ROBOT"); delay(80);
  Serial.println();
}
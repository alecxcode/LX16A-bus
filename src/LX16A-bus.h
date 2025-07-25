/*
  Morse.h - Library for LX-16A bus servomortors with BusLinker.
  Created by Aleksandr Vankov, July 20, 2025.
  Released into the public domain.
*/

#ifndef LX16A_H
#define LX16A_H

#include <Arduino.h>
#include <SoftwareSerial.h>

class LX16A {
public:
  LX16A(uint8_t id, HardwareSerial &serial);
  void initialize(long baud = 115200);
  void setID(uint8_t new_id);
  void move(float angle, uint16_t time = 0, bool wait = false);
  void enableTorque();
  void disableTorque();
  float getPhysicalAngle();
  float getCommandedAngle();
  void setMotorMode(int16_t speed);
  void setServoMode();
  void ledPowerOn();
  void ledPowerOff();
  bool isMotorMode(bool pollHardware = false);
  bool isTorqueEnabled(bool pollHardware = false);
  bool isLedPowerOn(bool pollHardware = false);
  int getTemp();
  int getVin();

private:
  uint8_t motorid;
  HardwareSerial *serialx;
  bool motorMode;
  bool torqueEnabled;
  bool ledPowered;
  float commandedAngle;

  uint8_t checksum(uint8_t *packet, uint8_t length);
  void sendPacket(uint8_t *packet, uint8_t length);
  bool readPacket(uint8_t *buffer, uint8_t length);
  uint16_t toServoRange(float angle);
  float fromServoRange(uint16_t value);
};

#endif

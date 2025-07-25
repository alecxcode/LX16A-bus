#include "LX16A-bus.h"

LX16A::LX16A(uint8_t id, HardwareSerial &serial) {
  motorid = id;
  serialx = &serial;
  motorMode = false;
  torqueEnabled = false;
  ledPowered = false;
  commandedAngle = -1.0;
}

void LX16A::initialize(long baud) {
  if (!Serial) { 
    serialx->begin(baud);
  }
  motorMode = isMotorMode(true);
  torqueEnabled = isTorqueEnabled(true);
  ledPowered = isLedPowerOn(true);
}

uint8_t LX16A::checksum(uint8_t *packet, uint8_t length) {
  uint16_t sum = 0;
  for (uint8_t i = 2; i < length; i++) {
    sum += packet[i];
  }
  return (~sum) & 0xFF;
}

void LX16A::sendPacket(uint8_t *packet, uint8_t length) {
  uint8_t fullPacket[16];
  fullPacket[0] = 0x55;
  fullPacket[1] = 0x55;
  memcpy(fullPacket + 2, packet, length);
  fullPacket[length + 2] = checksum(fullPacket, length + 2);

  serialx->write(fullPacket, length + 3);
}

bool LX16A::readPacket(uint8_t *buffer, uint8_t length) {
  uint32_t start = millis();
  while (serialx->available() < length + 6) {
    if (millis() - start > 100) return false;
  }
  for (uint8_t i = 0; i < length + 6; i++) {
    buffer[i] = serialx->read();
  }
  return true;
}

uint16_t LX16A::toServoRange(float angle) {
  return (uint16_t)(angle * 25.0 / 6.0);
}

float LX16A::fromServoRange(uint16_t value) {
  return (float)value * 6.0 / 25.0;
}

void LX16A::setID(uint8_t newmotorid) {
  uint8_t packet[] = { motorid, 4, 13, newmotorid };
  sendPacket(packet, sizeof(packet));
  motorid = newmotorid;
}

void LX16A::move(float angle, uint16_t time, bool wait) {
  uint16_t angleVal = toServoRange(angle);
  uint8_t angleLow = angleVal & 0xFF;
  uint8_t angleHigh = (angleVal >> 8) & 0xFF;
  uint8_t timeLow = time & 0xFF;
  uint8_t timeHigh = (time >> 8) & 0xFF;

  uint8_t packet[] = {
    motorid, 7, wait ? 7 : 1,
    angleLow, angleHigh,
    timeLow, timeHigh
  };

  sendPacket(packet, sizeof(packet));
}

void LX16A::enableTorque() {
  uint8_t packet[] = { motorid, 4, 31, 1 };
  sendPacket(packet, sizeof(packet));
  torqueEnabled = true;
}

void LX16A::disableTorque() {
  uint8_t packet[] = { motorid, 4, 31, 0 };
  sendPacket(packet, sizeof(packet));
  torqueEnabled = false;
}

float LX16A::getPhysicalAngle() {
  uint8_t packet[] = { motorid, 3, 28 };
  sendPacket(packet, sizeof(packet));

  uint8_t response[10];
  if (!readPacket(response, 2)) return -1;
  uint16_t raw = response[5] | (response[6] << 8);
  if (raw > abs(32767)) raw = 0;
  
  return fromServoRange(raw);
}

float LX16A::getCommandedAngle() {
  return commandedAngle;
}

void LX16A::setMotorMode(int16_t speed) {
  if (!torqueEnabled) {
    return;
  }

  if (speed < -1000) speed = -1000;
  if (speed > 1000) speed = 1000;

  uint16_t encodedSpeed = speed < 0 ? (uint16_t)(speed + 65536) : (uint16_t)speed;

  uint8_t packet[] = {motorid, 7, 29, 1, 0,
    (uint8_t)(encodedSpeed & 0xFF),
    (uint8_t)((encodedSpeed >> 8) & 0xFF)
  };
  sendPacket(packet, sizeof(packet));
  motorMode = true;
}

void LX16A::setServoMode() {
  uint8_t packet[] = {motorid, 7, 29, 0, 0, 0, 0};
  sendPacket(packet, sizeof(packet));
  motorMode = false;
}

void LX16A::ledPowerOff() {
  uint8_t packet[] = { motorid, 4, 33, 1 };
  sendPacket(packet, sizeof(packet));
  ledPowered = false;
}

void LX16A::ledPowerOn() {
  uint8_t packet[] = { motorid, 4, 33, 0 };
  sendPacket(packet, sizeof(packet));
  ledPowered = true;
}


bool LX16A::isMotorMode(bool pollHardware) {
  if (!pollHardware) {
    return motorMode;
  }

  uint8_t packet[] = { motorid, 3, 30 };
  sendPacket(packet, sizeof(packet));

  uint8_t response[10]; 
  if (!readPacket(response, 4)) {
    return false;
  }

  return response[5] == 1;
}

bool LX16A::isTorqueEnabled(bool pollHardware) {
  if (!pollHardware) {
    return torqueEnabled;
  }

  uint8_t packet[] = { motorid, 3, 32 };
  sendPacket(packet, sizeof(packet));

  uint8_t response[10];
  if (!readPacket(response, 1)) {
    return false;
  }

  return response[5] == 1;
}

bool LX16A::isLedPowerOn(bool pollHardware) {
  if (!pollHardware) {
    return ledPowered;
  }

  uint8_t packet[] = { motorid, 3, 34 };
  sendPacket(packet, sizeof(packet));

  uint8_t response[10];
  if (!readPacket(response, 1)) {
    return false;
  }

  return response[5] == 0;
}

int LX16A::getTemp() {
  uint8_t packet[] = { motorid, 3, 26 };
  sendPacket(packet, sizeof(packet));

  uint8_t response[10];
  if (!readPacket(response, 1)) {
    return -1; 
  }

  return response[5];
}

int LX16A::getVin() {
  uint8_t packet[] = { motorid, 3, 27 };
  sendPacket(packet, sizeof(packet));

  uint8_t response[10];
  if (!readPacket(response, 2)) {
    return -1;
  }

  return response[5] | (response[6] << 8);
}

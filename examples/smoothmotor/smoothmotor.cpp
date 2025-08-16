#include "smoothmotor.h"

void SmoothMotor::start(int16_t tSpeed) {
  if (!servo->isMotorMode()) return;
  currentSpeed = 0;
  targetSpeed = tSpeed;
  step = (targetSpeed > 0) ? 25 : -25;
  lastUpdate = millis();
  running = true;
  starting = true;
  stopping = false;
}

void SmoothMotor::stop() {
  if (!servo || !servo->isMotorMode()) return;
  if (!running || stopping) return;
  targetSpeed = 0;
  step = (currentSpeed > 0) ? -25 : 25;
  lastUpdate = millis();
  running = true;
  starting = false;
  stopping = true;
}

void SmoothMotor::update(unsigned long now) {
  if ((!starting && !stopping && !running) || !servo) return;
  if (now - lastUpdate >= 25) {
    currentSpeed += step;
    lastUpdate = now;
    bool reachedTarget = (step > 0 && currentSpeed >= targetSpeed) ||
                         (step < 0 && currentSpeed <= targetSpeed);
    if (reachedTarget) {
      currentSpeed = targetSpeed;
      if (stopping) {
        running = false;
        stopping = false;
      }
      if (starting) {
        starting = false;
      }
    }
    servo->setMotorMode(currentSpeed);
  }
}


bool SmoothMotor::isRunning() const {
  return running;
}

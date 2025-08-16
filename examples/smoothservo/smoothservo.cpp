#include "smoothservo.h"

void SmoothServo::start(float toAngle) {
  targetAngle = toAngle;
  startAngle = servo->getPhysicalAngle();
  x = 0.0;
  lastUpdate = millis();
  running = true;
}

void SmoothServo::update(unsigned long now) {
  if (!running) return;
  if (now - lastUpdate >= 50) {
    if (x > 1.0) {
      running = false;
      return;
    }
    // the function is a = s+(t-s)(6x^5-15x^4+10x^3)
    float a = startAngle + (targetAngle - startAngle) * (x * x * x) * (x * (6 * x - 15) + 10); 
    servo->move(a, 50);
    x += 0.025;
    lastUpdate = now;
  }
}

bool SmoothServo::isRunning() {
  return running;
}

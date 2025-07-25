#include "sineosc.h"

void SineOscillator::start(LX16A& s, float maxA, int numOsc) {
  servo = &s;
  maxAngle = maxA;
  numOscillations = numOsc;
  x = -M_PI / 2.0;
  lastUpdate = millis();
  running = true;
}

void SineOscillator::update(unsigned long now) {
  if (!running) return;
  if (now - lastUpdate >= 50) {
    if (x >= M_PI * 2 * numOscillations - M_PI / 2.0) {
      servo->move(0, 50);
      running = false;
    }
    float a = sin(x) * (maxAngle / 2.0) + (maxAngle / 2.0);
    servo->move(a, 50);
    x += 0.05;
    lastUpdate = now;
  }
}

bool SineOscillator::isRunning() {
  return running;
}

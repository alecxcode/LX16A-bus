// SineOscillator.h
#ifndef SINE_OSCILLATOR_H
#define SINE_OSCILLATOR_H

#include <LX16A-bus.h>
#include <math.h>

class SineOscillator {
public:
  SineOscillator(LX16A& s) : servo(&s) {}

  void start(float maxA, int numOsc);
  void update(unsigned long now);
  bool isRunning();

private:
  LX16A* servo;
  float maxAngle;
  int numOscillations;
  double x;
  unsigned long lastUpdate;
  bool running = false;
};

#endif

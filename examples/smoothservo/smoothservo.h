#ifndef SMOOTH_MOVER_H
#define SMOOTH_MOVER_H

#include <LX16A-bus.h>

class SmoothServo {
public:
  SmoothServo(LX16A& s) : servo(&s) {}
  
  void start(float targetAngle);
  void update(unsigned long now);
  bool isRunning();

private:
  LX16A* servo;
  float targetAngle;
  float startAngle;
  double x;
  unsigned long lastUpdate;
  bool running = false;
};

#endif

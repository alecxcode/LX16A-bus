#ifndef SMOOTH_MOVER_H
#define SMOOTH_MOVER_H

#include <LX16A-bus.h>

class SmoothServo {
public:
  void start(LX16A& s, float targetAngle);
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

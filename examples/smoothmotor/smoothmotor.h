#ifndef SMOOTH_MOTOR_H
#define SMOOTH_MOTOR_H

#include <LX16A-bus.h>

class SmoothMotor {
public:
  SmoothMotor(LX16A& s) : servo(&s) {}

  void start(int16_t targetSpeed);
  void stop();
  void update(unsigned long now);
  bool isRunning() const;

private:
  LX16A *servo;
  int16_t currentSpeed = 0;
  int16_t targetSpeed = 0;
  int16_t step = 50;
  unsigned long lastUpdate = 0;
  bool running = false;
  bool starting = false;
  bool stopping = false;
};

#endif

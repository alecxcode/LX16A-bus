# LX-16A Bus Servo Library for Arduino

A lightweight object-oriented library with a class for controlling bus servo motors (Hiwonder, LewanSoul) using a BusLinker.

It basically contains `LX16A` class and logic that are very similar to the [PyLX-16A](https://github.com/ethanlipson/PyLX-16A) package. But this implementation is in C++.

## Features

- Compatible with 3-pin LX-16A bus servo motors, and possibly with other servos of this family  
- Provides an easy-to-use class with methods  
- Contains [examples](/examples/) with smooth motion (easing in and out) in servo and motor modes

## Requirements

- Any Arduino or Arduino-core board  
- Arduino IDE, PlatformIO, or another IDE  
- BusLinker, also known as the TTL/USB Debug Board for Serial Bus Servo
- Could be used directly without BusLinker but read (get) methods will not work
- External power for the motor

<!--TODO: ## Video Tutorial with Electronics

[![Video Tutorial](https://img.youtube.com/vi/VIDEO/mqdefault.jpg)](https://www.youtube.com/watch?v=VIDEO) -->

## Installation

Put the files from the `src` directory into your project (sketch directory), or install via the Arduino Library Manager (after this library is added to the Library Manager).

## Usage: All Methods and Descriptions

Create the instance of the servomotor:  
`LX16A(uint8_t id, HardwareSerial &serial);`

Initialize the servo and read some of its parameters:  
`void initialize(long baud = 115200);`

Set the ID of the servo:  
`void setID(uint8_t new_id);`

Rotate to the given angle (for LX-16A from 0 to 240):  
`void move(float angle, uint16_t time = 0, bool wait = false);`

Enable torque so that it does not relax (prevents moving due to gravity or other forces):  
`void enableTorque();`

Disable torque so that you can rotate it, for instance, with your hands:  
`void disableTorque();`

Read the physical angle at which the servo is currently positioned:  
`float getPhysicalAngle();`

Read the last commanded angle (not necessarily the same as physical angle):  
`float getCommandedAngle();`

Set the servo to the motor mode (continuous rotation without positioning):  
`void setMotorMode(int16_t speed);`

Set the servo to the servo mode (positioning, no continuous rotation):  
`void setServoMode();`

Turn on internal servo LED:  
`void ledPowerOn();`

Turn off internal servo LED:  
`void ledPowerOff();`

Check if the servo is in the motor mode:  
`bool isMotorMode(bool pollHardware = false);`

Check if torque is enabled:  
`bool isTorqueEnabled(bool pollHardware = false);`

Check if internal LED is on:  
`bool isLedPowerOn(bool pollHardware = false);`

Read the current temperature at the servo in °C:  
`int getTemp();`

Read supplied voltage in millivolts:  
`int getVin();`

## Example

See more examples and get smooth motion classes in the [examples](/examples/) folder.

```cpp
#include <Arduino.h>
#include "LX16A-bus.h"

LX16A motor1(1, Serial);
LX16A motor2(2, Serial);

void setup() {
  Serial.begin(115200);
  motor1.initialize();
  motor1.enableTorque();
  motor2.initialize();
  motor2.enableTorque();
  motor1.setServoMode();
  motor2.setServoMode();
}

void loop() {
  float angle = motor1.getPhysicalAngle();
  delay(50);
  Serial.print("angle: ");
  Serial.println(angle);
  motor1.move(240);
  delay(1000);
  motor2.move(240);
  delay(2000);
  angle = motor1.getPhysicalAngle();
  delay(50);
  Serial.print("angle: ");
  Serial.println(angle);
  motor1.move(0);
  delay(1000);
  motor2.move(0);
  delay(2000);
}
```

## Help the Creator

If you find this useful, consider supporting the developer.

[![Donate](https://exoimages.pages.dev/buttons/donate-ora.svg)](https://www.gofundme.com/f/keep-my-science-journey-alive-with-support)
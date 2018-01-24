#ifndef _CONFIGURATION_CONTROLS_H
#define _CONFIGURATION_CONTROLS_H
#include "API.h"

inline int getLeftJoystick() {
  return joystickGetAnalog(1, 3);
}

inline int getRightJoystick() {
  return joystickGetAnalog(1, 2);
}

inline bool getOpenMobileGoal() {
  return joystickGetDigital(1, 7, JOY_UP);
}

inline bool getCloseMobileGoal() {
  return joystickGetDigital(1, 7, JOY_LEFT);
}

#endif

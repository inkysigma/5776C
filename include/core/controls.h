#ifndef CORE_CONTROL_H
#define CORE_CONTROL_H
#include "API.h"

inline int getJoystickLeft() {
  return joystickGetAnalog(1, 3);
}

inline int getJoystickRight() {
  return joystickGetAnalog(1, 2);
}

inline int getJoystickLeftTurn() {
  return joystickGetAnalog(1, 4);
}

inline int getJoystickRightTurn() {
  return joystickGetAnalog(1, 1);
}

inline bool getRaiseLift() {
  return joystickGetDigital(1, 5, JOY_UP);
}

inline bool getLowerLift() {
  return joystickGetDigital(1, 5, JOY_DOWN);
}

inline bool getRaiseClaw() {
  return joystickGetDigital(1, 6, JOY_UP);
}

inline bool getRaiseClawPartial() {
  return joystickGetDigital(1, 7, JOY_RIGHT);
}

inline bool getLowerClaw() {
  return joystickGetDigital(1, 6, JOY_DOWN);
}

inline bool getToggleClaw() {
  return joystickGetDigital(1, 7, JOY_DOWN);
}

inline bool getOpenGoal() {
  return joystickGetDigital(1, 7, JOY_UP);
}

inline bool getRetractGoal() {
  return joystickGetDigital(1, 7, JOY_LEFT);
}

inline bool getBuildStack() {
  return joystickGetDigital(1, 8, JOY_DOWN);
}

inline bool getDecreaseStack() {
  return joystickGetDigital(1, 8, JOY_LEFT);
}

inline bool getResetStack() {
  return joystickGetDigital(1, 8, JOY_UP);
}

inline bool getIncreaseStack() {
  return joystickGetDigital(1, 8, JOY_RIGHT);
}
#endif

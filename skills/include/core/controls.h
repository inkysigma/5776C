/**
 * @file core/controls.h
 *
 * @brief This file contains inline methods to return the values from the user
 *        joystick. Each function is parameterless but is inserted at compile
 *        so you will need to run make clean in order to reupload
 **/

#ifndef _CONFIGURATION_CONTROLS_H
#define _CONFIGURATION_CONTROLS_H
#include "API.h"

/**
 * @method getLeftJoystick()
 * @brief Get the value returned by the left joystick in the forward and
 *        backward direction. This will most likely be used to control the
 *        drive on the left side.
 **/
inline int getLeftJoystick() {
  return joystickGetAnalog(1, 3);
}

/**
 * @method getRightJoystick()
 * @brief Get the value returned by the right joystick in the forward and
 *        backward direction. This will most likely be used to control the
 *        drive on the right side.
 **/
inline int getRightJoystick() {
  return joystickGetAnalog(1, 2);
}

/**
 * @method getRightJoystick()
 * @brief Get the value returned by the right joystick in the forward and
 *        backward direction. This will most likely be used to control the
 *        drive on the right side.
 **/
inline bool getOpenMobileGoal() {
  return joystickGetDigital(1, 7, JOY_UP);
}

inline bool getCloseMobileGoal() {
  return joystickGetDigital(1, 7, JOY_LEFT);
}

inline bool getRunAuton() {
    return joystickGetDigital(1,8, JOY_DOWN);
}

inline bool getTestFeedback() {
  return joystickGetDigital(1, 7, JOY_DOWN);
}

inline bool getStopTestFeedback() {
  return joystickGetDigital(1, 7, JOY_RIGHT);
}

#endif

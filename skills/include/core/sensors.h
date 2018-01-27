/**
 * @file core/sensors.h
 *
 * @brief This file contains the core functionality of the motors by creating
 *        methods to interact with sensors.
 *
 *        e.g readLeft() will return the number of ticks on the left encoder.
 *
 *        This file is not recompiled when you change it. Thus running make
 *        clean is necessary.
 *
 *        IMPORTANT: If you change this file, run make clean to delete old
 *                   binaries. Given that this problem has occurred multiple
 *                   times, I cannot stress that you need to run make clean
 *
 *        TL;DR make clean
**/

#ifndef _CORE_SENSORS_H
#define _CORE_SENSORS_H

#include "API.h"
#include "configuration/sensors.h"

extern Encoder leftEncoder;
extern Encoder rightEncoder;
extern Gyro mainGyro;

inline int readGyro() {
  return -gyroGet(mainGyro);
}

inline void resetMainGyro() {
  gyroReset(mainGyro);
}

inline int readMobileGoalPot() {
  return analogReadCalibrated(MOBILE_GOAL_POT);
}

inline int readLeftDrive() {
  return encoderGet(leftEncoder);
}

inline int readRightDrive() {
  return encoderGet(rightEncoder);
}

inline void resetLeftDriveEncoder() {
  encoderReset(leftEncoder);
}

inline void resetRightDriveEncoder() {
  encoderReset(rightEncoder);
}

inline void resetDriveEncoder() {
  encoderReset(leftEncoder);
  encoderReset(rightEncoder);
}

int getLeftDrive();
int getRightDrive();
int getMobileGoal();
int getGyro();
void resetGyro();
void resetDrive();
void resetLeftDrive();
void resetRightDrive();


#endif

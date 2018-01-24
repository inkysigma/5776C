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
#include "configuration/sensors.h"

#ifndef _CORE_SENSORS_H
#define _CORE_SENSORS_H

#include "API.h"

extern Encoder leftEncoder;
extern Encoder rightEncoder;

inline int readGyro() {
  return (analogReadCalibratedHR(MainGyro) + analogReadCalibratedHR(SecondaryGyro)) / 2;
}

inline int readMobileGoalPot() {
  return analogReadCalibrated(MobileGoalPot);
}

inline int readLeftDrive() {
  return encoderGet(leftEncoder);
}

inline int readRightDrive() {
  return encoderGet(rightEncoder);
}

inline void resetDrive() {
  encoderReset(leftEncoder);
  encoderReset(rightEncoder);
}

#endif
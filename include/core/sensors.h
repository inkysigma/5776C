#ifndef CORE_SENSORS_H
#define CORE_SENSORS_H

#include "API.h"
#include "configuration/sensors.h"

inline int getVertibarPot() {
  return analogRead(VertibarPot);
}

inline int getLiftPot() {
  return analogRead(LiftPot);
}

inline int getMobileGoalPot() {
  return 0;
}

inline int getLeftDrive() {
  int left;
  imeGet(LeftDriveIME, &left);
  return left;
}

inline int getRightDrive() {
  int right;
  imeGet(RightDriveIME, &right);
  return -right;
}

inline void resetDrive() {
  imeReset(LeftDriveIME);
  imeReset(RightDriveIME);
}

inline int getLeftVelocity() {
  int leftv;
  imeGetVelocity(LeftDriveIME, &leftv);
  return leftv;
}

inline int getRightVelocity() {
  int rightv;
  imeGetVelocity(RightDriveIME, &rightv);
  return rightv;
}

extern Gyro mainGyro;

inline void resetGyro() {
  gyroReset(mainGyro);
}

inline int getGyro() {
  return gyroGet(mainGyro);
}


#endif

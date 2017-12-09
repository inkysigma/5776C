#ifndef CORE_SENSORS_H
#define CORE_SENSORS_H

#include "util/JINX.h"
#include "configuration/sensors.h"
#include "API.h"

extern Encoder chainEncoder;
extern Gyro mainGyro;

inline int getLiftPot() {
  return analogRead(LiftPot);
}

inline int getMobileGoalPot() {
  return analogRead(MobileGoalPot);
}


inline int getChainLift() {
  return encoderGet(chainEncoder);
}

inline void resetChainLift() {
  encoderReset(chainEncoder);
}

inline int getGyro() {
  return gyroGet(mainGyro);
}

inline void resetGyro() {
  gyroReset(mainGyro);
}

inline int getLeftDrive() {
  int leftIME;
  imeGet(LeftIME, &leftIME);
  return leftIME;
}

inline int getRightDrive() {
  int rightIME;
  imeGet(RightIME, &rightIME);
  return rightIME;
}

inline void resetDrive() {
  imeReset(LeftIME);
  imeReset(RightIME);
}


#endif

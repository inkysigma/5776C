#ifndef CORE_SENSORS_H
#define CORE_SENSORS_H

#include "util/JINX.h"
#include "configuration/sensors.h"
#include "API.h"

inline int getLiftPot() {
  return analogRead(LiftPot);
}

inline int getMobileGoalPot() {
  return analogRead(MobileGoalPot);
}

extern Encoder chainEncoder;

inline int getChainLift() {
  return encoderGet(chainEncoder);
}

inline void resetChainLift() {
  encoderReset(chainEncoder);
}

extern Gyro mainGyro;

#endif

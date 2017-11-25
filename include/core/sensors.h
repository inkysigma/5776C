#ifndef CORE_SENSORS_H
#define CORE_SENSORS_H

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
  return encoderGet(chainEncoder) / 1.5;
}

inline void resetChainLift() {
  encoderReset(chainEncoder);
}

#endif

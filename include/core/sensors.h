#ifndef CORE_SENSORS_H
#define CORE_SENSORS_H

#include "configuration/sensors.h"
#include "API.h"

inline int getLeftPot() {
  return analogRead(LeftLiftPot);
}

inline int getRightPot() {
  return analogRead(RightLiftPot);
}

inline int getMobileGoalPot() {
  return analogRead(MobileGoalPot);
}
inline int getSwitchLiftPot() {
  return analogRead(SwitchLiftPot);
}

#endif

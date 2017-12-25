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

inline int getLeftDrive() {
  int left;
  imeGet(0, &left);
  return left;
}

inline int getRightDrive() {
  int right;
  imeGet(0, &right);
  return right;
}

inline void resetDrive() {
  imeReset(0);
  imeReset(1);
}

#endif

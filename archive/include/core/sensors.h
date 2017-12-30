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


#endif

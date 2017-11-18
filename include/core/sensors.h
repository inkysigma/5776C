#ifndef CORE_SENSORS_H
#define CORE_SENSORS_H

#include "configuration/sensors.h"
#include "API.h"

void setLiftInit(int left, int right);
int getLeftPot();
int getRightPot();

void setMobileGoalInit(int left, int right);
inline int getMobileGoalPot() {
  return analogRead(MobileGoalPot);
}
int getSwitchLiftPot();

#endif

#ifndef OPS_USEROPS_H
#define OPS_USEROPS_H
#include "core/motors.h"
#include "core/sensors.h"

void retractGoal(void *args);
void openGoal(void *args);
void toggleGoal();
void flashLed(void* args);

#endif

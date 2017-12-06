#ifndef OPS_USEROPS_H
#define OPS_USEROPS_H
#include "core/motors.h"
#include "core/sensors.h"

void initGoal(float kp, float ki, float kd, float dt);
void retractGoal(void *args);
void openGoal(void *args);
void toggleGoal();
void flashLed(void* args);

#endif

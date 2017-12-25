#ifndef PID_LIFT_H
#define PID_LIFT_H

#include "API.h"
#include "pid/pidlib.h"

void setLiftTarget(int target);
void setLiftPidConfig(float kp, float ki, float kd);

void startLiftPid();
void stopLiftPid();

void incrementLift();
void decrementLift();

#endif

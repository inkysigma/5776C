#ifndef PID_LIFT_H
#define PID_LIFT_H

#include "API.h"
#include "pid/pidlib.h"

void setLiftTarget(int left, int right);
void setLiftPidConfig(float lkp, float lki, float lkd, float rkp, float rki,
                      float rkd);

void startLiftPid();
void stopLiftPid();

void incrementLift();
void decrementLift();

#endif

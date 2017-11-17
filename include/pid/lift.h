#ifndef PID_LIFT_PID_H
#define PID_LIFT_PID_H

#include "API.h"
#include "pid/pidlib.h"

void setLiftTargets(int target);
void setLiftPidConfig(pid *left, pid *right);
void startLiftPid();
void stopLiftPid();

#endif

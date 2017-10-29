#ifndef PID_LIFT_PID_H
#define PID_LIFT_PID

#include "API.h"
#include "pid/pidlib.h"

void setLiftTargets(int left, int right);
void setLiftPidConfig(pid *left, pid *right);
void startRightPid();
void startLeftPid();
void stopRightPid();
void stopLeftPid();

#endif

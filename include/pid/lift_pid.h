#ifndef PID_LIFT_PID_H
#define PID_LIFT_PID

#include "API.h"
#include "pid/pidlib.h"

void setLiftPidConfig(pid *left, pid *right);
void startRightPid(int t);
void startLeftPid();
void stopRightPid();
void stopLeftPid();

#endif

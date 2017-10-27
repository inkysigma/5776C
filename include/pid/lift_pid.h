#ifndef PID_LIFT_PID_H
#define PID_LIFT_PID

#include "API.h"
#include "pid/pidlib.h"

extern void setConfig(pid *left, pid *right);
extern void startRightPid(int t);
extern void startLeftPid();
extern void stopRightPid();
extern void stopLeftPid();

#endif

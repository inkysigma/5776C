#ifndef PID_LIFT_PID_H
#define PID_LIFT_PID_H

#include "API.h"
#include "pid/pidlib.h"

void setLiftTarget(int target);
void setLiftPidConfig(pid *lift);
void startLiftPid();
void stopLiftPid();

#endif

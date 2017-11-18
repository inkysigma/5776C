#ifndef PID_VERTIBAR_H
#define PID_VERTIBAR_H

#include "API.h"
#include "pid/pidlib.h"

void holdVertibar(void *arguments);
void setVertTarget(int target);
void setVertibarPidConfig(pid *vertibarPid);
float getVertibarPid();

#endif

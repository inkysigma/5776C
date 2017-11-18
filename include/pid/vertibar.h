#ifndef PID_VERTIBAR_H
#define PID_VERTIBAR_H

#include "API.h"
#include "pid/pidlib.h"

void holdVertibar(void *arguments);
void startVertibarPid();
void stopVertibarPid();
void setVertibarPidConfig(pid *vertibarPid);

#endif

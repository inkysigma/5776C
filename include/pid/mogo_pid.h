#ifndef PID_MOGO_PID_H
#define PID_MOGO_PID_H

#include "API.h"
#include "pid/pidlib.h"
#include "core/motors.h"
#include "core/sensors.h"

extern void setLeftMogoConfig(pid* config);
extern void startLeftMogoControl();

#endif

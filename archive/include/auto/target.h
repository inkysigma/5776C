#ifndef AUTO_LIFTTARGET_H
#define AUTO_LIFTTARGET_H

#include "API.h"
#include "pid/pidlib.h"

extern void setLiftConfig(pid* left, pid* right);
extern void setDriveConfig(pid* left, pid* right);
extern void setSwitchLiftConfig(pid* config);
extern bool targetLiftHeight(int target, int timeout);
extern bool targetDrive(int target, int timeout);
extern bool targetSwitchLift(int target, int timeout);
#endif

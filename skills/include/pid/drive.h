#ifndef _PID_DRIVE_H
#define _PID_DRIVE_H
#include "API.h"

void setDriveTarget(int left, int right);
void updateDriveTargets();
void resetDriveFeedback();
bool isDriveConfident();

#endif
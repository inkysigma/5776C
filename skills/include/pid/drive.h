#ifndef _PID_DRIVE_H
#define _PID_DRIVE_H

void setDriveTarget(int left, int right);

void updateDriveTargets();

void resetDriveFeedback();

#endif
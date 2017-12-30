#ifndef OPS_AUTOPS_H
#define OPS_AUTOPS_H
#include "API.h"

void setRightDrivePid(float kp, float ki, float kd, float dt);
void setLeftDrivePid(float kp, float ki, float kd, float dt);
void setDriveTarget(float left, float right);
void startDrivePid();
void stopDrivePid();
void resetDrivePid();

void incrementLeftDrivePid(int amt);
void incrementRightDrivePid(int amt);

#endif

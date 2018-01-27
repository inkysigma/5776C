#ifndef _PID_LEFT_H
#define _PID_LEFT_H
#include "API.h"

void initLeftDriveFeedback(float kp, float ki, float kd, float min_i, float max_i);

void setLeftDriveGoal(float target);
void resetLeftDriveFeedback();
void updateLeftDriveCompletion();
void startLeftDriveFeedback();
void stopLeftDriveFeedback();

bool isLeftConfident();
bool isLeftRunning();

#endif

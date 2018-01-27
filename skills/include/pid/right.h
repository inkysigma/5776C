#ifndef _PID_RIGHT_H
#define _PID_RIGHT_H
#include "API.h"

void initRightDriveFeedback(float kp, float ki, float kd, float min_i, float max_i);

void setRightDriveGoal(float target);
void resetRightDriveFeedback();
void updateRightDriveCompletion();
void startRightDriveFeedback();
void stopRightDriveFeedback();

bool isRightConfident();
bool isRightRunning();

#endif

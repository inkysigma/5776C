#ifndef _PID_RIGHT_H
#define _PID_RIGHT_H
#include "API.h"

void initRightDriveFeedback(float kp, float ki, float kd, float min_i,
                            float max_i);

void setRightDriveGoal(float target);
void resetRightDriveFeedback();
void updateRightDriveCompletion();
void startRightDriveFeedback();
void stopRightDriveFeedback();
void pauseRightDriveFeedback();

bool isRightConfident();
bool isRightRunning();

float stepRightPid();

bool isRightWithin(int distance);

#endif

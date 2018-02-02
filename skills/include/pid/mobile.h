#ifndef _PID_MOBILE_H
#define _PID_MOBILE_H
#include "API.h"

void initMobileGoalFeedback(float kp, float ki, float kd, float min_i, float max_i);
void setMobileGoalDriveGoal(float target);
void resetMobileGoalDriveFeedback();
void updateMobileGoalDriveCompletion();
void startMobileGoalDriveFeedback();
void stopMobileGoalDriveFeedback();
void pauseMobileGoalDriveFeedback();

bool isMobileGoalConfident();
bool isMobileGoalRunning();

#endif

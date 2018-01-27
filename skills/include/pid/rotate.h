#ifndef _PID_ROTATE_H
#define _PID_ROTATE_H
#include "API.h"

void initRotateFeedback(float kp, float ki, float kd, float min_i, float max_i);

void setRotateDriveGoal(float target);
void resetRotateDriveFeedback();
void updateRotateDriveCompletion();
void startRotateFeedback();
void stopRotateFeedback();

bool isRotateConfident();
bool isRotateRunning();

#endif

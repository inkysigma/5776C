#ifndef _PID_LEFT_H
#define _PID_LEFT_H
#include "API.h"

/**
 * @method left/initLeftDriveFeedback
 * @brief Initializes the parameters of the PID on the left drive
 * @param kp the proportional constant to multiply the error by.
 **/
void initLeftDriveFeedback(float kp, float ki, float kd, float min_i,
                           float max_i);

void setLeftDriveGoal(float target);
void resetLeftDriveFeedback();
void updateLeftDriveCompletion();

void startLeftDriveFeedback();
void stopLeftDriveFeedback();
bool isLeftRunning();

bool isLeftConfident();

float stepLeftPid();

bool isLeftWithin(int distance);

#endif

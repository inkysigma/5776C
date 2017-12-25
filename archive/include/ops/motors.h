#ifndef OPS_MOTOR_OPS_H
#define OPS_MOTOR_OPS_H

#include "core/motors.h"
#include "core/sensors.h"
#include "util/concurrency.h"
#include "API.h"

#define MOGO_OUT 4048
#define MOGO_IN 1000

void setClaw(int pos);
void setLift(int pos);
void openClawFully();
void closeClawFully(bool stall);
void lowerLiftTo(int lift);
void toggleClawOpen(bool stall);
void resetClaw();
void resetClawState();
void openGoal();
void retractGoal();
void toggleGoal();

#endif

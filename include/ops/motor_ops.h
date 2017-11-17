#ifndef OPS_MOTOR_OPS_H
#define OPS_MOTOR_OPS_H

#include "core/motors.h"
#include "core/sensors.h"
#include "util/concurrency.h"
#include "API.h"

void raiseClaw();
void lowerClaw();
void raiseLift(int left, int right, bool stall);
void lowerLift();
void lowerClawPartial();
void raiseClawPartial(bool stall);
void openClawFully();
void closeClawFully(bool stall);
void lowerLiftTo(int left, int right);
void toggleClawOpen(bool stall);

extern bool claw_open;

#endif

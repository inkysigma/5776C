#ifndef OPS_MOTOR_OPS_H
#define OPS_MOTOR_OPS_H

#include "core/motors.h"
#include "core/sensors.h"
#include "util/concurrency.h"
#include "API.h"

void raiseClaw(int pos);
void lowerClaw(int pos);
void raiseLift(int lift);
void lowerLift();
void lowerClawPartial();
void raiseClawPartial(bool stall);
void openClawFully();
void closeClawFully(bool stall);
void lowerLiftTo(int lift);
void toggleClawOpen(bool stall);
void resetClaw();
void resetClawState();

extern bool claw_open;

#endif

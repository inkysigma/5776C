#ifndef OPS_MOTOR_OPS_H
#define OPS_MOTOR_OPS_H

#include "core/motors.h"
#include "core/sensors.h"
#include "util/concurrency.h"
#include "API.h"

#define CONE_POT_HEIGHT 90
#define CONE_POT_CONST 20
#define CONE_RELEASE_CONST 50

#define LOW_SWITCH_POT 1300
#define HIGH_SWITCH_POT 200
#define MID_SWITCH_POT 1000
#define POWER_SWITCH_POT 800

#define OPEN_CLAW_TIME 80
#define CLOSE_CLAW_TIME 70

#define OUT_ANGLE 90
#define IN_ANGLE 0
#define FAST_SPEED 100
#define SLOW_ANGLE 45
#define SLOW_SPEED 50
#define SYNC_SPEED 15

/**
void raiseLiftTo(int cone_level, bool stall);
void lowerLiftTo(int cone_level, bool stall);
void lowerClawPartial(bool stall);
void raiseClawPartial(bool stall);
void closeClawFully();
=======
void moveLiftTo(int cone_level);
void lowerClawPartial();
void raiseClawPartial();
>>>>>>> 731ed01cfc8b63877281b40e52c43743a11e8379
void releaseCone(bool close);
void lowerClawFully();
void raiseClawFully();
void closeClawFully();
void openClawFully();
void moveMogoIn();
void moveMogoIn();
void syncMogo();**/

void raiseClaw();
void lowerClaw();
void raiseLift(int left, int right, bool stall);
void lowerLift();
void raiseClawPartial(bool stall);
void openClawFully();
void closeClawFully(bool stall);

extern bool claw_open;

#endif

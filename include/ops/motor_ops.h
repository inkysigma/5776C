#ifndef OPS_MOTOR_OPS_H
#define OPS_MOTOR_OPS_H

#include "core/motors.h"
#include "core/sensors.h"
#include "util/concurrency.h"
#include "API.h"

#define CONE_POT_HEIGHT 90
#define CONE_POT_CONST 20
#define CONE_RELEASE_CONST 50

#define LOW_SWITCH_POT 3400
#define HIGH_SWITCH_POT 1770
#define MID_SWITCH_POT 2950
#define POWER_SWITCH_POT 2800

#define OPEN_CLAW_TIME 80
#define CLOSE_CLAW_TIME 70

#define OUT_ANGLE 90
#define IN_ANGLE 0
#define FAST_SPEED 100
#define SLOW_ANGLE 45
#define SLOW_SPEED 50
#define SYNC_SPEED 15

extern void raiseLiftTo(int cone_level, bool stall);
extern void lowerLiftTo(int cone_level, bool stall);
extern void lowerClawPartial(bool stall);
extern void raiseClawPartial(bool stall);
extern void closeClawFully();
extern void releaseCone(bool close);
extern void lowerClawFully();
extern void raiseClawFully(bool stall);
extern void openClawFully();
extern void moveMogoIn();
extern void moveMogoIn();
extern void syncMogo();

#endif

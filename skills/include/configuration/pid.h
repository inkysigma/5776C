#ifndef _PID_H
#define _PID_H

#include "fbc.h"

#define LEFT_DRIVE_KP 0.26
#define LEFT_DRIVE_KI 0
#define LEFT_DRIVE_KD 15
#define LEFT_DRIVE_MAX_I 40
#define LEFT_DRIVE_MIN_I -40
#define LEFT_DRIVE_DT 20

#define RIGHT_DRIVE_KP 0.07
#define RIGHT_DRIVE_KI 0
// #define RIGHT_DRIVE_KI 0.0008
#define RIGHT_DRIVE_KD 0.074
#define RIGHT_DRIVE_MAX_I 30
#define RIGHT_DRIVE_MIN_I -30
#define RIGHT_DRIVE_DT 20

#define MOBILE_GOAL_KP 2
#define MOBILE_GOAL_KI 0
#define MOBILE_GOAL_KD 10
#define MOBILE_GOAL_MAX_I 40
#define MOBILE_GOAL_MIN_I -40
#define MOBILE_GOAL_DT 20

#define ROTATE_KP 0.4
#define ROTATE_KI 0
#define ROTATE_KD 40
#define ROTATE_MAX_I 40
#define ROTATE_MIN_I -40
#define ROTATE_DT 20

#endif

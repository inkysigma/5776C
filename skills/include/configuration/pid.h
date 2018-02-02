#ifndef _PID_H
#define _PID_H

#include "fbc.h"

#define LEFT_DRIVE_KP 0.7
#define LEFT_DRIVE_KI 0
#define LEFT_DRIVE_KD 1.1
#define LEFT_DRIVE_MAX_I 40
#define LEFT_DRIVE_MIN_I -40
#define LEFT_DRIVE_DT 20

#define RIGHT_DRIVE_KP 0.7
#define RIGHT_DRIVE_KI 0
#define RIGHT_DRIVE_KD 1.1
#define RIGHT_DRIVE_MAX_I 30
#define RIGHT_DRIVE_MIN_I -30
#define RIGHT_DRIVE_DT 20

#define MOBILE_GOAL_KP 0.4
#define MOBILE_GOAL_KI 0.1
#define MOBILE_GOAL_KD 0.2
#define MOBILE_GOAL_MAX_I 45
#define MOBILE_GOAL_MIN_I -45
#define MOBILE_GOAL_DT 20

#define ROTATE_KP 0.4
#define ROTATE_KI 0
#define ROTATE_KD 40
#define ROTATE_MAX_I 40
#define ROTATE_MIN_I -40
#define ROTATE_DT 20

#endif

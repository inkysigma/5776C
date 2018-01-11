#ifndef OPERATIONS_AUTONOMOUS_H
#define OPERATIONS_AUTONOMOUS_H
#ifndef MOTOR_H
#include "../motors.h"
#endif
#ifndef PID_VERT_C
#include "../pid/vertibar.c"
#endif
#ifndef UTIL_MATH_H
#include "../util/math.h"
#endif

bool setLift(int target, int timeout) {
	setLiftTarget(target);
	clearTimer(T1);
	waitUntil(within(SensorValue[lift], target, 70) || time1[T1] > timeout);
	return time1[T1] > timeout;
}

bool setVertibar(int target, int timeout) {
	setVertibarTarget(target);
	clearTimer(T1);
	waitUntil(within(SensorValue[vertibar], target, 60) || time1[T1] > timeout);
	return time1[T1] > timeout;
}

#endif

#ifndef OPERATIONS_AUTONOMOUS_H
#define OPERATIONS_AUTONOMOUS_H
#include "../motors.h"
#include "../pid/vertibar.c"
#include "../util/math.h"

void liftVertibarCompletely(bool pidenabled) {
	if (pidenabled) {
		setVertibarTarget(1165);
		return;
	}
	moveVertibar(100);
	delay(1300);
	moveVertibar(20);
}

void lowerVertibarCompletely(bool pidenabled) {
	if (pidenabled) {
		setVertibarTarget(3677);
		return;
	}
	moveVertibar(-100);
	delay(1300);
	moveVertibar(-10);
}

bool setLift(int target, int timeout) {
	setLiftTarget(target);
	clearTimer(T1);
	waitUntil(within(SensorValue[lift], target, 40) || time1[T1] > timeout);
	return time1[T1] > timeout;
}

bool setVertibar(int target, int timeout) {
	setVertibarTarget(target);
	clearTimer(T1);
	waitUntil(within(SensorValue[vertibar], target, 40) || time1[T1] > timeout);
	return time1[T1] > timeout;
}

#endif

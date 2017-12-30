#ifndef CORE_MOTOR_H
#define CORE_MOTOR_H

#include "configuration/motors.h"
#include "API.h"
#include "util/math.h"

inline void moveDrive(int left, int right) {
	motorSet(LeftDrive, bound(left, 127, -127));
	motorSet(RightDrive, -bound(right, 127, -127));
}

inline void rotateDrive(int speed) {
	motorSet(LeftDrive, bound(speed, 127, -127));
	motorSet(RightDrive, -bound(speed, 127, -127));
}

inline void moveLift(int power) {
	motorSet(LeftLift, bound(power, 127, -127));
	motorSet(RightLift, -bound(power, 127, -127));
}

inline void openClaw(int power) {
	motorSet(Claw, power);
}

inline void closeClaw(int power) {
	motorSet(Claw, -power);
}

inline void moveSwitchLift(int power) {
	// set the power on the motor of the vertibar. positive is open
	motorSet(Vertibar, -power);
}

inline void lowerSwitchLift(int power) {
	// move the switch lift until it rotates the other way
	moveSwitchLift(power);
}

inline void raiseSwitchLift(int power) {
	moveSwitchLift(-power);
}

inline void moveGoal(int power) {
	motorSet(LeftMobileGoal, bound(power, 127, -127));
	motorSet(RightMobileGoal, -bound(power, 127, -127));
}

#endif

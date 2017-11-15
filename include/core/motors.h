#ifndef CORE_MOTOR_H
#define CORE_MOTOR_H

#include "configuration/motors.h"
#include "API.h"

#define LEVEL_CHANGE 30

inline void moveDrive(int left, int right) {
	motorSet(LeftDrive, left);
	motorSet(RightDrive, -right);
}

inline void rotateDrive(int speed) {
	motorSet(LeftDrive, speed);
	motorSet(RightDrive, speed);
}

inline void moveLeftLift(int power) {
	motorSet(LeftLift, -power);
}

inline void moveRightLift(int power) {
	motorSet(RightLift, power);
}

inline void moveLift(int power) {
	moveLeftLift(power);
	moveRightLift(power);
}

inline void applyStall() {
	moveLift(15);
}

inline void openClaw(int power) {
	motorSet(Claw, -power);
}

inline void closeClaw(int power) {
	openClaw(-power);
}

inline void stopClaw() {
	openClaw(0);
}

inline void moveSwitchLift(int power) {
	motorSet(SwitchLift, power);
}

inline void lowerClaw(int power) {
	// move the switch lift until it rotates the other way
	moveSwitchLift(-power);
}

inline void raiseClaw(int power) {
	moveSwitchLift(power);
}

inline void moveGoal(int power) {
	motorSet(LeftMobileGoal, -power);
	motorSet(RightMobileGoal, power);
}

#endif

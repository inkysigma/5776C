#ifndef CORE_MOTOR_H
#define CORE_MOTOR_H
#include "configuration/motors.h"
#include "API.h"

#define LEVEL_CHANGE 30

void moveSwitchLift(int power);

void moveDrive(int left, int right) {
	motorSet(LeftDrive, left);
	motorSet(RightDrive, -right);
}

void rotateDrive(int speed) {
	motorSet(LeftDrive, speed);
	motorSet(RightDrive, speed);
}

void moveLeftLift(int power) {
	motorSet(LeftLift, -power);
}

void moveRightLift(int power) {
	motorSet(RightLift, power);
}

void moveLift(int power) {
	moveLeftLift(power);
	moveRightLift(power);
}

void applyStall() {
	moveLift(15);
}

void openClaw(int power) {
	motorSet(Claw, -power);
}

void closeClaw(int power) {
	openClaw(-power);
}

void stopClaw() {
	openClaw(0);
}

void moveSwitchLift(int power) {
	motorSet(SwitchLift, -power);
}

void lowerClaw(int power) {
	// move the switch lift until it rotates the other way
  moveSwitchLift(power);
}

void raiseClaw(int power) {
	moveSwitchLift(-power);
}

void moveLeftMogo(int power) {
	motorSet(LeftMobileGoal, power);
}

void moveRightMogo(int power) {
	motorSet(RightMobileGoal, -power);
}

void moveGoal(int power) {
	moveLeftMogo(power);
	moveRightMogo(power);
}


#endif

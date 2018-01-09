#ifndef MOTOR_H
#define MOTOR_H
void moveLift(int power) {
	motor[port9] = -power;
	motor[port8] = power;
}

void moveVertibar(int power) {
	motor[lVertibar] = -power;
	motor[rVertibar] = -power;
}

void openClaw(int power) {
	motor[claw] = power;
}
#endif

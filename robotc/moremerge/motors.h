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

void moveMobileGoal(int power) {
	motor[port2] = power;
}

void resetGyro() {
	SensorValue[gyro] = 0;
}

void moveDrive(int left, int right) {
	motor[rDrive] = left;
	motor[lDrive] = -right;
}

void resetDriveIME() {
	SensorValue[LeftDrive] = 0;
	SensorValue[RightDrive] = 0;
}
#endif

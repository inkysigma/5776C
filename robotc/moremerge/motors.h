#ifndef MOTOR_H
#define MOTOR_H

//set lift motors to "power"
void moveLift(int power) {
	motor[port9] = -power;
	motor[port8] = power;
}

//set vertibar motors to "power"
void moveVertibar(int power) {
	motor[lVertibar] = -power;
	motor[rVertibar] = -power;
}

//set claw to "power"
void openClaw(int power) {
	motor[claw] = -power;
}

void moveMobileGoal(int power) {
	motor[port2] = power;
}

//set gyro sensor value to 0
void resetGyro() {
	SensorValue[gyro] = 0;
}

//set drive left and right motors separately
void moveDrive(int left, int right) {
	motor[rDrive] = left;
	motor[lDrive] = -right;
}

//set drive encoders to 0
void resetDriveIME() {
	SensorValue[LeftDrive] = 0;
	SensorValue[RightDrive] = 0;
}
#endif


void resetGyro() {
	SensorValue[gyro] = 0;
}

bool within(float a, float b, float margin) {
	return abs(a - b) < margin;
}

void moveMobileGoal(int power) {
	motor[port2] = power;
	motor[port3] = -power;
}

void moveDrive(int left, int right) {
	motor[port5] = left;
	motor[port4] = -right;
}

void resetDriveIME() {
	SensorValue[LeftDrive] = 0;
	SensorValue[RightDrive] = 0;
}

void moveLift(int power) {
	motor[port9] = -power;
	motor[port8] = power;
}

void moveVertibar(int power) {
	motor[vertibar] = -power;
}

void openClaw(int power) {
	motor[claw] = power;
}


void defensive() {
	moveDrive(127, 127);
	delay(4000);
	moveDrive(-10, -10);
	delay(100);
	moveDrive(0, 0);
}

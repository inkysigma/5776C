
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


void twenty() {
	resetDriveIME();
	moveLift(100);
	waitUntil(SensorValue[lift] > 1500);
	moveMobileGoal(127);
	waitUntil(SensorValue[mobogo] > 1433);
	moveMobileGoal(0);
	moveLift(60);
	delay(900);
	moveDrive(127, 127);
	moveLift(0);
	waitUntil(within(SensorValue[LeftDrive], 1380, 40) || within(SensorValue[RightDrive], -1380, 40));
	moveDrive(0, 0);
	delay(500);
	moveMobileGoal(-100);
	waitUntil(within(SensorValue[mobogo], 0, 20));
	moveMobileGoal(0);

	// attempt to return to base
	moveDrive(-90, -90);
	waitUntil(within(SensorValue[LeftDrive], 170, 80));
	moveDrive(0, 0);
	delay(400);
	resetGyro();
	moveDrive(127, -127);
	while (!within(SensorValue[gyro], -1000, 30)) { moveDrive((1000 + SensorValue[gyro]), -(SensorValue[gyro] + 1000)); }
	moveDrive(60, 60);
	waitUntil(within(SensorValue[LeftDrive], 100, 40));
	moveDrive(0, 0);

	// attempt to score in twenty point zone
	delay(400);
	resetGyro();
	delay(400);
	while (!within(SensorValue[gyro], -890, 40)) { moveDrive((890 + SensorValue[gyro]), -(SensorValue[gyro] + 890)); }
	moveDrive(-30, 30);
	delay(400);
	moveDrive(0, 0);


	moveDrive(127, 127);
	clearTimer(T1);
	waitUntil(within(SensorValue[LeftDrive], 1230, 10) || time1[T1] > 2500);
	moveDrive(0, 0);

	moveMobileGoal(100);
	waitUntil(within(SensorValue[mobogo], 504, 40));
	moveMobileGoal(-20);

	moveDrive(-100, -100);
	clearTimer(T1);
	waitUntil(within(SensorValue[LeftDrive], -40, 70) || time1[T1] > 1000);
	moveDrive(0, 0);
	moveMobileGoal(0);
}

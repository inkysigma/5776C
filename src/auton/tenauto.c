
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

void ten() {
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
	waitUntil(within(SensorValue[LeftDrive], 1460, 40));
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
	moveDrive(-127, 127);
	while (!within(SensorValue[gyro], 1800, 30)) { moveDrive(-(1800 + SensorValue[gyro]), (SensorValue[gyro] + 1800)); }
	moveDrive(0, 0);
	delay(400);
	moveDrive(30, 50);
	clearTimer(T1);
	waitUntil(within(SensorValue[LeftDrive], 20, 40) || time1[T1] > 1500);
	moveDrive(-10, -10);

	// attempt to score in ten point zone
	moveMobileGoal(100);
	waitUntil(within(SensorValue[mobogo], 1443, 20));
	moveMobileGoal(-20);

	moveDrive(-120, -120);
	moveMobileGoal(-100);
	delay(500);
	moveMobileGoal(0);
	clearTimer(T1);
	waitUntil(within(SensorValue[LeftDrive], 0, 30) || time1[T1] > 200);
	delay(300);
	moveDrive(10, 10);
	delay(400);
	moveDrive(0, 0);
}

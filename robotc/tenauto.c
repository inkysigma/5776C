
void resetGyro() {
	SensorValue[gyro] = 0;
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

void ten() {
	resetGyro();
	openClaw(-20);
	moveVertibar(40);
	resetDriveIME();
	moveLift(100);
	waitUntil(SensorValue[lift] > 1500);
	moveMobileGoal(127);
	moveLift(60);
	delay(900);
	moveDrive(100, 100);
	moveLift(0);
	waitUntil(SensorValue[mobogo] > 3110);
	moveMobileGoal(-10);
	waitUntil(within(SensorValue[LeftDrive], 1380, 40) || within(SensorValue[RightDrive], -1380, 40));
	moveDrive(0, 0);
	delay(500);
	moveMobileGoal(-100);
	waitUntil(within(SensorValue[mobogo], 1300, 20));
	moveMobileGoal(0);

	moveLift(-100);
	waitUntil(within(SensorValue[lift], 1200, 40));
	moveLift(10);
	openClaw(100);
	delay(400);
	openClaw(0);
	moveLift(100);


	// attempt to return to base
	moveDrive(-90, -90);
	waitUntil(SensorValue[lift] > 1500);
	moveLift(0);
	waitUntil(within(SensorValue[LeftDrive], 300, 80));
	moveDrive(0, 0);
	delay(400);
	resetGyro();
	while (!within(SensorValue[gyro], -1700, 30)) { moveDrive(0.6 * (1800 + SensorValue[gyro]), -0.6 * (SensorValue[gyro] + 1800)); }
	moveDrive(-20, 20);
	delay(400);
	moveDrive(0, 0);

	// attempt to score in ten point zone
	moveLift(100);
	waitUntil(within(SensorValue[lift], 1700, 40));
	moveLift(0);
	moveMobileGoal(100);
	waitUntil(within(SensorValue[mobogo], 3110, 20));
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

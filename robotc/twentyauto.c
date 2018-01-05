
void resetGyro() {
	SensorValue[gyro] = 0;
}

void moveMobileGoal(int power) {
	motor[port2] = power;
}

void moveDrive(int left, int right) {
	motor[port5] = left;
	motor[port4] = -right;
}

void resetDriveIME() {
	SensorValue[LeftDrive] = 0;
	SensorValue[RightDrive] = 0;
}

void twenty() {
	resetGyro();
	openClaw(-20);
	moveVertibar(50);
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
	while (!within(SensorValue[gyro], 450, 30)) { moveDrive(-0.6 * (450 + SensorValue[gyro]), 0.6 * (SensorValue[gyro] + 450)); }
	moveDrive(20, -20);
	moveDrive(-70, -70);
	resetDriveIME();
	waitUntil(within(SensorValue[LeftDrive], -200, 40));
	moveDrive(0, 0);

	// attempt to score in twenty point zone
	delay(400);
	resetGyro();
	delay(400);
	while (!within(SensorValue[gyro], 890, 40)) { moveDrive(- 0.7 * (890 + SensorValue[gyro]), 0.7 * (SensorValue[gyro] + 890)); }
	moveDrive(30, -30);
	delay(400);
	moveDrive(0, 0);


	moveLift(100);
	moveDrive(127, 127);
	resetDriveIME();
	clearTimer(T1);
	waitUntil(SensorValue[lift] > 1800);
	moveLift(0);
  waitUntil(within(SensorValue[LeftDrive], 1230, 10) || time1[T1] > 2500);
	moveDrive(0, 0);

	moveMobileGoal(100);
	waitUntil(within(SensorValue[mobogo], 2650, 20));
	moveMobileGoal(-20);

	moveDrive(-120, -120);
	clearTimer(T1);
	resetDriveIME();
	waitUntil(within(SensorValue[LeftDrive], -700, 70) || time1[T1] > 1000);
	moveDrive(0, 0);
	moveMobileGoal(0);
}

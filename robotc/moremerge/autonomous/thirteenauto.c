void resetGyro() {
	SensorValue[gyro] = 0;
}

void moveDrive(int left, int right) {
	motor[port5] = left;
	motor[port4] = -right;
}

void resetDriveIME() {
	SensorValue[LeftDrive] = 0;
	SensorValue[RightDrive] = 0;
}

const int blue = 1;

void thirteen() {
	resetDriveIME();
	openClaw(-30);

	// replace with PID holding at some specific, high height
	moveLift(100);
	delay(500);
	moveLift(20);

	// extend mogo intake
	moveMobileGoal(127);
	waitUntil(SensorValue[mobogo] > 3110);
	moveMobileGoal(0);

	// collect mogo
	moveDrive(127, 127);
	waitUntil(within(SensorValue[LeftDrive], 1520, 40));

	moveDrive(-50, -50);
	wait1Msec(30);
	moveDrive(0, 0);

	// withdraw mogo intake
	moveMobileGoal(-127);
	waitUntil(SensorValue[mobogo] < 1310);
	moveMobileGoal(0);

	// make lift come down
	moveLift(-50);
	delay(400);
	moveLift(0);

	// release preload cone
	openClaw(40);
	delay(300);
	openClaw(0);

	// reset the claw
	moveLift(100);
	delay(100);
	moveVertibar(-500);
	delay(250);
	moveLift(-100);
	moveVertibar(0);
	delay(250);
	moveLift(0);

	// collect cone behind, raise lift up
	resetDriveIME();
	moveDrive(70, 70);
	waitUntil(within(SensorValue[LeftDrive], 370, 40));
	moveDrive(-10, -10);
	delay(300);
	moveDrive(0, 0);

	openClaw(-127);
	delay(250);
	openClaw(-40);

	// replace with PID holding at some specific, high height enough to score on stago
	moveVertibar(50);
	moveLift(100);
	delay(1000);
	moveVertibar(0);
	moveLift(20);

	// go backwards, rotate 135 degrees, score on stationary goal
	resetDriveIME();
	moveDrive(-117, -127);
	clearTimer(T1);
	waitUntil(within(SensorValue[LeftDrive], -1830, 40)||time1[T1]>4000);
	moveDrive(0, 0);


	// rotate for stat go
	resetGyro();
	while (!within(SensorValue[gyro], -blue * 900, 40)) { moveDrive(blue * 0.7 * (900 + SensorValue[gyro]), -blue * 0.7 * (SensorValue[gyro] + 900)); }
	moveDrive(-10 * blue, 10 * blue);
	delay(200);
	moveDrive(0, 0);


	// drive into stago
	moveDrive(127, 127);
	delay(1100);
	moveDrive(0, 0);

	// come down on stago
	moveLift(-100);
	delay(300);
	moveLift(0);
	openClaw(40);
	delay(250);
	openClaw(0);
	delay(20);

	//rotate for mogo and lift
	moveVertibar(100);
	moveLift(30);
	delay(400);
	moveVertibar(20);

	moveDrive(-127, -127);
	delay(40);
	moveDrive(0,0);

	resetGyro();

	while (!within(SensorValue[gyro], -800, 40)) { moveDrive(- 0.7 * (-800 + SensorValue[gyro]), 0.7 * (SensorValue[gyro] + -800)); }
	moveDrive(70, -70);
	delay(400);
	moveDrive(0, 0);

	//lineup to score mogo
	moveDrive(127, 127);
	delay(120);
	moveDrive(0,0);

	// extend mogo intake
	moveVertibar(100);
	moveLift(80);
	moveMobileGoal(127);
	waitUntil(SensorValue[mobogo] > 3110);
	moveMobileGoal(0);
	moveDrive(-127,-127);
	delay(1000);
	moveDrive(0,0);

}

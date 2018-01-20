#ifndef AUTO_TEN_C
#define AUTO_TEN_C

#ifndef MOTOR_H
#include "../motors.h"
#endif

void ten() {
	// initialization tasks
	moveLift(127);
	resetDriveIME();
	openClaw(-20);
	moveVertibar(5);
	delay(200);
	moveMobileGoal(127);
	waitUntil(SensorValue[lift] > 1400);

	// begin moving the mobile goal after the lift is sufficiently high
	moveLift(30);
	moveDrive(65, 77);
	waitUntil(SensorValue[lift] > 1500);
	while (SensorValue[mobogo] < 2920) moveMobileGoal(1.1 * (2930 - SensorValue[mobogo]));
	moveDrive(115, 127);
	moveMobileGoal(10);

	waitUntil(within(SensorValue[LeftDrive], 1620, 20) || SensorValue[LeftDrive] > 1660);
	moveDrive(-10, -10);
	delay(300);
	moveDrive(0, 0);
	moveMobileGoal(-127);
	waitUntil(within(SensorValue[mobogo], 1300, 20));
	moveMobileGoal(0);

	// drop the first cone into its place
	moveLift(-75);
	waitUntil(within(SensorValue[lift], 1200, 40));
	moveLift(10);
	openClaw(100);
	delay(400);
	openClaw(10);
	moveLift(100);

	// collect cone behind, raise lift up
	resetDriveIME();
	waitUntil(within(SensorValue[lift], 1350, 20) || SensorValue[lift] > 1350);
	moveLift(30);
	moveVertibar(-100);
	waitUntil(within(SensorValue[vertibar], 2820, 20) || SensorValue[vertibar] > 2830);
	moveVertibar(-10);
	moveLift(-100);
	waitUntil(within(SensorValue[lift], 1100, 20) || SensorValue[lift] < 1090);
	moveLift(-10);

	moveDrive(85, 85);
	waitUntil(within(SensorValue[LeftDrive], 390, 40));
	moveDrive(0, 0);

	openClaw(-127);
	delay(300);
	openClaw(-40);

	//attempt to score second cone
	moveDrive(-127, -127);
	moveLift(127);
	bool vertibarPassed = false;
	bool liftPassed = false;
	clearTimer(T1);
	while ((!vertibarPassed || !liftPassed) && time1[T1] < 2500) {
		if (within(SensorValue[vertibar], 545, 30) || SensorValue[vertibar] < 530) {
			moveVertibar(0);
			vertibarPassed = true;
		}
		if (within(SensorValue[lift], 1706, 20)) {
			moveLift(20);
			if (!vertibarPassed) moveVertibar(100);
			liftPassed = true;
		}
	}
	moveLift(-80);
	clearTimer(T1);
	waitUntil(SensorValue[lift] < 1200 && time1[T1] < 1000);
	openClaw(127);
	delay(300);
	moveLift(127);
	openClaw(10);

	// attempt to return to base
	moveDrive(-127, -127);
	waitUntil(SensorValue[lift] > 1500);
	moveLift(20);
	waitUntil(within(SensorValue[LeftDrive], -1500, 80));
	moveDrive(20, 20);
	delay(100);
	moveDrive(0, 0);
	resetGyro();
	delay(400);
	resetGyro();
#if BLUE
	while (!within(SensorValue[gyro], -2000, 30)) { moveDrive(0.6 * (2600 + SensorValue[gyro]), -0.6 * (SensorValue[gyro] + 2600)); }
#else
	while (!within(SensorValue[gyro], 2000, 30)) { moveDrive(- 0.6 * (2600 - SensorValue[gyro]), 0.6 * (2600 - SensorValue[gyro]));
#endif
		moveDrive(-20, 20);
		delay(400);
		moveDrive(0, 0);

		// attempt to score in ten point zone
		moveMobileGoal(100);
		waitUntil(within(SensorValue[mobogo], 2980, 40));
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

#endif

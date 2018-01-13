#ifndef AUTO_TWENTY_C
#define AUTO_TWENTY_C

#ifndef MOTOR_H
#include "../motors.h"
#endif
#ifndef CONFIGURATION_H
#include "../configuration.h"
#endif

void twenty() {
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
	while (SensorValue[mobogo] < 3035) moveMobileGoal(1.1 * (3100 - SensorValue[mobogo]));
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
	waitUntil(within(SensorValue[vertibar], 3380, 20) || SensorValue[vertibar] > 3390);
	moveVertibar(-10);
	moveLift(-100);
	waitUntil(within(SensorValue[lift], 1140, 20) || SensorValue[lift] < 1100);
	moveLift(-10);

	moveDrive(85, 85);
	waitUntil(within(SensorValue[LeftDrive], 390, 40));
	moveDrive(0, 0);

	openClaw(-127);
	delay(300);
	openClaw(-40);

	//attempt to score second cone
	moveVertibar(70);
	moveDrive(-127, -127);
	moveLift(127);
	bool vertibarPassed = false;
	bool liftPassed = false;
	clearTimer(T1);
	while (!vertibarPassed && !liftPassed && time1[T1] < 2500) {
		if (within(SensorValue[vertibar], 1060, 60)) {
			moveVertibar(5);
			vertibarPassed = true;
		}

		if (within(SensorValue[lift], 1506, 20)) {
			moveLift(20);
			if (!vertibarPassed) moveVertibar(100);
			liftPassed = true;
		}
	}
	moveLift(-80);
	clearTimer(T1);
	waitUntil(SensorValue[lift] < 1200 && time1[T1] < 1000);
	openClaw(127);
	moveLift(127);
	openClaw(10);

	// attempt to return to base
	moveDrive(-127, -127);
	waitUntil(SensorValue[lift] > 1500);
	moveLift(20);
	waitUntil(within(SensorValue[LeftDrive], -1700, 80));
	moveDrive(20, 20);
	delay(100);
	moveDrive(0, 0);
	resetGyro();

	// rotate to prepare to score in 20 point zone
#if BLUE==1
	while (!within(SensorValue[gyro], 450, 30)) { moveDrive(-0.6 * (450 + SensorValue[gyro]), 0.6 * (SensorValue[gyro] + 450)); }
#else
	while (!within(SensorValue[gyro], -450, 30)) { moveDrive(0.6 * (450 + SensorValue[gyro]), - 0.6 * (SensorValue[gyro] + 450)); }
#endif
	moveDrive(20, -20);
	delay(30);
	moveDrive(-100, -100);
	resetDriveIME();
	waitUntil(within(SensorValue[LeftDrive], -270, 40));
	moveDrive(10, 10);
	delay(100);
	moveDrive(0, 0);

	// attempt to score in twenty point zone
	resetGyro();
#if BLUE==1
	while (!within(SensorValue[gyro], 890, 40)) { moveDrive(- 0.7 * (890 + SensorValue[gyro]), 0.7 * (SensorValue[gyro] + 890)); }
	moveDrive(40, -40);
#else
	while (!within(SensorValue[gyro], -890, 40)) { moveDrive(0.7 * (890 + SensorValue[gyro]), -0.7 * (SensorValue[gyro] + 890)); }
	moveDrive(-40, 40);
#endif
	delay(100);
	moveDrive(0, 0);


	moveLift(100);
	moveDrive(127, 127);
	resetDriveIME();
	clearTimer(T1);
	waitUntil(SensorValue[lift] > 1800);
	moveVertibar(0);
	moveLift(0);
  waitUntil(within(SensorValue[LeftDrive], 1200, 10) || time1[T1] > 1350);
	moveDrive(0, 0);

	moveMobileGoal(100);
	waitUntil(within(SensorValue[mobogo], 2650, 20));
	moveMobileGoal(-20);

	moveDrive(-127, -127);
	clearTimer(T1);
	resetDriveIME();
	waitUntil(within(SensorValue[LeftDrive], -600, 70) || time1[T1] > 1000);
	moveDrive(0, 0);
	moveMobileGoal(0);
}

#endif

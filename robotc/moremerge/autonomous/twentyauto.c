#ifndef AUTO_TWENTY_C
#define AUTO_TWENTY_C

#ifndef MOTOR_H
#include "../motors.h"
#endif
#ifndef CONFIGURATION_H
#include "../configuration.h"
#endif

void twenty() {
#if BLUE==1
	writeDebugStreamLine("using blue line");
#else
	writeDebugStreamLine("using red line");
#endif
	// initialization tasks
	resetGyro();
	resetDriveIME();
	openClaw(-20);
	moveVertibar(5);
	moveLift(100);
	waitUntil(SensorValue[lift] > 1500);

	// begin moving the mobile goal after the lift is sufficiently high
	moveMobileGoal(127);
	moveLift(30);
	delay(500);
	moveDrive(115, 127);
	waitUntil(SensorValue[mobogo] > 2800);
	moveMobileGoal(1);
	waitUntil(within(SensorValue[LeftDrive], 1000, 40) || SensorValue[LeftDrive] > 1180);
	moveMobileGoal(127);
	moveDrive(60, 60);
	while (SensorValue[mobogo] < 2990) moveMobileGoal(1.2 * (2990 - SensorValue[mobogo]));
	moveMobileGoal(-10);
	delay(50);
	moveMobileGoal(0);
	waitUntil(within(SensorValue[LeftDrive], 1580, 40) || SensorValue[LeftDrive] > 1600);
	moveDrive(0, 0);
	delay(500);
	moveMobileGoal(-100);
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
	waitUntil(within(SensorValue[lift], 1300, 20) || SensorValue[lift] > 1350);
	moveLift(30);
	moveVertibar(-100);
	waitUntil(within(SensorValue[vertibar], 3380, 20) || SensorValue[vertibar] > 3390);
	moveVertibar(10);
	moveLift(-100);
	waitUntil(within(SensorValue[lift], 1100, 20));
	moveLift(10);

	moveDrive(70, 70);
	waitUntil(within(SensorValue[LeftDrive], 370, 40));
	moveDrive(-10, -10);
	delay(200);
	moveDrive(0, 0);

	openClaw(-127);
	delay(250);
	openClaw(-30);

	//attempt to score second cone
	moveVertibar(100);
	moveDrive(-70, -70);
	moveLift(80);
	bool vertibarPassed = false;
	bool liftPassed = false;
	clearTimer(T1);
	while (!vertibarPassed && !liftPassed && time1[T1] < 2500) {
		if (within(SensorValue[vertibar], 1060, 60)) {
			moveVertibar(5);
			vertibarPassed = true;
		}

		if (within(SensorValue[lift], 1304, 20)) {
			moveLift(20);
			liftPassed = true;
		}
	}
	moveLift(-80);
	clearTimer(T1);
	waitUntil(SensorValue[lift] < 1200 && time1[T1] < 1000);
	openClaw(127);
	delay(700);
	writeDebugStreamLine("We've probably deposited the second goal");
	moveLift(127);
	openClaw(10);

	// attempt to return to base
	moveDrive(-90, -90);
	waitUntil(SensorValue[lift] > 1500);
	moveLift(20);
	waitUntil(within(SensorValue[LeftDrive], -1700, 80));
	moveDrive(10, 10);
	delay(400);
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
	moveDrive(-70, -70);
	resetDriveIME();
	waitUntil(within(SensorValue[LeftDrive], -270, 40));
	moveDrive(0, 0);

	// attempt to score in twenty point zone
	delay(400);
	resetGyro();
	delay(400);
#if BLUE==1
	while (!within(SensorValue[gyro], 890, 40)) { moveDrive(- 0.7 * (890 + SensorValue[gyro]), 0.7 * (SensorValue[gyro] + 890)); }
#else
	while (!within(SensorValue[gyro], -890, 40)) { moveDrive(0.7 * (890 + SensorValue[gyro]), -0.7 * (SensorValue[gyro] + 890)); }
#endif
	moveDrive(30, -30);
	delay(400);
	moveDrive(0, 0);


	moveLift(100);
	moveDrive(127, 127);
	resetDriveIME();
	clearTimer(T1);
	waitUntil(SensorValue[lift] > 1800);
	moveVertibar(0);
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

#endif

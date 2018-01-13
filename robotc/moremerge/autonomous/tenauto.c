#ifndef AUTO_TEN_C
#define AUTO_TEN_C

#ifndef MOTOR_H
#include "../motors.h"
#endif

void ten() {
	// initialization tasks
	resetGyro();
	resetDriveIME();
	openClaw(-20);
	moveVertibar(20);
	moveLift(100);
	waitUntil(SensorValue[lift] > 1500);

	// begin moving the mobile goal after the lift is sufficiently high
	moveMobileGoal(127);
	moveLift(30);
	delay(900);
	moveDrive(115, 127);
	waitUntil(SensorValue[mobogo] > 2840);
	moveMobileGoal(0);
	waitUntil(within(SensorValue[LeftDrive], 1000, 40) || SensorValue[LeftDrive] > 1180);
	moveMobileGoal(127);
	moveDrive(60, 60);
	while (SensorValue[mobogo] < 2990) moveMobileGoal(1.5 * (3000 - SensorValue[mobogo]));
	moveMobileGoal(-10);
	delay(50);
	moveMobileGoal(0);
	waitUntil(within(SensorValue[LeftDrive], 1580, 40) || SensorValue[LeftDrive] > 1620);
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
	clearTimer(T1);
	waitUntil(within(SensorValue[vertibar], 3380, 20) || SensorValue[vertibar] > 3400 || time1[T1] > 1600);
	moveVertibar(10);
	moveLift(-100);
	waitUntil(within(SensorValue[lift], 1100, 20));
	moveLift(10);

	// drive forward to collect second cone
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
	moveLift(120);


	resetDriveIME();
#if BLUE
	moveDrive(-65, -75);
#else
	moveDrive(-70, -70);
#endif
	bool vertibarPassed = false;
	bool liftPassed = false;
	clearTimer(T1);
	while (!vertibarPassed && !liftPassed && time1[T1] < 2500) {
		if (within(SensorValue[vertibar], 1060, 60)) {
			moveVertibar(5);
			vertibarPassed = true;
		}

		if (within(SensorValue[lift], 1364, 20)) {
			writeDebugStreamLine("Lift has reached appropiate height");
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
#if BLUE
	moveDrive(-85, -100);
#else
	moveDrive(-100, -100);
#endif
	clearTimer(T1);
	waitUntil(SensorValue[lift] > 1500 || time1[T1] > 1500);

	moveLift(30);
	waitUntil(within(SensorValue[LeftDrive], -1470, 40) || SensorValue[LeftDrive] < -1470);
	moveDrive(0, 0);
	delay(400);
	resetGyro();
	while (!within(SensorValue[gyro], -1900, 30)) { moveDrive(0.6 * (1900 + SensorValue[gyro]), -0.6 * (SensorValue[gyro] + 1900)); }
	moveDrive(-20, 20);
	delay(400);
	moveDrive(0, 0);

	// attempt to score in ten point zone
	moveLift(100);
	waitUntil(within(SensorValue[lift], 1700, 40));
	moveLift(0);
	moveMobileGoal(100);
	waitUntil(within(SensorValue[mobogo], 3110, 40));
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

#ifndef STAGO_AUTO_C
#define STAGO_AUTO_C

#ifndef MOTORS_H
#include "../motors.h"
#endif

void stago() {
	resetDriveIME();
	openClaw(-50);
	moveVertibar(-127);
	delay(400);
	moveVertibar(0);
	moveLift(100);
	delay(700);
	moveDrive(100, 100);
	bool drivePassed = false;
	bool liftPassed = false;
	clearTimer(T1);
	while (((!within(SensorValue[lift], 2162, 50) && SensorValue[lift] < 2170)
		|| (!within(SensorValue[LeftDrive], 380, 50) && SensorValue[LeftDrive] < 400))
		&& time1[T1] < 8000) {
		if (SensorValue[LeftDrive] < 380) {
			moveDrive(380 - SensorValue[LeftDrive],380 - SensorValue[LeftDrive]);
		}
		if (SensorValue[lift] < 2162) {
			moveLift(2162 - SensorValue[lift]);
		}
		if (within(SensorValue[lift], 2162, 40) || SensorValue[lift] > 2170) {
			liftPassed = true;
		}
		if (within(SensorValue[LeftDrive], 550, 40) || SensorValue[LeftDrive] > 600) {
			drivePassed = true;
		}
		if (drivePassed) {
			moveDrive(-10, -10);
			delay(100);
			moveDrive(0, 0);
		}
		if (liftPassed) {
			moveLift(20);
		}
		delay(20);
	}
	writeDebugStreamLine("Drive IME %f", SensorValue[LeftDrive]);
	// slam the cone down onto the lift
	moveLift(-70);
	waitUntil(within(SensorValue[lift], 2000, 40) || SensorValue[lift] < 1950);
	openClaw(127);
	delay(300);
	openClaw(10);
	moveLift(127);
	resetDriveIME();
	moveDrive(-100, -100);
	delay(300);
	moveLift(60);
	waitUntil(within(SensorValue[LeftDrive], -400, 30));
	waitUntil(SensorValue[lift] > 2300);
	moveLift(30);
	moveDrive(10, 10);
	delay(300);
	moveDrive(0, 0);

	resetGyro();
	moveDrive(-70, 70);
	waitUntil(within(SensorValue[gyro], 850, 20));
	moveDrive(10, -10);
	delay(300);
	moveDrive(0, 0);


	// begin to attempt to collect the second mogo
	resetDriveIME();
	moveMobileGoal(127);
	moveDrive(127, 127);
	while (SensorValue[mobogo] < 3035) moveMobileGoal(1.1 * (3100 - SensorValue[mobogo]));
	moveMobileGoal(10);

	waitUntil(within(SensorValue[LeftDrive], 1620, 20) || SensorValue[LeftDrive] > 1660);
	moveDrive(-10, -10);
	delay(300);
	moveDrive(0, 0);
	moveMobileGoal(-127);
	waitUntil(within(SensorValue[mobogo], 1300, 20));
	moveMobileGoal(0);

	// attempt to return to base
	resetDriveIME();
	moveDrive(-127, -127);
	waitUntil(within(SensorValue[LeftDrive], -1320, 80));
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
	waitUntil(within(SensorValue[LeftDrive], -450, 40));
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

	moveDrive(127, 127);
	resetDriveIME();
	clearTimer(T1);
	waitUntil(SensorValue[lift] > 1800);
	moveVertibar(0);
	moveLift(0);
  waitUntil(within(SensorValue[LeftDrive], 1360, 10) || time1[T1] > 1650);
	moveDrive(0, 0);

	moveMobileGoal(100);
	waitUntil(within(SensorValue[mobogo], 2790, 20));
	moveMobileGoal(-50);

	moveDrive(-127, -127);
	clearTimer(T1);
	resetDriveIME();
	waitUntil(within(SensorValue[LeftDrive], -600, 70) || time1[T1] > 1000);
	moveDrive(0, 0);
	moveMobileGoal(0);
}

#endif

#include "core/motors.h"
#include "core/sensors.h"
#include "configuration/robot.h"
#include "util/concurrency.h"

void ten() {
	// initialization tasks
	resetGyro();
	resetDrive();
	openClaw(-20);
	moveSwitchLift(20);
	moveLift(100);
	waitUntil(getLiftPot() > 1500, 3000);

	// begin moving the mobile goal after the lift is sufficiently high
	moveGoal(127);
	moveLift(30);
	delay(900);
	moveDrive(115, 127);
	waitUntil(getMobileGoalPot() > 2840, 3000);
	moveGoal(0);
	waitUntil(within(getLeftDrive(), 1000, 40) || getLeftDrive() > 1180, 6000);
	moveGoal(127);
	moveDrive(60, 60);
	while (getMobileGoalPot() < 2990) moveGoal(1.5 * (3000 - getMobileGoalPot()));
	moveGoal(-10);
	delay(50);
	moveGoal(0);
	waitUntil(within(getLeftDrive(), 1600, 40) || getLeftDrive() > 1620, 6000);
	moveDrive(0, 0);
	delay(500);
	moveGoal(-100);
	waitUntil(within(getMobileGoalPot(), 1300, 20), 2000);
	moveGoal(0);

	// drop the first cone into its place
	moveLift(-75);
	waitUntil(within(getLiftPot(), 1200, 40), 2000);
	moveLift(10);
	openClaw(100);
	delay(400);
	openClaw(10);
	moveLift(100);

	// collect cone behind, raise lift up
	resetDrive();
	waitUntil(within(getLiftPot(), 1300, 20) || getLiftPot() > 1350, 3000);
	moveLift(30);
	moveSwitchLift(-100);
	waitUntil(within(getVertibarPot(), 3380, 20) || getVertibarPot() > 3400, 1600);
	moveSwitchLift(10);
	moveLift(-100);
	waitUntil(within(getLiftPot(), 1100, 20), 3000);
	moveLift(10);

	// drive forward to collect second cone
	moveDrive(70, 70);
	waitUntil(within(getLeftDrive(), 370, 40), 3000);
	moveDrive(-10, -10);
	delay(200);
	moveDrive(0, 0);

	openClaw(-127);
	delay(250);
	openClaw(-30);

	//attempt to score second cone
	moveSwitchLift(100);
	moveLift(120);


	resetDrive();
#if BLUE
	moveDrive(-65, -75);
#else
	moveDrive(-70, -70);
#endif
	bool vertibarPassed = false;
	bool liftPassed = false;
	executeUntil ({
		if (within(getVertibarPot(), 1060, 60)) {
			moveSwitchLift(5);
			vertibarPassed = true;
		}

		if (within(getLiftPot(), 1450, 20)) {
			moveLift(20);
			liftPassed = true;
		}
	}, !vertibarPassed && !liftPassed, 2500)
	moveLift(-100);
	waitUntil(getLiftPot() < 1150, 1000);
	moveLift(-10);
	openClaw(127);
	delay(700);
	moveLift(127);
	openClaw(10);


	// attempt to return to base
#if BLUE
	moveDrive(-85, -100);
#else
	moveDrive(-100, -100);
#endif
	waitUntil(getLiftPot() > 1400, 1500);

	moveLift(30);
	waitUntil(within(getLeftDrive(), -1470, 40) || getLeftDrive() < -1470, 6000);
	moveDrive(0, 0);
	delay(400);
	resetGyro();
	while (!within(getGyro(), -1900, 30)) { moveDrive(0.6 * (1900 + getGyro()), -0.6 * (getGyro() + 1900)); }
	moveDrive(-20, 20);
	delay(400);
	moveDrive(0, 0);

	// attempt to score in ten point zone
	moveLift(100);
	waitUntil(within(getLiftPot(), 1700, 40), 3000);
	moveLift(0);
	moveGoal(100);
	waitUntil(within(getMobileGoalPot(), 3110, 40), 3000);
	moveGoal(-20);

	moveDrive(-120, -120);
	moveGoal(-100);
	delay(500);
	moveGoal(0);
	waitUntil(within(getLeftDrive(), 0, 30), 200);
	delay(300);
	moveDrive(10, 10);
	delay(400);
	moveDrive(0, 0);
}

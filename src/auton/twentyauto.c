#include "core/motors.h"
#include "configuration/robot.h"
#include "core/sensors.h"
#include "util/concurrency.h"

void twenty() {
	// initialization tasks
	moveLift(127);
	resetDrive();
	openClaw(-20);
	moveSwitchLift(5);
	delay(200);
	moveGoal(127);
	waitUntil(getLiftPot() > 1400, 2000);

	// begin moving the mobile goal after the lift is sufficiently high
	moveLift(30);
	moveDrive(65, 77);
	waitUntil(getLiftPot() > 1500, 2000);
	while (getMobileGoalPot() < 3035) moveGoal(1.1 * (3100 - getMobileGoalPot()));
	moveDrive(115, 127);
	moveGoal(10);

	waitUntil(within(getLeftDrive(), 1620, 20) || getLeftDrive() > 1660, 6000);
	moveDrive(-10, -10);
	delay(300);
	moveDrive(0, 0);
	moveGoal(-127);
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
	waitUntil(within(getLiftPot(), 1350, 20) || getLiftPot() > 1350, 2000);
	moveLift(30);
	moveSwitchLift(-100);
	waitUntil(within(getVertibarPot(), 3380, 20) || getVertibarPot() > 3390, 2000);
	moveSwitchLift(-10);
	moveLift(-100);
	waitUntil(within(getLiftPot(), 1100, 20) || getLiftPot() < 1090, 2000);
	moveLift(-10);

	moveDrive(85, 85);
	waitUntil(within(getLeftDrive(), 390, 40), 1500);
	moveDrive(0, 0);

	openClaw(-127);
	delay(300);
	openClaw(-40);

	//attempt to score second cone
	moveSwitchLift(70);
	moveDrive(-127, -127);
	moveLift(127);
	bool vertibarPassed = false;
	bool liftPassed = false;
	executeUntil ({
		if (within(getVertibarPot(), 1060, 60)) {
			moveSwitchLift(5);
			vertibarPassed = true;
		}

		if (within(getLiftPot(), 1606, 20)) {
			moveLift(20);
			if (!vertibarPassed) moveSwitchLift(100);
			liftPassed = true;
		}
	}, !vertibarPassed && !liftPassed, 2500)
	moveLift(-80);
	waitUntil(getLiftPot() < 1200, 1000);
	openClaw(127);
	moveLift(127);
	openClaw(10);

	// attempt to return to base
	moveDrive(-127, -127);
	waitUntil(getLiftPot() > 1400, 2000);
	moveLift(30);
	waitUntil(within(getLeftDrive(), -1700, 80), 6000);
	moveDrive(20, 20);
	delay(100);
	moveDrive(0, 0);
	resetGyro();

	// rotate to prepare to score in 20 point zone
#if BLUE==1
	while (!within(getGyro(), 450, 30)) { moveDrive(-0.6 * (450 + getGyro()), 0.6 * (getGyro() + 450)); }
#else
	while (!within(getGyro(), -450, 30)) { moveDrive(0.6 * (450 + getGyro()), - 0.6 * (getGyro() + 450)); }
#endif
	moveDrive(20, -20);
	delay(30);
	moveDrive(-100, -100);
	resetDrive();
	waitUntil(within(getLeftDrive(), -380, 40), 2000);
	moveDrive(10, 10);
	delay(100);
	moveDrive(0, 0);

	// attempt to score in twenty point zone
	resetGyro();
#if BLUE==1
	while (!within(getGyro(), 890, 40)) { moveDrive(- 0.7 * (890 + getGyro()), 0.7 * (getGyro() + 890)); }
	moveDrive(40, -40);
#else
	while (!within(getGyro(), -890, 40)) { moveDrive(0.7 * (890 + getGyro()), -0.7 * (getGyro() + 890)); }
	moveDrive(-40, 40);
#endif
	delay(100);
	moveDrive(0, 0);


	moveLift(100);
	moveDrive(127, 127);
	resetDrive();
	waitUntil(getLiftPot() > 1800, 2000);
	moveSwitchLift(0);
	moveLift(0);
  waitUntil(within(getLeftDrive(), 1200, 10), 1350);
	moveDrive(0, 0);

	moveGoal(100);
	waitUntil(within(getMobileGoalPot(), 2650, 20), 2000);
	moveGoal(-20);

	moveDrive(-127, -127);
	resetDrive();
	waitUntil(within(getLeftDrive(), -600, 70), 1000);
	moveDrive(0, 0);
	moveGoal(0);
}

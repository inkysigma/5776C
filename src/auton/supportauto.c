#include "core/motors.h"
#include "core/sensors.h"

#include "util/math.h"
#include "util/concurrency.h"

void twentyseven() {
	resetDrive();

	moveLift(100);
	delay(500);
	moveLift(0);

	// begin by depositing the goal on stationary
	bool vertReached = false;
	bool liftReached = false;
	bool driveReached = false;
	executeUntil({
		if (!vertReached) {
			raiseSwitchLift(90);
		}
		else {
			raiseSwitchLift(0);
		}
		if (!liftReached)
			moveLift(90);
		else
			raiseSwitchLift(0);
		if (!driveReached)
			moveDrive(100, 100);
		else
			moveDrive(0, 0);
		if (within(getVertibarPot(), 2300, 40)) {
			vertReached = true;
			raiseSwitchLift(-10);
		}
		if (within(getLiftPot(), 1740, 20)) {
			liftReached = true;
			moveLift(-5);
		}
		if (within(getLeftDrive(), 680, 20)) {
			driveReached = true;
			moveDrive(-5, -5);
		}
	}, !vertReached && !liftReached && !driveReached, 2000);

	raiseSwitchLift(0);
	moveLift(20);
	moveDrive(0, 0);

	raiseSwitchLift(-80);
	waitUntil(getVertibarPot() < 1640, 2000);
	raiseSwitchLift(0);

	moveLift(-100);
	waitUntil(within(getLiftPot(), 1400, 40), 500);
	moveLift(0);

	openClaw(100);
	delay(400);
	openClaw(0);
	return;

	resetDrive();

	moveLift(100);
	waitUntil(getLiftPot() > 1500, 1000);
	moveGoal(127);
	waitUntil(getMobileGoalPot() > 1433, 1500);
	moveGoal(0);
	moveLift(60);
	delay(900);
	moveDrive(127, 127);
	moveLift(0);
	waitUntil(within(getLeftDrive(), 1380, 40) || within(getRightDrive(), -1380, 40), 3000);
	moveDrive(0, 0);
	delay(500);
	moveGoal(-100);
	waitUntil(within(getMobileGoalPot(), 0, 20), 3000);
	moveGoal(0);


	moveDrive(-90, -90);
	waitUntil(within(getLeftDrive(), 170, 80), 3000);
	moveDrive(0, 0);
	delay(400);
	resetGyro();
	moveDrive(-127, 127);
	while (!within(getGyro(), 1000, 30)) { moveDrive(-(1000 + getGyro()), (getGyro() + 1000)); }
	moveDrive(60, 60);
	waitUntil(within(getLeftDrive(), 100, 40), 3000);
	moveDrive(0, 0);

	// attempt to score in twenty point zone
	delay(400);
	resetGyro();
	delay(400);
	while (!within(getGyro(), 890, 40)) { moveDrive(-(890 + getGyro()), (getGyro() + 890)); }
	moveDrive(30, -30);
	delay(400);
	moveDrive(0, 0);



	moveDrive(127, 127);
	waitUntil(within(getLeftDrive(), 1230, 10), 3000);
	moveDrive(0, 0);

	moveGoal(100);
	waitUntil(within(getMobileGoalPot(), 504, 40), 1000);
	moveGoal(-20);

	moveDrive(-100, -100);
	waitUntil(within(getLeftDrive(), -40, 70), 800);
	moveDrive(0, 0);
	moveGoal(0);
}

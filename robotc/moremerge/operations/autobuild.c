#ifndef AUTOBUILD_DRIVER_LOADS_C
#define AUTOBUILD_DRIVER_LOADS_C
#ifndef PID_VERT_C
#include "../pid/vertibar.c"
#endif
#ifndef PID_LIFT_C
#include "../pid/lift.c"
#endif
#ifndef AUTONOMOUS_H
#include "autonomous.h"
#endif

typedef struct {
	int liftHeight;
	int vertTarget;
	bool matchLoads;
	bool lowerLift;
	bool maxHeight;
	bool liftMobileGoal;
} buildConfiguration;
buildConfiguration drive_loads;

bool isRunning = false;
bool driver = false;
/**
task buildStack() {
	// build the autostack
	resetLiftPid();

	// set the lift to the initial height

	// if the operation requested is a match load, then we need to increase height a bit
	// this avoids slamming the cone for the first few stacks and has no effect on later ones
	if (drive_loads.matchLoads)
		incrementLiftBy(400);

	openClaw(-30);

	// move to the correct height and begin moving the vertibar when appropiate or
	// the timer reachers 2.5 seconds. We don't use the setLift function here because
	// for matchloads on lower cones, we want to start even if the lift target is higher
	setLiftTarget(drive_loads.liftHeight);
	clearTimer(T1);
	waitUntil(SensorValue[lift] > drive_loads.liftHeight
	|| within(SensorValue[lift], drive_loads.liftHeight, 100)
	|| time1[T1] > 2500);

	// raise the vertibar
	setVertibar(drive_loads.vertTarget, 1200);

	// this operation should only be done for higher cones.
	if (drive_loads.liftMobileGoal) {
		moveMobileGoal(120);
		delay(700);
		moveMobileGoal(0);
	}

	clearTimer(T1);
	// wait until the lift is much close to its target and also the case for match loads where
	// SensorValue[lift] > drive_loads.height
	waitUntil(within(SensorValue[lift], drive_loads.liftHeight, 50) || time1[T1] > 1800);
	delay(200);

	// do we need to lower the lift at the top extra?
	stopTask(liftpid);
	stopTask(vertpid);
	incrementLiftBy(-75);
	startTask(liftpid);
	startTask(vertpid);



	// deposit the cone
	openClaw(100);
	delay(200);
	openClaw(5);

	// reset the lift pid and raise it past the cone height so that we can
	// lower the vertibar
	resetLiftPid();
	incrementLiftBy(330);
	waitUntil(withinLiftTarget(40));


	if (drive_loads.maxHeight) {
		stopTask(liftpid);
		stopTask(vertpid);
		moveLift(30);

		isRunning = false;
		return;
	}

	// reset the lift the the height of the driver loads or match loads
	if (drive_loads.matchLoads) {
		// reopen the claw
		openClaw(100);
		delay(400);
		openClaw(15);

		// set the vertibar back to the lower height

		setVertibar(2712, 1600);
		// set the lift target
		setLift(1630, 2500);
	}
	else {
		// lower the vertibar and reset the lift
		setVertibar(2400, 800);
		setLift(1055, 800);
		setVertibar(2712, 1600);
	}

	// stop the pids so driver control can return
	stopLiftPid();
	stopVertibarPid();
	isRunning = false;
	moveLift(20);
}**/

bool withinOrGreater(float a, float b, float margin) {
	return a > b || within(a, b, margin);
}

bool withinOrLess(float a, float b, float margin) {
	return a < b || within(a, b, margin);
}

task buildStackWithoutPid() {
	isRunning = true;
	openClaw(-40);
	moveLift(127);
	waitUntil(within(drive_loads.liftHeight - 300, SensorValue[lift], 40) || SensorValue[lift] > drive_loads.liftHeight);
	moveLift(100);
	moveVertibar(127);
	while (!withinOrGreater(SensorValue[lift], drive_loads.liftHeight, 10) || !withinOrLess(SensorValue[vertibar], drive_loads.vertTarget, 10)) {
		moveLift(drive_loads.liftHeight - SensorValue[lift]);\
		if (within(SensorValue[vertibar], drive_loads.vertTarget, 20))
			moveVertibar(20);
	}

	moveVertibar(20);
	moveLift(-50);
	delay(500);
	moveLift(20);

	openClaw(127);
	delay(400);
	openClaw(10);

	moveLift(100);
	waitUntil(SensorValue[lift] > drive_loads.liftHeight + 100);
	moveLift(30);
	moveVertibar(-127);
	while (SensorValue[vertibar] < 2750) {
		moveVertibar(SensorValue[vertibar] - 2750);
	}
	writeDebugStreamLine("vertibar at %f", SensorValue[vertibar]);

	moveVertibar(10);
	moveLift(-100);
	waitUntil(SensorValue[lift] < 1105);
	moveLift(30);

	isRunning = false;
}

bool setLiftBuildHeight(int cone_stack) {

	switch(cone_stack) {
	case 0:
		drive_loads.liftHeight = 1400;
		drive_loads.vertTarget = 560;
		break;
	case 1:
		drive_loads.liftHeight = 1520;
		drive_loads.vertTarget = 560;
		break;
	case 2:
		drive_loads.liftHeight = 1620;
		drive_loads.vertTarget = 560;
		break;
	case 3:
		drive_loads.liftHeight = 1720;
		drive_loads.vertTarget = 560;
		break;
	case 4:
		drive_loads.liftHeight = 1820;
		drive_loads.vertTarget = 560;
		break;
	case 5:
		drive_loads.liftHeight = 1880;
		drive_loads.vertTarget = 560;
		break;
	case 6:
		drive_loads.liftHeight = 2020;
		drive_loads.vertTarget = 560;
		drive_loads.lowerLift = true;
		break;
	case 7:
		drive_loads.liftHeight = 2120;
		drive_loads.vertTarget = 560;
		drive_loads.lowerLift = true;
		break;
	case 8:
		drive_loads.liftHeight = 2320;
		drive_loads.vertTarget = 560;
		drive_loads.lowerLift = true;
		break;
	case 9:
		drive_loads.liftHeight = 2420;
		drive_loads.vertTarget = 560;
		drive_loads.lowerLift = true;
		break;
	case 10:
		drive_loads.liftHeight = 2540;
		drive_loads.vertTarget = 560;
		drive_loads.lowerLift = true;
		drive_loads.maxHeight = true;
		break;
	default:
		return false;
	}
	if (cone_stack >= 5) {
		drive_loads.liftMobileGoal = true;
	}
	return true;
}

bool buildMatchLoads(int cone_stack) {
	resetLiftPid();
	writeDebugStreamLine("building match loads: %i", cone_stack);
	setVertibarTarget(3703);
	setLiftTarget(1139);
	startTask(liftpid);
	startTask(vertpid);

	isRunning = true;
	driver = true;

	drive_loads.lowerLift = false;
	drive_loads.maxHeight = false;

	if (!setLiftBuildHeight(cone_stack)) return false;

	drive_loads.matchLoads = false;

	// startTask(buildStack);
	return true;
}

bool buildDriverLoads(int cone_stack) {
	resetLiftPid();
	isRunning = true;
	driver = true;

	drive_loads.maxheight = false;

	if (!setLiftBuildHeight(cone_stack)) return false;

	drive_loads.matchLoads = false;

	startTask(buildStackWithoutPid);
	return true;
}

bool getRunning() {
	return isRunning;
}

void stopAutoBuild() {
	writeDebugStreamLine("stopping autobuild");
	if (!isRunning) {
		return;
	}
	isRunning = false;

	stopLiftPid();
	stopVertibarPid();
	// suspendTask(buildStack);
	// stopTask(buildStack);
	moveLift(0);
	moveVertibar(0);
}

#endif

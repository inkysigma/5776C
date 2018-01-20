#ifndef AUTOBUILD_DRIVER_LOADS_C
#define AUTOBUILD_DRIVER_LOADS_C

// this is the file for pid of vertibar
// the pid is kept for legacy purposes from when the
// autostack functionality used a pid.
#ifndef PID_VERT_C
#include "../pid/vertibar.c"
#endif

// this is the file for pid of lift
#ifndef PID_LIFT_C
#include "../pid/lift.c"
#endif

// this is a core file that includes some basic pid functionality
#ifndef AUTONOMOUS_H
#include "autonomous.h"
#endif


// this struct represents the configuration of the autostack
typedef struct {
	// the height to lift the rd4b to
	int liftHeight;

	// the vertibar target to hit when attempting to reach the top.
	// this varies because apparently pots are bad
	int vertTarget;

	// is this a match load or a drive load. this affects start height
	// and return height
	bool matchLoads;

	// should we lower the lift. this may be unnecessary on lower cone
	// heights because reasons
	bool lowerLift;

	// is this the maximum height for the bot? if so, do not go back down
	// this may push the stack over if we try to go down
	bool maxHeight;

	// should we lift the mobile goal and power it out?
	// this occurs because the mobile goal is tilted and may need to
	// power out to properly receive a cone on higher levels
	bool liftMobileGoal;

	// should we lift the lift initially during match loads.
	// this occurs because the autostack may simply twist the
	// cone off the match loader and strafe it towards the mobile goal which will
	// not stack correctly
	bool liftInitial;
} buildConfiguration;

// the actual configuration instance of the struct
buildConfiguration drive_loads;

// is the autostack running
bool isRunning = false;

// is a within or greater than b by some margin.
// i.e. is a > b - margin
bool withinOrGreater(float a, float b, float margin) {
	return a > b || within(a, b, margin);
}


// is a within or greater than b by some margin
// i.e. is a < b + margin
bool withinOrLess(float a, float b, float margin) {
	return a < b || within(a, b, margin);
}

// build the autostack without a pid. this task is
// never directly called for by the driver or by code
// outside this file. instead, use the helper functions
// to help configure the correct drive_loads
task buildStackWithoutPid() {

	// mark the task state as running so driver control
	// cannot interfere
	isRunning = true;

	// apply a small stall torque to ensure that the cone remains
	// in place throughout this operation
	openClaw(-30);

	// being moving the lift up
	moveLift(127);

	if (drive_loads.liftInitial && drive_loads.matchLoads) {
		waitUntil(SensorValue[lift] > 1600);
	}

	// wait until the driver loads are a little below target height or above target height
	// following this we should ensure that the vertibar begins raising for concurrency
	waitUntil(withinOrGreater(SensorValue[lift], drive_loads.liftHeight - 300, 40));

	// move the vertibar up so that we can deposit the cone later
	moveVertibar(127);

	// begin targeting the appropiate lift and vertibar values
	// the lift needs to be within or greater since going up increases the
	// lift value. therefore, we need to wait until the target is at least above.
	// overshooting the lift is fine or better than undershooting
	// on the other hand, the vertibar pot sensor decreases value as
	// the vertibar goes up. so "undershooting the value" means we've overshot the vertibar
	// which is also an ok condition
	while (!withinOrGreater(SensorValue[lift], drive_loads.liftHeight, 10)
		|| !withinOrLess(SensorValue[vertibar], drive_loads.vertTarget, 50)) {

		// apply a small p term to the lift so it slows down as it approaches the target
		// momentum will likely ensure it overshoots its target
		if (withinOrGreater(SensorValue[lift], drive_loads.liftHeight, 20)) {
			moveLift(30);
		}
		else {
			moveLift(2 * (drive_loads.liftHeight - SensorValue[lift]));
		}
		// if the vertbar target has been reached, simply apply a stall torque
		if (withinOrLess(SensorValue[vertibar], drive_loads.vertTarget, 20)) {
			moveVertibar(20);
		}
		else {
			// use a simple p term to the vertibar so it slows down to prevent excessive stalling
			moveVertibar((SensorValue[vertibar] - drive_loads.vertTarget));
		}
	}

	// check if the vertibar has not reached the correct height.
	// this occurs sometimes for some reason despite the while loop above
	moveVertibar(90);
	// clear timer T1 for setup to ensure vertibar reaches correct height
	clearTimer(T1);
	// wait until vertibar or timer runs out in about 1500 milliseconds
	waitUntil(withinOrLess(SensorValue[vertibar], drive_loads.vertTarget, 50) || time1[T1] > 2000);

	// we apply a stall torque to the vertibar to ensure it doesn't move too much
	moveVertibar(2);
	writeDebugStreamLine("vertibar at: %f", SensorValue[vertibar]);

	// move the lift down for better accuracy. we time this simply because
	// it's sufficient and more work is unnecessary
	moveLift(-100);
	delay(100);

	// apply a lift stall to ensure that the lift doesn't fall down
	moveLift(20);

	// open the claw for a small amount of time to release the cone.
	// we should have deposited the claw by now
	openClaw(127);
	if (drive_loads.liftMobileGoal) {
		moveMobileGoal(100);
	}
	delay(400);

	moveMobileGoal(0);

	// apply a small claw open stall to ensure that it remains open
	openClaw(10);

	// move the lift back up to ensure that when we lower the vertibar later,
	// we don't get caught in the newly created stack
	moveLift(127);

	// wait until we are slightly above the target height so we have room to
	// lower the vertibar

	waitUntil(SensorValue[lift] > drive_loads.liftHeight + 50);

	if (drive_loads.matchLoads && drive_loads.liftInitial) {
		waitUntil(SensorValue[lift] > 1650);
	}

	// small stall torque to ensure that the lift does not go back down
	moveLift(30);

	openClaw(-127);

	// move the vertibar down
	moveVertibar(-127);

	delay(300);
	openClaw(0);

	// ensure that the vertibar hits the "lowered" position correctly
	while (SensorValue[vertibar] < 2750) {
		//we enable a small kp to prevent excessive stalling and better accuracy
		moveVertibar(SensorValue[vertibar] - 2750);
	}

	// apply a light stall torque to the vertibar
	moveVertibar(10);

	openClaw(127);

	// move the lift back down to original state


	// wait until we are at ground position yet
	// TODO: add a match loads ground position
	if (!drive_loads.matchLoads) {
		// if we are not in matchloads, simply return to ground position
		moveLift(-80);
		delay(300);
		openClaw(10);
		waitUntil(SensorValue[lift] < 1105);
	}
	else {
		// if we are in matchloads, we need to check if we are currently
		// above or below the target height
		if (SensorValue[matchloads]) {
			// if the sensor value reads true, that must mean that it is not pressed
			// this means that we should go down in order to press the button
			moveLift(-70);
			delay(200);
			openClaw(10);
			waitUntil(!SensorValue[matchloads]);
		}
		else {
			// if the sensor value reads false, that must mean that it is pressed
			// this means we ought to go up in order to stop pressing the button
			moveLift(70);
			delay(200);
			openClaw(10);
			waitUntil(SensorValue[matchloads]);
		}
	}

	// reapply a small stall torque so we don't have the lift collapse
	moveLift(30);

	// mark that we are done with autostack
	isRunning = false;
}

bool setLiftBuildHeight(int cone_stack) {
	// configure the auto stack for a given cone height
	switch(cone_stack) {
	case 0:
		drive_loads.liftHeight = 1320;
		drive_loads.vertTarget = 560;
		drive_loads.liftInitial = true;
		break;
	case 1:
		drive_loads.liftHeight = 1440;
		drive_loads.vertTarget = 560;
		drive_loads.liftInitial = true;
		break;
	case 2:
		drive_loads.liftHeight = 1520;
		drive_loads.vertTarget = 560;
		break;
	case 3:
		drive_loads.liftHeight = 1700;
		drive_loads.vertTarget = 560;
		break;
	case 4:
		drive_loads.liftHeight = 1790;
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
	// we need to lift the mobile goal if the stack if greater than 5
	// otherwise the cone becomes misalign with the claw
	if (cone_stack >= 5) {
		drive_loads.liftMobileGoal = true;
	}
	return true;
}

bool buildMatchLoads(int cone_stack) {\
	writeDebugStreamLine("building match loads: %i", cone_stack);

	// preemptively set isRunning to true to ensure that out of order
	// execution does not do something unexpected
	isRunning = true;
	// set the driver configuration for match loads
	drive_loads.lowerLift = false;
	drive_loads.maxHeight = false;
	drive_loads.matchLoads = true;

	// setLiftBuildHeight will return false if it was unable to correctly
	// configure the drive_loads. this likely means cone_stack is too great
	// we should return here to prevent stalling
	if (!setLiftBuildHeight(cone_stack)) return false;

	// start the autostack with proper configuration
	startTask(buildStackWithoutPid);

	// return true to indicate that the operation was successful
	return true;
}

bool buildDriverLoads(int cone_stack) {
	isRunning = true;

	drive_loads.maxHeight = false;
	drive_loads.matchLoads = false;

	if (!setLiftBuildHeight(cone_stack)) return false;

	startTask(buildStackWithoutPid);
	return true;
}

bool getRunning() {
	// get whether the autostack is running
	return isRunning;
}

void stopAutoBuild() {
	writeDebugStreamLine("stopping autobuild");
	// to stop autobuild, we have several tasks
	isRunning = false;

	stopLiftPid();
	stopVertibarPid();
	// suspendTask(buildStack);
	stopTask(buildStackWithoutPid);
	moveLift(0);
	moveVertibar(0);
}

#endif

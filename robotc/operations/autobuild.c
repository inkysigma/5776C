#ifndef AUTOBUILD_DRIVER_LOADS_C
#define AUTOBUILD_DRIVER_LOADS_C
#ifndef PID_VERT_C
#include "../pid/vertibar.c"
#endif
#ifndef PID_LIFT_C
#include "../pid/lift.c"
#endif
#include "autonomous.h"

typedef struct {
	int height;
	bool matchLoads;
	bool lowerLift;
	bool maxheight;
	bool liftMobileGoal;
} buildConfiguration;

buildConfiguration drive_loads;

bool isRunning = false;
bool driver = false;

task buildDriver() {
	// set the lift to the initial height
	if (drive_loads.matchLoads)
		setLift(1600, 800);

	openClaw(-30);
	if (drive_loads.matchLoads) openClaw(-40);

	setVertibar(2950, 200);

	// move to the correct height and begin moving the vertibar when appropiate or
	// the timer reachers 2.5 seconds.
	setLiftTarget(drive_loads.height);
	clearTimer(T1);
	if (drive_loads.liftMobileGoal) {
		moveMobileGoal(120);
		delay(1000);
		moveMobileGoal(0);
	}
	waitUntil(SensorValue[lift] > drive_loads.height || within(SensorValue[lift], drive_loads.height, 200) || time1[T1] > 2500);
	// raise the vertibar
	setVertibar(1230, 1700);
	delay(200);

	if (drive_loads.matchLoads)
		delay(700);

	clearTimer(T1);
	waitUntil(within(SensorValue[lift], drive_loads.height, 50) || time1[T1] > 2500);
	if (drive_loads.lowerLift) {
		incrementLiftBy(-90);
		clearTimer(T1);
		waitUntil(withinLiftTarget(20) || time1[T1] > 700);
		delay(400);
		} else {
		incrementLiftBy(-50);
		delay(600);
	}

	openClaw(100);
	delay(200);
	openClaw(0);

	resetLiftPid();
	incrementLiftBy(300);
	waitUntil(withinLiftTarget(50));
	if (drive_loads.maxheight) {
		stopTask(liftpid);
		stopTask(vertpid);
		moveLift(30);

		isRunning = false;
		return;
	}

	// reset the lift the the height of the driver loads
	if (drive_loads.matchLoads) {
		setVertibar(2900, 800);
		setLift(1600, 800);
		delay(400);
		setVertibar(3400, 1600);

		clearTimer(T1);
		waitUntil((within(SensorValue[lift], 1481, 50) && within(SensorValue[vertibar], 3400, 50)) || time1[T1] > 2500);
		} else {
		// lower the vertibar
		setVertibar(2900, 800);
		setLift(924, 800);
		delay(400);
		setVertibar(3630, 1600);

		clearTimer(T1);
		waitUntil((within(SensorValue[lift], 924, 50) && within(SensorValue[vertibar], 3630, 50)) || time1[T1] > 2500);
	}

	stopLiftPid();
	stopVertibarPid();
	isRunning = false;
	moveLift(10);
}


bool setLiftBuildHeight(int cone_stack) {

	switch(cone_stack) {
	case 0:
		drive_loads.height = 1150;
		break;
	case 1:
		drive_loads.height = 1320;
		break;
	case 2:
		drive_loads.height = 1440;
		break;
	case 3:
		drive_loads.height = 1530;
		break;
	case 4:
		drive_loads.height = 1590;
		break;
	case 5:
		drive_loads.height = 1675;
		break;
	case 6:
		drive_loads.height = 1820;
		drive_loads.lowerLift = true;
		break;
	case 7:
		drive_loads.height = 1930;
		drive_loads.lowerLift = true;
		break;
	case 8:
		drive_loads.height = 2030;
		drive_loads.lowerLift = true;
		break;
	case 9:
		drive_loads.height = 2110;
		drive_loads.lowerLift = true;
		break;
	case 10:
		drive_loads.height = 2200;
		drive_loads.lowerLift = true;
		drive_loads.maxheight = true;
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
	writeDebugStreamLine("building match loads");
	setVertibarTarget(SensorValue[vertibar]);
	setLiftTarget(SensorValue[lift]);
	startTask(liftpid);
	startTask(vertpid);

	if (cone_stack == 0) {
		setLift(1600, 1000);
		setVertibar(3400, 1000);
	}

	isRunning = true;
	driver = true;

	drive_loads.lowerLift = false;
	drive_loads.maxheight = false;

	if (!setLiftBuildHeight(cone_stack)) return false;

	drive_loads.matchLoads = true;

	startTask(buildDriver);
	return true;
}

bool buildDriverLoads(int cone_stack) {
	resetLiftPid();
	writeDebugStreamLine("building driver loads");
	setVertibarTarget(SensorValue[vertibar]);
	setLiftTarget(SensorValue[lift]);
	startTask(liftpid);
	startTask(vertpid);
	isRunning = true;
	driver = true;

	drive_loads.maxheight = false;

	if (!setLiftBuildHeight(cone_stack)) return false;

	drive_loads.matchLoads = false;

	startTask(buildDriver);
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
	stopTask(buildDriver);
	moveLift(0);
	moveVertibar(0);
}

#endif

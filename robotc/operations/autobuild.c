#ifndef AUTOBUILD_DRIVER_LOADS_C
#define AUTOBUILD_DRIVER_LOADS_C
#include "../pid/vertibar.c"
#include "../pid/lift.c"
#include "autonomous.h"

typedef struct {
	int height;
	bool matchLoads;
	bool lowerLift;
	bool maxheight;
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


	// move to the correct height and begin moving the vertibar when appropiate or
	// the timer reachers 2.5 seconds.
	setLiftTarget(drive_loads.height);
	clearTimer(T1);
	waitUntil(SensorValue[lift] > drive_loads.height || within(SensorValue[lift], drive_loads.height, 200) || time1[T1] > 2500);
	// raise the vertibar
	setVertibar(1230, 2000);
	delay(200);

	if (drive_loads.matchLoads)
		delay(700);

	clearTimer(T1);
	waitUntil(within(SensorValue[lift], drive_loads.height, 50) || time1[T1] > 2500);
	writeDebugStreamLine("finished with lift and vertibar");
	if (drive_loads.lowerLift) {
		incrementLiftBy(-50);
		clearTimer(T1);
		waitUntil(withinLiftTarget(20) || time1[T1] > 700);
		delay(400);
	}

	openClaw(100);
	delay(200);
	openClaw(0);

	incrementLiftBy(160);
	delay(900);
	if (drive_loads.maxheight) {
		stopTask(liftpid);
		stopTask(vertpid);
		moveLift(30);

		isRunning = false;
		return;
	}

	// reset the lift the the height of the driver loads
	if (drive_loads.matchLoads) {

		setVertibar(3400, 1600);
		setLift(1600, 800);

		clearTimer(T1);
		waitUntil((within(SensorValue[lift], 1481, 50) && within(SensorValue[vertibar], 3400, 20)) || time1[T1] > 2500);
		} else {
		// lower the vertibar
		setVertibar(3630, 1600);
		setLift(924, 800);

		clearTimer(T1);
		waitUntil((within(SensorValue[lift], 924, 50) && within(SensorValue[vertibar], 3630, 20)) || time1[T1] > 2500);
	}

	stopTask(liftpid);
	stopTask(vertpid);
	moveLift(30);

	isRunning = false;
}


bool setLiftBuildHeight(int cone_stack) {
	switch(cone_stack) {
	case 0:
		drive_loads.height = 1150;
		break;
	case 1:
		drive_loads.height = 1340;
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
		drive_loads.height = 1777;
		break;
	case 7:
		drive_loads.height = 1930;
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
	return true;
}

bool buildMatchLoads(int cone_stack) {

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
	stopTask(liftpid);
	stopTask(vertpid);
	stopTask(buildDriver);
	moveLift(0);
	moveVertibar(0);
}

#endif

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

int vert;
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
	writeDebugStreamLine("buildDriver is being run");
	resetLiftPid();

	// set the lift to the initial height
	if (drive_loads.matchLoads)
		incrementLiftBy(400);

	openClaw(30);

	// move to the correct height and begin moving the vertibar when appropiate or
	// the timer reachers 2.5 seconds.


	clearTimer(T1);
	setLiftTarget(drive_loads.height);


	writeDebugStreamLine("waitUntil lift is at %i", drive_loads.height);
	waitUntil(SensorValue[lift] > drive_loads.height || within(SensorValue[lift], drive_loads.height, 100) || time1[T1] > 2500);
	if (time1[T1] > 2500)
		writeDebugStreamLine("timeout");

	// raise the vertibar
	setVertibar(1000, 1200);
	if (drive_loads.liftMobileGoal) {
		moveMobileGoal(120);
		delay(1200);
		moveMobileGoal(0);
	}

	writeDebugStreamLine("waitUntil lift is at %i", drive_loads.height);
	clearTimer(T1);
	waitUntil(within(SensorValue[lift], drive_loads.height, 100) || SensorValue[lift] > drive_loads.height|| time1[T1] > 1800);
	if (time1[T1] > 2500)
		writeDebugStreamLine("timeout");

	if (drive_loads.lowerLift) {
		writeDebugStreamLine("lowering lift with extra");
		incrementLiftBy(-90);
		clearTimer(T1);
		writeDebugStreamLine("waitUntil lift is at 700");
		waitUntil(withinLiftTarget(20) || time1[T1] > 700);
		if (time1[T1] > 700)
			writeDebugStreamLine("timeout");
		delay(400);
		}
	else {
		writeDebugStreamLine("lowering lift");
		incrementLiftBy(-50);
		delay(200);
	}

	openClaw(100);
	delay(200);
	openClaw(5);

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
		openClaw(100);
		setLiftCap(90);
		setLiftTarget(1630);
		waitUntil(SensorValue[lift] = drive_loads.height);
		setVertibar(vert, 800);
		delay(400);
		openClaw(15);
		setVertibar(3400, 1600);

		clearTimer(T1);
		int prev = SensorValue[lift];
		writeDebugStreamLine("waitUntil lift is at 1640 and vertibar is at 3400");
		while (!(within(SensorValue[lift], 1640, 50) && within(SensorValue[vertibar], 3400, 50) && abs(prev - SensorValue[lift]) < 40) && time1[T1] < 2500) {
			if (time1[T1] > 2500)
				writeDebugStreamLine("timeout");
			if (SensorValue[lift] < 1750)
				setLiftCap(40);
		}
		setLiftCap(120);

		} else {
		// lower the vertibar
		setVertibar(2900, 800);
		setLift(924, 800);
		delay(400);
		setVertibar(3630, 1600);

		clearTimer(T1);
		writeDebugStreamLine("waitUntil lift is at 924 and vertibar is at 3630");
		waitUntil((within(SensorValue[lift], 924, 50) && within(SensorValue[vertibar], 3630, 50)) || time1[T1] > 2500);
		if (time1[T1] > 2500)
			writeDebugStreamLine("timeout at 124");
	}

	stopLiftPid();
	stopVertibarPid();
	isRunning = false;
	moveLift(10);
}

bool setLiftBuildHeight(int cone_stack) {

	switch(cone_stack) {
	case 0:
		drive_loads.height = 1261;
	  vert = 1502;
		break;
	case 1:
		drive_loads.height = 1337;
		vert = 1504;
		break;
	case 2:
		drive_loads.height = 1473;
		vert = 1504;
		break;
	case 3:
		drive_loads.height = 1600;
		vert = 1477;
		break;
	case 4:
		drive_loads.height = 1719;
		vert = 1477;
		break;
	case 5:
		drive_loads.height = 1855;
		vert = 1420;
		break;
	case 6:
		drive_loads.height = 1920;
		drive_loads.lowerLift = true;
		break;
	case 7:
		drive_loads.height = 2000;
		drive_loads.lowerLift = true;
		break;
	case 8:
		drive_loads.height = 2150;
		drive_loads.lowerLift = true;
		break;
	case 9:
		drive_loads.height = 2260;
		drive_loads.lowerLift = true;
		break;
	case 10:
		drive_loads.height = 2240;
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
	writeDebugStreamLine("building match loads: %i", cone_stack);
	setVertibarTarget(3703);
	setLiftTarget(1139);
	startTask(liftpid);
	startTask(vertpid);

	isRunning = true;
	driver = true;

	drive_loads.lowerLift = false;
	drive_loads.maxheight = false;

	if (!setLiftBuildHeight(cone_stack)) return false;

	drive_loads.matchLoads = false;

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
	suspendTask(buildDriver);
	stopTask(buildDriver);
	moveLift(0);
	moveVertibar(0);
}

#endif

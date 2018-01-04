#ifndef AUTOBUILD_DRIVER_LOADS_C
#define AUTOBUILD_DRIVER_LOADS_C
#include "../pid/vertibar.c"
#include "../pid/lift.c"
#include "autonomous.h"

typedef struct {
	int height;
} buildConfiguration;

buildConfiguration drive_loads;

bool isRunning = false;
bool driver = false;


task autonomous() {
	// set the lift to the initial height
	setLift(1481, 800);

	// move to the correct height and begin moving the vertibar when appropiate or
	// the timer reachers 2.5 seconds.
	setLiftTarget(drive_loads.height);
	clearTimer(T1);
	waitUntil(SensorValue[lift] > drive_loads.height || within(SensorValue[lift], 200, drive_loads.height || time1[T1] > 2500);

	// raise the vertibar
	setVertibar(3677, 1600);

	openClaw(100);
	delay(400);
	openClaw(0);

	// lower the vertibar
	setVertibar(1165);


	// reset the lift the the height of the driver loads
	setLift(1481, 800);
}

task buildFull() {

}

void buildDriverLoads(int cone_stack) {
	startTask(liftpid);
	startTask(vertpid);
	isRunning = true;
	driver = true;

	switch(cone_stack) {
	case 0:
		drive_loads.height = 1280;
	}

	startTask(buildDriver);
}

void stopAutoBuild() {
	if (!isRunning) {
		return;
	}
	stopTask(liftpid);
	stopTask(vertpid);
	if (driver) {
		stopTask(buildDriver);
		} else {
		stopTask(buildFull);
	}
}

#endif

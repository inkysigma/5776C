// main autostack logic
bool stacked;
int maxHeight;
task autostackUp() {
	stacked = false;

	// stop any prior lift tasks
	stopTask(autonTopLift);
	stopTask(topLiftPI);
	stopTask(autonMainLift);
	stopTask(mainLiftPI);

	// claw stall
	motor[claw] = -30;

	// bring top lift to intermediary height
	// start by powering max
	topLift.target = 1300;
	topLift.timeout = 4000;
	topLift.power = 127;
	startTask(autonTopLift);
	while (SensorValue[vertibar] < 1500) // change pot value
		wait1Msec(20);

	stopTask(autonTopLift);
	// then PI to exact intermediary height
	motor[vertibar] = 10;

	// lift to desired height
	mainLift.target = maxHeight;
	mainLift.power = 70;
	mainLift.timeout = 4000;
	startTask(autonMainLift);

	// after the lift has risen a certain amount begin raising top lift to max height
	while (SensorValue[lift] < maxHeight - 200)
		wait1Msec(20);

	stopTask(autonTopLift);
	stopTask(topLiftPI);

	topLift.power = 127;
	topLift.target = 2750;
	startTask(autonTopLift);
	while (SensorValue[vertibar] < 2550)
		wait1Msec(20);
	stopTask(autonTopLift);
	motor[vertibar]= 20;

	// open claw at the end
	stopTask(mainLiftPI);
	stopTask(autonMainLift);
	motor[claw] = -50;
	moveMainLift(-127);
	wait1Msec(200);
	moveMainLift(0);
	motor[claw] = 127;
	wait1Msec(100);
	motor[claw] = 0;
	moveMainLift(127);
	waitUntil(SensorValue[lift] > maxHeight);
	moveMainLift(0);

	// flag that cone is stacked
	stacked = true;
}



task fieldReset() {
	motor[claw] = -30;
	wait1Msec(200);
	motor[claw] = 0;

	// bring top lift down
	topLift.power = 127;
	topLift.timeout = 1000;
	topLift.target = 1530;
	if (maxHeight > 1500) {
		startTask(topLiftPI);
	} else {
		startTask(autonTopLift);
	}


	// bring main lift down when top lift is sufficiently far
	while (SensorValue[vertibar] > 1530)
		wait1Msec(20);

	stopTask(topLiftPI);
	moveTopLift(-10);
	mainLift.target = 1300;
	mainLift.power = 70;
	mainLift.timeout = 1500;
	startTask(autonMainLift);
	if (SensorValue[lift] > 1700)
		wait1Msec(300);
	mainLift.power = 127;

	// bring top lift in when main lift is sufficiently far down
	while (SensorValue[lift] > mainLift.target + 400)
		wait1Msec(20);

	stopTask(topLiftPI);
	moveTopLift(-127);
	wait1Msec(500);
	stacked = false;
}

task matchReset() {
	moveConeIntake(-15);

	// bring top lift down
	topLift.target = 1530;
	startTask(topLiftPI);

	// bring main lift down when top lift is sufficiently far
	while (SensorValue[vertibar] > topLift.target)
		wait1Msec(20);

	mainLift.target = 1570;
	mainLift.power = 127;
	mainLift.timeout = 3000;
	startTask(mainLiftPI);

	while (SensorValue[lift] > mainLift.target)
		wait1Msec(20);

	stacked = false;
}

void autostackTaskReset() {
		// stop all tasks relating to autostack
	stopTask(autostackUp);
	stopTask(fieldReset);
	stopTask(matchReset);
	stopTask(autonMainLift);
	stopTask(mainLiftPI);
	stopTask(autonTopLift);
	stopTask(topLiftPI);
	stopTask(autonConeIntake);

	// ensure no motors are moving
	moveMainLift(0);
	moveTopLift(0);

	motor[claw] = 0;
}

void abortAutostack() {
	// stop all tasks relating to autostack
	autostackTaskReset();

	// stops waits
	stacked = true;
	wait1Msec(100);
	stacked = false;
}

bool FIELD = true;
bool MATCH = false;

void autostack(int conesOnMogo, bool reset) {
	// set height to stack cone
	//TUNE THESE VALUES
	if (conesOnMogo == 0) {
		maxHeight = 1320;
	} else if (conesOnMogo == 1) {
		maxHeight = 1420;
	} else if (conesOnMogo == 2) {
		maxHeight = 1550;
	} else if (conesOnMogo == 3) {
		maxHeight = 1670;
	} else if (conesOnMogo == 4) {
		maxHeight = 1920;
	} else if (conesOnMogo == 5) {
		maxHeight = 2070;
	} else if (conesOnMogo == 6) {
		maxHeight = 2140;
	} else if (conesOnMogo == 7) {
		maxHeight = 2280;
	} else if (conesOnMogo == 8) {
		maxHeight = 2410;
	} else if (conesOnMogo == 9) {
		maxHeight = 2510;
	} else if (conesOnMogo == 10) {
		maxHeight = 2640;
	} else if (conesOnMogo == 11) {
		maxHeight = 2900;
	} else if (conesOnMogo <= 12) {
		maxHeight = 3050;
	}

	// autostack
	startTask(autostackUp);
	while (stacked == false)
		wait1Msec(20);
	wait1Msec(100);

// ensure no task carries over to reset
	autostackTaskReset();
	// reset
	if (reset == FIELD) {
		startTask(fieldReset);
		while (stacked == true)
			wait1Msec(20);
	} else {
		startTask(matchReset);
	}
}

task autonStack() {
	// autostack up
	maxHeight = 1450;

	startTask(autostackUp);
	while (stacked == false)
		wait1Msec(20);
	//autostackTaskReset();
}

task autonReset() {
	// field reset
	startTask(fieldReset);

	// wait
	while (stacked == true)
		wait1Msec(20);

	// ensure no task carries over to drive
	abortAutostack();
}

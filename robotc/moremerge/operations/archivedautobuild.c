// do not use this autobuild. it requires a pid which is apparently
// worse in performance.
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

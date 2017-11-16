#include "ops/motor_ops.h"
void moveLiftTo() {
	// move lift using pid
}

void lowerClawPartial() {
	executeUntil({
		lowerClaw(100);
	},
	getSwitchLiftPot() < MID_SWITCH_POT,
	2000);
}

void raiseClawPartial() {
	executeUntil({
		raiseClaw(127);
	},
	getSwitchLiftPot() > MID_SWITCH_POT,
	2000);

}


void closeClawFully() {
	closeClaw(85);
	delay(CLOSE_CLAW_TIME);
	closeClaw(20);
	delay(30);
	claw_open = false;
}

void toggleClaw() {
	if (claw_open == false) {
		claw_open = true;
		openClawFully();
	} else {
		claw_open = false;
		closeClawFully();
	}
}

void releaseCone(bool close) {
	openClaw(100);
	delay(CONE_RELEASE_CONST);
	if (close) {
		closeClawFully();
	}
	else {
		stopClaw();
	}
}


void lowerClawFully() {
<<<<<<< HEAD
	executeUntil({
		lowerClaw(127);
	}, getSwitchLiftPot() < LOW_SWITCH_POT, 4000);
	lowerClaw(0);
}

void raiseClawFully() {
	raiseClaw(127);
	executeUntil({
		raiseClaw(90);
	}, getSwitchLiftPot() > POWER_SWITCH_POT, 4000);
	raiseClaw(90);
	executeUntil({}, getSwitchLiftPot() > HIGH_SWITCH_POT, 4000);
=======
  executeUntil({
  	lowerClaw(127);
  }, getSwitchLiftPot() < LOW_SWITCH_POT, 4000);
  // writeJINXFormat("		Stopped lowering claw at %d which must be greater than than %d\n", getSwitchLiftPot(),
	// 	LOW_SWITCH_POT);
	lowerClaw(0);
}

void raiseClawFully(bool stall) {
  raiseClaw(127);
  executeUntil({}, getSwitchLiftPot() > POWER_SWITCH_POT, 4000);
  // writeJINXFormat("		Stopped raising claw at %d which must be less than than %d\n", getSwitchLiftPot(),
	// 	POWER_SWITCH_POT);
	raiseClaw(90);
  executeUntil({}, getSwitchLiftPot() > HIGH_SWITCH_POT, 4000);
  if (stall) {

  	lowerClaw(15);
	}
	else {
		raiseClaw(0);
	}
  // writeJINXFormat("		Stopped raising claw at %d which must be less than than %d\n", getSwitchLiftPot(),
	// 	HIGH_SWITCH_POT);
>>>>>>> cdba150aacaea904fd7bbcce47d374ffc279fd95
}

void openClawFully() {
	openClaw(90);
	delay(OPEN_CLAW_TIME);
	openClaw(0);
	delay(40);
	claw_open = true;
}


void moveMogoOut() {
	while (getRightMobilePot() < SLOW_ANGLE) {
		moveGoal(SLOW_SPEED);
	}
	while (getRightMobilePot() > OUT_ANGLE) {
		// motor[RightMobileGoal] = FAST_SPEED;
		moveGoal(FAST_SPEED);
	}
}

void moveMogoIn() {
	while (getRightMobilePot() > IN_ANGLE) {
		moveRightMogo(-FAST_SPEED);
		moveLeftMogo(FAST_SPEED);
	}
	moveRightMogo(0);
	moveLeftMogo(0);
}

void syncMogo() {
	while (getRightMobilePot() > IN_ANGLE && getRightMobilePot() > IN_ANGLE) {
		if (getRightMobilePot() > IN_ANGLE) {
			moveRightMogo(-SYNC_SPEED);
		} else {
			moveRightMogo(0);
		}
		if (getLeftMobilePot() > IN_ANGLE) {
			moveLeftMogo(-SYNC_SPEED);
		} else {
			moveLeftMogo(0);
		}
	}
}
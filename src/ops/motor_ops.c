#include "ops/motor_ops.h"
/**
void raiseLiftTo(int cone_level, bool stall) {
	executeUntil({
		setRightLiftTarget(right_pot);
	}, !within(getRightPot(), right_pot, 50), 2500);

	// writeJINXFormat("		Stopped raising lift at %d which must be greater than %d\n", getLeftPot(),
	// 	left_pot);

	if (stall) {
		delay(170);
		applyStall();
	}
	else {
		moveLift(0);
	}
}

void lowerLiftTo(int right_pot, bool stall) {

	executeUntil({
		setRightLiftTarget(right_pot);
	},
	!within(getLeftPot(), right_pot, 50),
	4000);

	// writeJINXFormat("		Stopped lowering lift at %d which must be less than %d\n", getLeftPot(), left_pot);

	if (stall) {
		delay(170);
		applyStall();
	}
	else {
		moveLift(0);
	}
}

void lowerClawPartial(bool stall) {
	executeUntil({
		lowerClaw(100);
	},
	getSwitchLiftPot() < MID_SWITCH_POT,
	2000);

	// writeJINXFormat("		Stopped partially lowering at %d which must be greater than %d\n", getSwitchLiftPot(),
	// 	MID_SWITCH_POT);

	if (stall) {
		raiseClaw(15);
	}
	else {
		moveLift(0);
	}
}

void raiseClawPartial(bool stall) {
	executeUntil({
		raiseClaw(127);
	},
	getSwitchLiftPot() > MID_SWITCH_POT,
	2000);

	// writeJINXFormat("		Stopped partially raising at %d which must be less than %d\n", getSwitchLiftPot(),
	// 	MID_SWITCH_POT);

	if (stall) {
		raiseClaw(15);
	}
	else {
		moveLift(0);
	}
}


void closeClawFully() {
	closeClaw(85);
	delay(CLOSE_CLAW_TIME);
	closeClaw(20);
	delay(30);
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
}

void openClawFully() {
	openClaw(90);
	delay(OPEN_CLAW_TIME);
	openClaw(0);
	delay(40);
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
**/

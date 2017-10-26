#include "ops/motor_ops.h"

const int OUT_ANGLE = 90;
const int IN_ANGLE = 0;
const int FAST_SPEED = 100;
const int SLOW_ANGLE = 45;
const int SLOW_SPEED = 50;
const int SYNC_SPEED = 15;

void raiseLiftTo(int cone_level, bool stall) {
	executeUntil({
		moveLift(80);
		wait1Msec(5);
	}, getLeftPot() < CONE_POT_HEIGHT * cone_level + CONE_POT_CONST, 2500);

	writeDebugStreamLine("		Stopped raising lift at %d which must be greater than %d", getLeftPot(),
		CONE_POT_HEIGHT * cone_level + CONE_POT_CONST);

	if (stall) {
		delay(170);
		applyStall();
	}
	else {
		moveLift(0);
	}
}

void lowerLiftTo(int cone_level, bool stall) {

	executeUntil({
		moveLift(-80);
		wait1Msec(5);
	},
	getLeftPot() > CONE_POT_HEIGHT * cone_level + CONE_POT_CONST,
	4000);

	writeDebugStreamLine("		Stopped lowering lift at %d which must be less than %d", getLeftPot(),
		CONE_POT_HEIGHT * cone_level + CONE_POT_CONST);

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
		wait1Msec(5);
	},
	SensorValue[SwitchLiftPot] < MID_SWITCH_POT,
	2000);

	writeDebugStreamLine("		Stopped partially lowering at %d which must be greater than %d", SensorValue[SwitchLiftPot],
		MID_SWITCH_POT);

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
		wait1Msec(5);
	},
	SensorValue[SwitchLiftPot] > MID_SWITCH_POT,
	2000);

	writeDebugStreamLine("		Stopped partially raising at %d which must be less than %d", SensorValue[SwitchLiftPot],
		MID_SWITCH_POT);

	if (stall) {
		raiseClaw(15);
	}
	else {
		moveLift(0);
	}
}


void closeClawFully() {
	closeClaw(85);
	wait1Msec(CLOSE_CLAW_TIME);
	closeClaw(20);
	wait1Msec(30);
}

void releaseCone(bool close) {
	openClaw(100);
	wait1Msec(CONE_RELEASE_CONST);
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
  	wait1Msec(5);
  }, SensorValue[SwitchLiftPot] < LOW_SWITCH_POT, 4000);
  writeDebugStreamLine("		Stopped lowering claw at %d which must be greater than than %d", SensorValue[SwitchLiftPot],
		LOW_SWITCH_POT);
	lowerClaw(0);
}

void raiseClawFully(bool stall) {
  raiseClaw(127);
  executeUntil({}, SensorValue[SwitchLiftPot] > POWER_SWITCH_POT, 4000);
  writeDebugStreamLine("		Stopped raising claw at %d which must be less than than %d", SensorValue[SwitchLiftPot],
		POWER_SWITCH_POT);
	raiseClaw(90);
  executeUntil({}, SensorValue[SwitchLiftPot] > HIGH_SWITCH_POT, 4000);
  if (stall) {
  	lowerClaw(15);
	}
	else {
		raiseClaw(0);
	}
  writeDebugStreamLine("		Stopped raising claw at %d which must be less than than %d", SensorValue[SwitchLiftPot],
		HIGH_SWITCH_POT);
}

void openClawFully() {
	openClaw(90);
	wait1Msec(OPEN_CLAW_TIME);
	openClaw(0);
	wait1Msec(40);
}


void moveMogoOut() {
	while (SensorValue[MogoRightPot] < SLOW_ANGLE) {
		moveGoal(SLOW_SPEED);
	}
	while (SensorValue[MogoRightPot] > OUT_ANGLE) {
		// motor[RightMobileGoal] = FAST_SPEED;
		moveGoal(FAST_SPEED);
	}
}

void moveMogoIn() {
	while (SensorValue[MogoRightPot] > IN_ANGLE) {
		moveRightMogo(-FAST_SPEED);
		moveLeftMogo(FAST_SPEED);
	}
	moveRightMogo(0);
	moveLeftMogo(0);
}

void syncMogo() {
	while (SensorValue[MogoRightPot] > IN_ANGLE && SensorValue[MogoLeftPot] > IN_ANGLE) {
		if (SensorValue[MogoRightPot] > IN_ANGLE) {
			motor[RightMobileGoal] = -SYNC_SPEED;
		} else {
			motor[RightMobileGoal] = 0;
		}
		if (SensorValue[MogoLeftPot] > IN_ANGLE) {
			motor[LeftMobileGoal] = -SYNC_SPEED;
		} else {
			motor[LeftMobileGoal] = 0;
		}
	}
}

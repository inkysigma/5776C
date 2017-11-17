#include "JINX.h"
#include "ops/motor_ops.h"
#include "util/math.h"

void raiseLift(int left, int right, bool stall) {
  executeUntil({ moveLift(100); }, !withinf(0.9 * left, getLeftPot(), 10) &&
                                       !withinf(0.9 * right, getRightPot(), 10),
               4000);
  executeUntil({ moveLift(80); }, withinf(left, getLeftPot(), 10) &&
                                       withinf(right, getRightPot(), 10),
               4000);
  if (stall) {
    moveLift(40);
  }
}

void lowerLift() {
  executeUntil({ moveLift(-40); },
               !withinf(0, getLeftPot(), 10) && !withinf(0, getRightPot(), 10),
               4000);
}

void raiseClaw() {
  executeUntil({ raiseSwitchLift(100); }, getSwitchLiftPot() < 2800, 3000);
  executeUntil({ raiseSwitchLift((2985 - getSwitchLiftPot()) * 0.7); }, getSwitchLiftPot() < 2985, 2000);
  raiseSwitchLift(0);
  writeJINXMessage("finished raising claw");
}

void lowerClaw() {
  executeUntil({ lowerSwitchLift(80); }, getSwitchLiftPot() > 1800, 4000);
  executeUntil({ lowerSwitchLift((getSwitchLiftPot() - 1700) * 0.6); }, getSwitchLiftPot() > 1760, 4000);
  raiseSwitchLift(20);
  writeJINXMessage("finished lowering claw");
}

void raiseClawPartial(bool stall) {
  executeUntil({ raiseSwitchLift(80); }, getSwitchLiftPot() < 1900, 2000);
  if (stall) {
    raiseSwitchLift(20);
  }
  writeJINXMessage("finished raising claw partial");
}

void openClawFully() {
  openClaw(127);
  delay(600);
  openClaw(10);
}

void closeClawFully(bool stall) {
  closeClaw(80);
  delay(300);
  closeClaw(15);
  delay(40);
}

/**
void raiseLiftTo(int cone_level, bool stall) {
        executeUntil({
                setRightLiftTarget(right_pot);
        }, !within(getRightPot(), right_pot, 50), 2500);

        // writeJINXFormat("		Stopped raising lift at %d which
must be greater than %d\n", getLeftPot(),
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

        // writeJINXFormat("		Stopped lowering lift at %d which
must be less than %d\n", getLeftPot(), left_pot);

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

        // writeJINXFormat("		Stopped partially lowering at %d
which must be greater than %d\n", getSwitchLiftPot(),
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

        // writeJINXFormat("		Stopped partially raising at %d
which must be less than %d\n", getSwitchLiftPot(),
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
  // writeJINXFormat("		Stopped lowering claw at %d which must be
greater than than %d\n", getSwitchLiftPot(),
        // 	LOW_SWITCH_POT);
        lowerClaw(0);
}

void raiseClawFully(bool stall) {
  raiseClaw(127);
  executeUntil({}, getSwitchLiftPot() > POWER_SWITCH_POT, 4000);
  // writeJINXFormat("		Stopped raising claw at %d which must be less
than than %d\n", getSwitchLiftPot(),
        // 	POWER_SWITCH_POT);
        raiseClaw(90);
  executeUntil({}, getSwitchLiftPot() > HIGH_SWITCH_POT, 4000);
  if (stall) {

<<<<<<< HEAD
        lowerClaw(15);
        }
        else {
                raiseClaw(0);
        }
  // writeJINXFormat("		Stopped raising claw at %d which must be less
than than %d\n", getSwitchLiftPot(),
        // 	HIGH_SWITCH_POT);
}

void openClawFully() {
        openClaw(90);
        delay(OPEN_CLAW_TIME);
        openClaw(0);
        delay(40);
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
	claw_open = true;
}**/

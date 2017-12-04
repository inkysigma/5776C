#include "ops/motors.h"
#include "core/robot.h"
#if DEBUG
#include "JINX.h"
#include "util/jinx.h"
#endif
#include "auto/build.h"
#include "pid/lift.h"
#include "pid/vertibar.h"
#include "configuration/pid/lift.h"
#include "util/math.h"

int claw_state = 0;

void raiseLift(int lift) {
  setLiftTarget(lift);
  executeUntil({}, !withinf(lift, getLiftPot(), 10), 2000);
}

void lowerLift() {
  setLiftTarget(LIFT_MIN);
  executeUntil({}, !withinf(0, getLiftPot(), 10), 4000);
}

void raiseClaw(int pos) {
  setVertibarTarget(pos);
  executeUntil({}, !withinf(getChainLift(), pos, 5), 2500);
  moveSwitchLift(0);
}

void lowerClaw(int pos) {
  setVertibarTarget(pos);
  executeUntil({}, !withinf(getChainLift(), pos, 10), 2500);
  moveSwitchLift(0);
}

void resetClaw() {
  stopVertibarPid();
  raiseSwitchLift(100);
  executeUntil({}, digitalRead(3) == HIGH, 7000);
  setVertibarTarget(0);
  resetChainLift();
  resetVertibarPid();
  startVertibarPid();
}

void lowerLiftTo(int lift) {
  setLiftTarget(lift);
  executeUntil({}, !withinf(getLiftPot(), lift, 5), 1000);
}

void openClawFully() {
  openClaw(80);
}

void closeClawFully(bool stall) {
  closeClaw(80);
}

void resetClawState() {
  claw_state = 0;
}

void toggleClawOpen(bool stall) {
  switch (claw_state) {
    case 0:
      closeClawFully(stall);
      claw_state = 1;
      break;
    case 1:
      stallClaw();
      claw_state = 2;
      break;
    case 2:
      openClawFully();
      claw_state = 3;
      break;
    case 3:
      stopClaw();
      claw_state = 0;
      break;
  }
}

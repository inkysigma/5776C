#include "ops/motors.h"
#include "core/robot.h"
#if DEBUG
#include "JINX.h"
#include "util/jinx.h"
#endif
#include "auto/build.h"
#include "pid/lift.h"
#include "pid/vertibar.h"
#include "util/math.h"

bool claw_open = false;

void raiseLift(int lift) {
  setLiftTarget(lift);
  executeUntil({}, !withinf(lift, getLiftPot(), 10), 2000);
}

void lowerLift() {
  setLiftTarget(1560);
  executeUntil({}, !withinf(0, getLiftPot(), 10), 4000);
}

void raiseClaw(int pos) {
  moveSwitchLift(127);
  // setVertibarTarget(pos);
  executeUntil({}, !withinf(getChainLift(), pos, 5), 2500);
  moveSwitchLift(0);
}

void lowerClaw(int pos) {
  moveSwitchLift(-127);
  // setVertibarTarget(pos);
  executeUntil({}, !withinf(getChainLift(), pos, 10), 2500);
  moveSwitchLift(0);
}

void resetClaw() {
  stopVertibarPid();
  raiseSwitchLift(80);
  updateValue("button", digitalRead(3));
  executeUntil({updateValue("button", digitalRead(3));}, digitalRead(3), 2000);
  raiseSwitchLift(0);
  resetVertibarPid();
  startVertibarPid();
}

void lowerLiftTo(int lift) {
  setLiftTarget(lift);
  executeUntil({}, !withinf(getLiftPot(), lift, 5), 1000);
}

void openClawFully() {
  openClaw(100);
  delay(200);
  openClaw(20);
  claw_open = true;
}

void closeClawFully(bool stall) {
  closeClaw(100);
  delay(200);
  closeClaw(40);
  resetChainLift();
  resetVertibarPid();
  claw_open = false;
}

void toggleClawOpen(bool stall) {
  if (claw_open) {
    closeClawFully(stall);
  } else {
    openClawFully();
  }
}

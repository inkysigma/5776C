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
  setLiftTarget(0);
  executeUntil({}, !withinf(0, getLiftPot(), 10), 4000);
}

void raiseClaw(int pos) {
  setVertibarTarget(pos);
  executeUntil({}, !withinf(getChainLift(), pos, 5), 2000);
}

void lowerClaw(int pos) {
  setVertibarTarget(pos);
  executeUntil({}, !withinf(getChainLift(), pos, 10), 1000);
}

void lowerLiftTo(int lift) {
  setLiftTarget(lift);
  executeUntil({}, !withinf(getLiftPot(), lift, 5), 1000);
}

const int PARTIAL_HEIGHT = 2120;
void lowerClawPartial() {
  setVertibarTarget(PARTIAL_HEIGHT);
  executeUntil({}, !withinf(getChainLift(), PARTIAL_HEIGHT, 10), 1000);
}

void raiseClawPartial(bool stall) {
  setVertibarTarget(PARTIAL_HEIGHT);
  executeUntil({}, !withinf(getChainLift(), PARTIAL_HEIGHT, 10), 100);
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
  claw_open = false;
}

void toggleClawOpen(bool stall) {
  if (claw_open) {
    closeClawFully(stall);
  } else {
    openClawFully();
  }
}

void raiseClawPid(int pos) {
  setVertibarTarget(pos);
  executeUntil({}, !withinf(getChainLift(), pos, 10), 3000);
}

void lowerClawPid(int pos) {
  setVertibarTarget(pos);
  executeUntil({}, !withinf(getChainLift(), pos, 10), 3000);
}

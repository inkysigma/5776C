#include "ops/motors.h"
#if DEBUG
#include "JINX.h"
#include "util/jinx.h"
#endif
#include "auto/build.h"
#include "pid/lift.h"
#include "pid/vertibar.h"
#include "util/math.h"

bool claw_open = false;

void raiseLift(int left, int right) {
  setLiftTarget(left, right);
  executeUntil({}, !withinf(left, getLeftPot(), 10), 2000);
}

void lowerLift() {
  setLiftTarget(0, 0);
  executeUntil({}, !withinf(0, getLeftPot(), 10), 4000);
}

void raiseClaw(int pos) {
  setVertibarTarget(pos);
  executeUntil({}, !withinf(getSwitchLiftPot(), pos, 5), 2000);
}

void lowerClaw(int pos) {
  setVertibarTarget(pos);
  executeUntil({}, !withinf(getSwitchLiftPot(), pos, 10), 1000);
}

void lowerLiftTo(int left, int right) {
  setLiftTarget(left, right);
  executeUntil({}, !withinf(getLeftPot(), left, 5), 1000);
}

const int PARTIAL_HEIGHT = 2120;
void lowerClawPartial() {
  setVertibarTarget(PARTIAL_HEIGHT);
  executeUntil({}, !withinf(getSwitchLiftPot(), PARTIAL_HEIGHT, 10), 1000);
}

void raiseClawPartial(bool stall) {
  setVertibarTarget(PARTIAL_HEIGHT);
  executeUntil({}, !withinf(getSwitchLiftPot(), PARTIAL_HEIGHT, 10), 100);
}

void openClawFully() {
  openClaw(127);
  delay(300);
  openClaw(20);
  claw_open = true;
}

void closeClawFully(bool stall) {
  closeClaw(100);
  delay(300);
  closeClaw(40);
  delay(40);
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
  executeUntil({}, !withinf(getSwitchLiftPot(), pos, 10), 3000);
}

void lowerClawPid(int pos) {
  setVertibarTarget(pos);
  executeUntil({}, !withinf(getSwitchLiftPot(), pos, 10), 3000);
}

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

bool claw_open = false;
bool claw_running = false;

void raiseLift(int lift) {
  setLiftTarget(lift);
  executeUntil({}, !withinf(lift, getLiftPot(), 10), 2000);
}

void lowerLift() {
  setLiftTarget(LEFT_MIN);
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
  writeJINXMessage("reset the claw");
  stopVertibarPid();
  raiseSwitchLift(80);
  executeUntil({}, digitalRead(3) == HIGH, 3000);
  resetVertibarPid();
  startVertibarPid();
}

void lowerLiftTo(int lift) {
  setLiftTarget(lift);
  executeUntil({}, !withinf(getLiftPot(), lift, 5), 1000);
}

void openClawFully() {
  openClaw(80);
  claw_open = true;
  claw_running = true;
}

void closeClawFully(bool stall) {
  closeClaw(80);
  claw_open = false;
  claw_running = true;
}

void toggleClawOpen(bool stall) {
  if (claw_running) {
    writeJINXMessage("hello");
    claw_running = false;
    stopClaw();
    return;
  }
  if (claw_open) {
    closeClawFully(stall);
  } else {
    openClawFully();
  }
}

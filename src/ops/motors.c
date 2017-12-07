#include "ops/motors.h"
#include "core/robot.h"
#include "auto/build.h"
#include "pid/lift.h"
#include "pid/vertibar.h"
#include "configuration/pid/lift.h"
#include "util/math.h"

int claw_state = 0;

void setLift(int lift) {
  setLiftTarget(lift);
  executeUntil({}, !within(lift, getLiftPot(), 10), 2000);
}

void setClaw(int pos) {
  setVertibarTarget(pos);
  executeUntil({delay(100);}, !within(getChainLift(), pos, 17), 1500);
}

void resetClaw() {
  stopVertibarPid();
  raiseSwitchLift(100);
  executeUntil({}, digitalRead(3) == HIGH, 7000);
  raiseSwitchLift(0);
  resetChainLift();
  setVertibarTarget(0);
  resetVertibarPid();
  startVertibarPid();
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

#include "ops/motors.h"
#include "core/robot.h"
#include "auto/build.h"
#include "pid/lift.h"
#include "pid/vertibar.h"
#include "configuration/pid/lift.h"
#include "util/math.h"
#include "JINX.h"

int claw_state = 0;
bool mogo_out = false;

void setLift(int lift) {
  setLiftTarget(lift);
  executeUntil({}, !within(lift, getLiftPot(), 10), 2000);
}

void setClaw(int pos) {
  setVertibarTarget(pos);
  executeUntil({delay(100);}, !within(getChainLift(), pos, 35), 1300);
}

void resetClaw() {
  stopVertibarPid();
  executeUntil({raiseSwitchLift(100);}, digitalRead(3) == HIGH, 2500);
  raiseSwitchLift(10);
  resetChainLift();
  delay(40);
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

void openGoal() {
    moveGoal(127);
    executeUntil({delay(100);}, !within(getMobileGoalPot(), MOGO_OUT, 3), 1300);
    moveGoal(0);
    mogo_out = true;
}

void retractGoal() {
    moveGoal(-127);
    executeUntil({delay(100);}, !within(getMobileGoalPot(), MOGO_IN, 3), 1300);
    moveGoal(0);
    mogo_out = false;
}

void toggleGoal() {
    if (mogo_out == false)
        openGoal();
    else
        retractGoal();
}

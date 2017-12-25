#include "ops/build.h"
#include "ops/motors.h"
#include "configuration/pid/lift.h"
#include "configuration/robot.h"
#include "pid/lift.h"
#include "pid/vertibar.h"
#include "util/math.h"

#if DEBUG
#include "JINX.h"
#endif

void setLift(int lift) {
  setLiftTarget(lift);
  executeUntil({}, !within(lift, getLiftPot(), 30), 2000);
}

void setClaw(int pos) {
  setVertibarTarget(pos);
  executeUntil({}, !within(getVertibarPot(), pos, 40), 1300);
}

void openClawFully() {
  openClaw(20);
  delay(500);
  openClaw(10);
}

void closeClawFully() {
  closeClaw(80);
  delay(200);
  closeClaw(25);
}

void openGoal() {
  moveGoal(127);
  executeUntil({ delay(100); }, !within(getMobileGoalPot(), MOGO_OUT, 3), 1300);
  moveGoal(0);
}

void retractGoal() {
  moveGoal(-127);
  executeUntil({ delay(100); }, !within(getMobileGoalPot(), MOGO_IN, 3), 1300);
  moveGoal(0);
}

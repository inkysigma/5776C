#include "ops/motor_ops.h"
#include "JINX.h"
#include "auto/build.h"
#include "util/math.h"
#include "util/jinx.h"

bool claw_open = false;

void raiseLift(int left, int right, bool stall) {
  executeUntil({
                moveLift((left - getLeftPot()) * 0.9);
              },
               (!withinf(left, getLeftPot(), 10) && !withinf(right, getRightPot(), 10)),
               2000);
  if (stall) {
    moveLift(20);
  }
}

void lowerLift() {
  executeUntil({ moveLift(-100); },
               (!withinf(0, getLeftPot(), 10) && !withinf(0, getRightPot(), 10)),
               4000);
}

void raiseClaw(int pos) {
  executeUntil(
      { raiseSwitchLift((pos - getSwitchLiftPot()) * 0.6); },
      !withinf(getSwitchLiftPot(), pos, 5), 2000);
  raiseSwitchLift(0);
}

void lowerClaw(int pos) {
  executeUntil({ lowerSwitchLift((getSwitchLiftPot() - pos) * 0.7); },
               !withinf(getSwitchLiftPot(), pos, 10), 1000);
  raiseSwitchLift(0);
}

void lowerLiftTo(int left, int right) {
  if (left < getLeftPot()) {
    return;
  }
  executeUntil({ moveLift((getLeftPot() - left) * -0.8); },
               !withinf(getLeftPot(), left, 5) &&
                   !withinf(getRightPot(), right, 5),
               1000);
  moveLift(20);
}

const int PartialHeight = 2120;
void lowerClawPartial() {
  executeUntil({ lowerSwitchLift((getSwitchLiftPot() - PartialHeight) * 0.9); },
               !withinf(getSwitchLiftPot(), PartialHeight, 10), 1000);
  raiseSwitchLift(30);
}

void raiseClawPartial(bool stall) {
  executeUntil({ lowerSwitchLift((getSwitchLiftPot() - PartialHeight) * 1.1); },
               !withinf(getSwitchLiftPot(), PartialHeight, 10), 100);
  if (stall) {
    raiseSwitchLift(30);
  }
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

#include "ops/motor_ops.h"
#include "JINX.h"
#include "auto/build.h"
#include "util/math.h"

bool claw_open = false;

void raiseLift(int left, int right, bool stall) {
  if (left < getLeftPot()) {
    return;
  }
  executeUntil({ moveLift((left - getLeftPot()) * 0.9); },
               !withinf(left, getLeftPot(), 10) &&
                   !withinf(right, getRightPot(), 10) &&
                   left < 1.2 * left && right < 1.2 * right,
               2000);
  if (stall) {
    moveLift(40);
  }
}

void lowerLift() {
  executeUntil({ moveLift(-100); },
               !withinf(0, getLeftPot(), 10) && !withinf(0, getRightPot(), 10),
               4000);
}

const int RAISED_POSITION = 3230;
void raiseClaw(int pos) {
  executeUntil({ raiseSwitchLift(100); },
               getSwitchLiftPot() < 0.9 * pos, 2000);
  executeUntil(
      { raiseSwitchLift((pos - getSwitchLiftPot()) * 0.7); },
      getSwitchLiftPot() < pos, 1000);
  executeUntil({ lowerSwitchLift(getSwitchLiftPot() - pos); },
               withinf(getSwitchLiftPot(), pos, 20), 250);
  raiseSwitchLift(0);
}

void lowerClaw(int pos) {
  executeUntil({ lowerSwitchLift(80); }, getSwitchLiftPot() > 1.2 * pos, 2000);
  executeUntil({ lowerSwitchLift((getSwitchLiftPot() - pos) * 0.6); },
               getSwitchLiftPot() > pos, 2000);
  executeUntil({ raiseSwitchLift((pos - getSwitchLiftPot()) * 0.6); },
               getSwitchLiftPot() < pos, 400);
  raiseSwitchLift(10);
}

void lowerLiftTo(int left, int right) {
  if (left < getLeftPot()) {
    return;
  }
  executeUntil({ moveLift((getLeftPot() - left) * -0.8); },
               !withinf(getLeftPot(), left, 5) &&
                   !withinf(getRightPot(), right, 5),
               2000);
  moveLift(20);
}

const int PartialHeight = 2120;
void lowerClawPartial() {
  executeUntil({ lowerSwitchLift(80); },
               getSwitchLiftPot() > 1.1 * PartialHeight, 1000);
  executeUntil({ lowerSwitchLift((getSwitchLiftPot() - PartialHeight) * 0.6); },
               getSwitchLiftPot() > PartialHeight, 1000);
  executeUntil({ raiseSwitchLift((PartialHeight - getSwitchLiftPot()) * 0.3); },
               PartialHeight > getSwitchLiftPot(), 200);

  raiseSwitchLift(30);
}

void raiseClawPartial(bool stall) {
  executeUntil({ raiseSwitchLift(90); }, getSwitchLiftPot() < PartialHeight,
               2000);
  executeUntil({ lowerSwitchLift((getSwitchLiftPot() - PartialHeight) * 0.6); },
               getSwitchLiftPot() > PartialHeight, 100);
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

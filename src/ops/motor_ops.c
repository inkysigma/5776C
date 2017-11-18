#include "JINX.h"
#include "ops/motor_ops.h"
#include "util/math.h"

bool claw_open = false;

void raiseLift(int left, int right, bool stall) {
  executeUntil({ moveLift(100); }, !withinf(0.9 * left, getLeftPot(), 10) &&
                                       !withinf(0.9 * right, getRightPot(), 5),
               4000);
  executeUntil({ moveLift(80); }, !withinf(left, getLeftPot(), 10) &&
                                      !withinf(right, getRightPot(), 5),
               4000);
  if (stall) {
    moveLift(40);
  }
}

void lowerLift() {
  executeUntil({ moveLift(-100); },
               !withinf(0, getLeftPot(), 10) && !withinf(0, getRightPot(), 10),
               4000);
}

const int RAISED_POSITION = 3000;
void raiseClaw() {
  executeUntil({ raiseSwitchLift(100); }, getSwitchLiftPot() < 0.9 * RAISED_POSITION,
               2000);
  executeUntil(
      { raiseSwitchLift((RAISED_POSITION - getSwitchLiftPot()) * 0.7); },
      getSwitchLiftPot() < RAISED_POSITION, 1000);
  executeUntil({ lowerSwitchLift(getSwitchLiftPot() - RAISED_POSITION); },
               withinf(getSwitchLiftPot(), RAISED_POSITION, 20), 250);
  raiseSwitchLift(0);
}

const int LOWERED_POSITION = 1630;
void lowerClaw() {
  executeUntil({ lowerSwitchLift(80); }, getSwitchLiftPot() > 1770, 4000);
  executeUntil({ lowerSwitchLift((getSwitchLiftPot() - 1750) * 0.6); },
               getSwitchLiftPot() > 1750, 2000);
  executeUntil({ raiseSwitchLift((1750 - getSwitchLiftPot()) * 0.6); },
               getSwitchLiftPot() < 1750, 2000);
  raiseSwitchLift(20);
}

void lowerClawPartial() {
  executeUntil({
    lowerSwitchLift(80);
  }, getSwitchLiftPot() > 2000, 1000);
  executeUntil({
    lowerSwitchLift((getSwitchLiftPot() - 1870) * 0.6);
  }, getSwitchLiftPot() > 1870, 1000);
  raiseSwitchLift(20);
}

void lowerLiftTo(int left, int right) {
  executeUntil({ moveLift(-100); }, !withinf(getLeftPot(), left, 5) &&
    !withinf(getRightPot(), right, 5), 2000);
  moveLift(40);
}

const int PartialHeight = 2000;
void raiseClawPartial(bool stall) {
  executeUntil({ raiseSwitchLift(90); }, getSwitchLiftPot() < PartialHeight, 2000);
  executeUntil({ lowerSwitchLift((getSwitchLiftPot() - PartialHeight) * 0.6); }, getSwitchLiftPot() > PartialHeight, 700);
  if (stall) {
    raiseSwitchLift(25);
  }
}

void openClawFully() {
  openClaw(127);
  delay(300);
  openClaw(0);
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

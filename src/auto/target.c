#include "auto/target.h"
#include "core/sensors.h"
#include "core/motors.h"
#include "util/math.h"
#include "util/concurrency.h"

pid *leftLift;
pid *rightLift;
pid *leftDrive;
pid *rightDrive;
pid *switchLift;

void setLiftConfig(pid *left, pid *right) {
  leftLift = left;
  rightLift = right;
}

void setDriveConfig(pid *left, pid *right) {
  leftDrive = left;
  rightDrive = right;
}

void setSwitchLiftConfig(pid *config) {
  switchLift = config;
}

void updateLeftLift() {
  moveLeftLift(pidStep(leftLift));
}

void updateRightLift() {
  moveRightLift(pidStep(rightLift));
}

bool targetLiftHeight(int target, int timeout) {
  int t = 0;
  while (t < timeout && !within(getLeftPot(), target, 50) && !within(getRightPot(), target, 50)) {
    updateLeftLift();
    updateRightLift();
    delay(20);
    t += 20;
  }
  if (t > timeout) {
    return false;
  }
  return true;
}

bool targetDrive(int target, int timeout) {
  resetIme();
  executeUntil({
    moveDrive(pidStep(leftDrive), pidStep(rightDrive));
  }, !within(getLeftIme(), target, 50) && !within(getRightIme(), target, 50), timeout);
  if (!within(getLeftIme(), target, 50) && !within(getRightIme(), target, 50))
    return false;
  return true;
}

bool targetSwitchLift(int target, int timeout) {
  executeUntil({
    moveSwitchLift(pidStep(switchLift));
  }, !within(getSwitchLiftPot(), target, 50), timeout);
  if (!within(getSwitchLiftPot(), target, 50))
    return false;
  return true;
}

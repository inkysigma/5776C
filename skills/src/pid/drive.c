#include "pid/drive.h"
#include "core/motors.h"
#include "pid/left.h"
#include "pid/right.h"
#include "util/math.h"

void setDriveTarget(int left, int right) {
  setLeftDriveGoal(left);
  setRightDriveGoal(right);
}

void updateDriveTargets() {
  float left = stepLeftPid();
  float right = stepRightPid();
  float maximum = max(abs(left), abs(right));
  if (!isLeftWithin(90) && !isRightWithin(90))
    moveDrive(left / maximum * 128, right / maximum * 128);
  moveDrive(left, right);
}

void resetDriveFeedback() {
  resetLeftDriveFeedback();
  resetRightDriveFeedback();
}
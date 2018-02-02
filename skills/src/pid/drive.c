#include "pid/drive.h"
#include "pid/left.h"
#include "pid/right.h"

void setDriveTarget(int left, int right) {
  setLeftDriveGoal(left);
  setRightDriveGoal(right);
}

void updateDriveTargets() {
  updateLeftDriveCompletion();
  updateRightDriveCompletion();
}

void resetDriveFeedback() {
  resetLeftDriveFeedback();
  resetRightDriveFeedback();
}
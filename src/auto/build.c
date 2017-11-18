#include "JINX.h"
#include "auto/build.h"
#include "ops/motor_ops.h"

int left[12] = {0, 0, 60, 120, 170, 436, 570, 717, 0, 0};

int right[12] = {0, 0, 60, 120, 202, 565, 700, 911, 0, 0};

int leftLower [12] = {0, 0, 0, 20, 70, 300, 350, 650};

int rightLower [12] = {0, 0, 0, 20, 70, 260, 450, 800};

bool autoBuildRunning = false;

void buildStackHelper(int left, int right, int left_lower, int right_lower) {
  closeClawFully(true);
  raiseClawPartial(true);
  raiseLift(left, right, true);
  raiseClaw();
  delay(300);
  lowerLiftTo(left_lower, right_lower);
  openClawFully();
  moveLift(100);
  delay(400);
  moveLift(40);
  lowerClawPartial();
  lowerLift();
  lowerClaw();
  moveLift(-127);
  delay(350);
  moveLift(0);
}

void buildStack(int cone_level) {
  autoBuildRunning = true;
  buildStackHelper(left[cone_level], right[cone_level],
    leftLower[cone_level], rightLower[cone_level]);
  autoBuildRunning = false;
}

int getAutoBuildRunning() {
  return autoBuildRunning;
}

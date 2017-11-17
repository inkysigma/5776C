#include "auto/build.h"
#include "ops/motor_ops.h"
#include "JINX.h"

int left [10] = {
  0,
  170,
  340,
  0,
  0,
  0,
  0,
  0,
  0,
  0
};

int right [10] = {
  0,
  170,
  340,
  0,
  0,
  0,
  0,
  0,
  0,
  0
};


void buildStackHelper(int left, int right) {
  closeClawFully(true);
  raiseClawPartial(true);
  raiseLift(left, right, true);
  raiseClaw();
  delay(300);
  openClawFully();
  lowerClaw();
  lowerLift();
}

void buildStack(int cone_level) {
  buildStackHelper(left[cone_level], right[cone_level]);
}

#include "ops/target.h"
#include "core/motors.h"
#include "core/sensors.h"
#include "util/concurrency.h"

void rotate(int degrees) {
  int leftMul, rightMul;
  if (degrees > 0) {
    leftMul = -1;
    rightMul = 1;
  } else {
    rightMul = -1;
    leftMul = 1;
  }
  int target = degrees * 10;
  resetGyro();
  executeUntil({
    int difference = abs(getGyro() - target);
    moveDrive(leftMul * difference, rightMul * difference);
  }, !within(getGyro(), target, 5) && getLeftVelocity() < 20, degrees * 10);
}

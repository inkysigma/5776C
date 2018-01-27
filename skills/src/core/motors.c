#include "core/motors.h"

void setLeftDrive(int power) {
 moveLeftDrive(power);
}

void setRightDrive(int power) {
  moveRightDrive(power);
}

void setMobileGoal(int power) {
  openMobileGoal(power);
}

void setRotate(int power) {
  moveRotate(power);
}

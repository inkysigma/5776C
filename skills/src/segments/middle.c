#include "JINX.h"
#include "pid/mobile.h"
#include "core/motors.h"
#include "core/sensors.h"
#include "pid/left.h"
#include "pid/right.h"
#include "segments.h"
#include "util/concurrency.h"
#include "util/math.h"

void middle() {
  resetLeftDriveFeedback();
  resetRightDriveFeedback();
  resetGyro();

  // begin opening the mobile goal and wait 200 milliseconds to ensure that we
  // have enough
  // time to reach the target value
  setMobileGoalDriveGoal(1928);
  waitUntil(isMobileGoalConfident(), 3000);

  moveDrive(127, 127);
  executeUntil({ moveDrive(upperBound(1360 - readRightDrive(), 80), upperBound(1360 - readRightDrive(), 80)); },
               readRightDrive() < 1380, 2700);
  delay(100);

  setMobileGoalDriveGoal(550);

  moveDrive(0, 0);

  waitUntil(isMobileGoalConfident(), 1500);

  executeUntil({ moveDrive(upperBound(120 - readRightDrive(), 70), upperBound(120 - readRightDrive(), 70)); },
               !(within(readRightDrive(), 150, 20) || readRightDrive() < 180),
               2000);
  moveDrive(10, 10);
  delay(200);
  moveDrive(0, 0);
}
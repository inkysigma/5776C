#include "JINX.h"
#include "core/motors.h"
#include "core/sensors.h"
#include "pid/left.h"
#include "pid/mobile.h"
#include "pid/right.h"
#include "segments.h"
#include "util/concurrency.h"
#include "util/math.h"


void middle() {
  resetRightDrive();
  resetGyro();
  startMobileGoalDriveFeedback();

  // begin opening the mobile goal and wait 200 milliseconds to ensure that we
  // have enough
  // time to reach the target value
  setMobileGoalDriveGoal(1890);
  waitUntil(isMobileGoalConfident(), 4000);

  moveDrive(127, 127);
  executeUntil(
      {
        moveDrive(upperBound(1360 - readRightDrive(), 80),
                  upperBound(1360 - readRightDrive(), 80));
      },
      readRightDrive() < 1380, 2700);
  delay(100);

  setMobileGoalDriveGoal(550);

  moveDrive(0, 0);

  waitUntil(isMobileGoalConfident(), 5000);
  pauseMobileGoalDriveFeedback();
  openMobileGoal(10);
  executeUntil(
      {
        moveDrive(upperBound(120 - readRightDrive(), 70),
                  upperBound(120 - readRightDrive(), 70));
      },
      !(within(readRightDrive(), 150, 20) || readRightDrive() < 180), 2000);
  moveDrive(10, 10);
  delay(200);
  moveDrive(0, 0);
}
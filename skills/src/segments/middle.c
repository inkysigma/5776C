#include "JINX.h"
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

  // startLeftDriveFeedback();
  // startRightDriveFeedback();

  // begin opening the mobile goal and wait 200 milliseconds to ensure that we
  // have enough
  // time to reach the target value
  openMobileGoal(127);
  delay(400);

  moveDrive(127, 127);
  executeUntil({ openMobileGoal(1900 - readMobileGoalPot()); },
               !(readMobileGoalPot() > 1960), 1000);
  closeMobileGoal(5);

  setRightDriveGoal(1300);
  executeUntil({ moveDrive(1300 - readRightDrive(), 1300 - readRightDrive()); },
               readRightDrive() < 1300, 2000);
  delay(100);
  closeMobileGoal(127);
  delay(200);

  moveDrive(0, 0);

  executeUntil({ closeMobileGoal(readMobileGoalPot() - 1120); },
               !(readMobileGoalPot() < 1120), 1000);
  openMobileGoal(10);

  executeUntil({ moveDrive(100 - readRightDrive(), 100 - readRightDrive()); },
               !(within(readRightDrive(), 100, 20) || readRightDrive() < 90),
               2000);
  moveDrive(10, 10);
  delay(200);
  moveDrive(0, 0);
  openMobileGoal(10);

  writeJINXMessage("finished middle");
}
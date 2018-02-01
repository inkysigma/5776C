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

  // begin opening the mobile goal and wait 200 milliseconds to ensure that we
  // have enough
  // time to reach the target value
  openMobileGoal(127);
  delay(400);

  moveDrive(127, 127);
  executeUntil({ openMobileGoal(1785 - readMobileGoalPot()); },
               !(readMobileGoalPot() > 1810), 1300);
  closeMobileGoal(5);


  executeUntil({ moveDrive(upperBound(1360 - readRightDrive(), 80), upperBound(1360 - readRightDrive(), 80)); },
               readRightDrive() < 1380, 2700);
  delay(100);
  closeMobileGoal(127);
  delay(600);

  moveDrive(0, 0);

  executeUntil({ closeMobileGoal(readMobileGoalPot() - 520); },
               !(readMobileGoalPot() < 520), 1000);
  openMobileGoal(20);

  executeUntil({ moveDrive(upperBound(200 - readRightDrive(), 70), upperBound(200 - readRightDrive(), 70)); },
               !(within(readRightDrive(), 270, 20) || readRightDrive() < 250),
               2000);
  moveDrive(10, 10);
  delay(200);
  moveDrive(0, 0);
  openMobileGoal(10);

  writeJINXMessage("finished middle");
}
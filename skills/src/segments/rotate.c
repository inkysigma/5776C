#include "core/motors.h"
#include "core/sensors.h"
#include "pid/drive.h"
#include "pid/left.h"
#include "pid/right.h"
#include "segments.h"

#include "JINX.h"
#include "pid/right.h"
#include "util/concurrency.h"
#include "util/jinx.h"
#include "util/math.h"

void rotateDeposit(bool clockwise) {
  if (clockwise) {
    writeJINXMessage("entered rotate");
    executeUntil(
        {
          moveDrive(upperBound(187 - readGyro(), 60), -upperBound(187 - readGyro(), 60));
          updateValue("gyro_auto", readGyro());
        },
        !within(readGyro(), 187, 5), 1500);
  } else {
    executeUntil({ moveDrive(-upperBound(187 + readGyro(), 70), upperBound(187 + readGyro(), 70)); },
                 !within(readGyro(), 187, 5), 1500);
  }
  moveDrive(100, 94);
  delay(600);
  moveDrive(0, 0);

  openMobileGoal(100);
  waitUntil(readMobileGoalPot() > 1850, 2000);

  resetLeftDriveFeedback();
  resetRightDriveFeedback();
  startLeftDriveFeedback();
  startRightDriveFeedback();
  closeMobileGoal(80);
  delay(200);
  closeMobileGoal(60);
  setDriveTarget(-400, -400);
  waitUntil(readMobileGoalPot() < 320, 2000);
  openMobileGoal(0);
  waitUntil(isDriveConfident(), 1000);

  stopLeftDriveFeedback();
  stopRightDriveFeedback();
}
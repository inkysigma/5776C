#include "JINX.h"
#include "core/motors.h"
#include "core/sensors.h"
#include "pid/drive.h"
#include "pid/left.h"
#include "pid/right.h"
#include "util/JINX.h"
#include "util/concurrency.h"
#include "util/math.h"

void cross() {
  resetGyro();
  resetDriveFeedback();
  executeUntil(
      {
        moveDrive(upperBound(-(165 + readGyro()), 80),
                  upperBound((165 + readGyro()), 80));
      },
      !within(readGyro(), -170, 5), 5000);
  moveDrive(10, -10);
  delay(400);
  moveDrive(0, 0);
  openMobileGoal(70);
  waitUntil(readMobileGoalPot() > 1745, 3000);
  openMobileGoal(-10);
  delay(300);
  resetDriveFeedback();
  startLeftDriveFeedback();
  startRightDriveFeedback();
  setDriveTarget(3083, 2250);
  waitUntil(within(readLeftDrive(), 2000, 10) || readLeftDrive() > 2100, 5000);

  // close mobile goal when crossing
  closeMobileGoal(80);
  waitUntil(readMobileGoalPot() < 320, 4000);
  openMobileGoal(60);
  delay(100);
  openMobileGoal(0);
  delay(500);
  waitUntil(isDriveConfident(), 4000);

  pauseLeftDriveFeedback();
  pauseRightDriveFeedback();
  moveDrive(0, 0);
}
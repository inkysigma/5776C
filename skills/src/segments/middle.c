#include "JINX.h"
#include "core/motors.h"
#include "core/sensors.h"
#include "pid/drive.h"
#include "pid/left.h"
#include "pid/mobile.h"
#include "pid/right.h"
#include "segments.h"
#include "util/concurrency.h"
#include "util/jinx.h"
#include "util/math.h"

void middle() {
  resetRightDriveFeedback();
  resetLeftDriveFeedback();
  resetGyro();
  startRightDriveFeedback();
  startLeftDriveFeedback();

  openMobileGoal(70);
  waitUntil(readMobileGoalPot() > 1735, 2500);
  openMobileGoal(-10);
  delay(300);

  resetRightDriveFeedback();
  resetLeftDriveFeedback();
  setDriveTarget(1220, 880);
  waitUntil(isDriveConfident(), 3000);
  writeJINXMessage("we are within range");
  moveDrive(0, 0);

  stopLeftDriveFeedback();
  stopRightDriveFeedback();
  moveDrive(60, 35);
  delay(500);
  moveDrive(0, 0);
  resetGyro();

  // retrat the mobile goal properly
  closeMobileGoal(127);
  waitUntil(readMobileGoalPot() < 320, 4000);
  writeJINXMessage("we have retracted");
  openMobileGoal(60);
  delay(100);
  openMobileGoal(0);
  delay(500);

  startRightDriveFeedback();
  startLeftDriveFeedback();
  setDriveTarget(320, 80);
  waitUntil(isDriveConfident(), 2000);

  writeJINXMessage("ending the middle phase");
  stopLeftDriveFeedback();
  stopRightDriveFeedback();
  moveDrive(0, 0);

  resetGyro();
}
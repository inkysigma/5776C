#include "segments.h"
#include "core/motors.h"
#include "core/sensors.h"
#include "util/concurrency.h"
#include "pid/left.h"
#include "pid/right.h"
#include "util/math.h"

void side() { 
  // reset the encoder values so we have a better base to work from
  resetLeftDriveFeedback();
  resetRightDriveFeedback();

  // begin opening the mobile goal and wait 200 milliseconds to ensure that we have enough
  // time to reach the target value
  openMobileGoal(127);
  delay(400);

  moveDrive(127, 127);
  executeUntil({
    openMobileGoal(1900 - readMobileGoalPot());
  }, !(readMobileGoalPot() > 1960), 1000);
  closeMobileGoal(5);

  executeUntil({
    moveDrive(1690 - readRightDrive(), 1690 - readRightDrive());
  }, readRightDrive() < 1700, 2000);
  delay(100);
  closeMobileGoal(127);
  delay(200);
  
  moveDrive(0, 0);

  executeUntil({
    closeMobileGoal(readMobileGoalPot() - 620);
  }, !(readMobileGoalPot() < 620), 1000);
  openMobileGoal(10);

  executeUntil({
    moveDrive(5 - readRightDrive(), 5 - readRightDrive());
  }, !(within(readRightDrive(), 0, 20) || readRightDrive() < -5), 2000);
  moveDrive(10, 10);
  delay(200);
  moveDrive(0, 0);
  openMobileGoal(10);
}
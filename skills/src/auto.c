/** @file auto.c
 * @brief File for autonomous code
 *
 * This file should contain the user autonomous() function and any functions
 * related to it.
 *
 * Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "JINX.h"
#include "core/motors.h"
#include "core/sensors.h"
#include "main.h"
#include "pid/drive.h"
#include "pid/left.h"
#include "pid/mobile.h"
#include "pid/right.h"
#include "segments.h"
#include "util/concurrency.h"
#include "util/jinx.h"
#include "util/math.h"

/*
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. If the robot is disabled or communications is lost, the autonomous task
 * will be stopped by the kernel. Re-enabling the robot will restart the task,
 * not re-start it from where it left off.
 *
 * Code running in the autonomous task cannot access information from the VEX
 * Joystick. However, the autonomous function can be invoked from another task
 * if a VEX Competition Switch is not available, and it can access joystick
 * information if called in this way.
 *
 * The autonomous task may exit, unlike operatorControl() which should never
 * exit. If it does so, the robot will await a switch to another mode or
 * disable/enable cycle.
 */

void autonomous() {
  // start the middle
  middle();

  // try to deposit the cone in the twenty point zone
  resetGyro();
  executeUntil(
      {
        moveDrive(upperBound(2 * (100 - readGyro()), 60),
                  upperBound(-2 * (100 - readGyro()), 60));
      },
      !within(readGyro(), 100, 5), 1500);
  moveDrive(-30, 30);
  delay(100);
  moveDrive(0, 0);

  resetLeftDriveFeedback();
  resetRightDriveFeedback();
  executeUntil(
      {
        moveDrive(upperBound(380 - readRightDrive(), 60),
                  upperBound(380 - readRightDrive(), 50));
      },
      !within(readRightDrive(), 385, 5), 2000);
  resetGyro();
  executeUntil(
      {
        moveDrive(upperBound(2 * (95 - readGyro()), 60),
                  upperBound(-1.8 * (95 - readGyro()), 55));
      },
      !within(readGyro(), 95, 5), 1700);
  moveDrive(-30, 30);
  delay(100);
  moveDrive(0, 0);

  resetLeftDriveFeedback();
  resetRightDriveFeedback();
  moveDrive(90, 90);
  waitUntil(readRightDrive() > 600, 3000);
  openMobileGoal(127);
  delay(900);
  moveDrive(-60, -60);
  closeMobileGoal(127);
  waitUntil(readMobileGoalPot() < 620, 1000);
  openMobileGoal(30);
  delay(200);
  openMobileGoal(10);

  writeJINXMessage("begin backing up");
  moveDrive(-70, -70);
  waitUntil(readRightDrive() < 200, 1000);
  moveDrive(40, 40);
  delay(200);
  moveDrive(0, 0);

  // begin to rotate again to get the second into the ten point zone
  resetGyro();
  executeUntil(
      {
        moveDrive(upperBound(-91 - readGyro(), 80),
                  -upperBound(-91 - readGyro(), 80));
      },
      !within(readGyro(), 92, 7), 1700);
  moveDrive(10, -10);
  delay(200);
  moveDrive(0, 0);

  // move forward into position
  resetRightDrive();
  executeUntil({ moveDrive(418 - readRightDrive(), 418- readRightDrive()); },
               !within(readRightDrive(), 427, 5), 1500);
  moveDrive(-10, -10);
  delay(200);
  moveDrive(0, 0);

  // rotate
  resetGyro();
  executeUntil(
      {
        moveDrive(upperBound((-85 - readGyro()), 60),
                  -upperBound((-85 - readGyro()), 60));
      },
      !within(readGyro(), -90, 7), 1700);
  moveDrive(10, -10);
  delay(500);
  moveDrive(0, 0);

  // begin the middle again
  resetRightDriveFeedback();
  resetLeftDriveFeedback();
  resetGyro();
  startRightDriveFeedback();
  startLeftDriveFeedback();

  openMobileGoal(70);
  waitUntil(readMobileGoalPot() > 1735, 3000);
  openMobileGoal(-10);
  delay(300);

  resetRightDriveFeedback();
  resetLeftDriveFeedback();
  setDriveTarget(880, 710);
  waitUntil(isDriveConfident(), 3000);
  writeJINXMessage("we are within range");
  moveDrive(0, 0);

  stopLeftDriveFeedback();
  stopRightDriveFeedback();
  moveDrive(50, 35);
  delay(400);
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
  setDriveTarget(80, -75);
  waitUntil(isDriveConfident(), 2000);

  writeJINXMessage("ending the middle phase");
  stopLeftDriveFeedback();
  stopRightDriveFeedback();

  // rotate and deposit
  rotateDeposit(true);

  // we need to cross the field in order to get the mobile goal
  cross();
  resetGyro();

  // finish up by rotating and depositing
  executeUntil(
      {
        moveDrive(-2 * upperBound(90 + readGyro(), 70),
                  2 * upperBound(90 + readGyro(), 70));
      },
      within(readGyro(), -90, 5), 2000);
  moveDrive(5, -5);
  delay(500);
  moveDrive(0, 0);

  resetLeftDriveFeedback();
  resetRightDriveFeedback();
  executeUntil(
      {
        moveDrive(upperBound(350 - readRightDrive(), 60),
                  upperBound(350 - readRightDrive(), 60));
      },
      !within(readRightDrive(), 350, 7), 2000);

  resetGyro();
  // finish up by rotating and depositing
  executeUntil(
      {
        moveDrive(upperBound(90 + readGyro(), 75),
                  -upperBound(90 + readGyro(), 70));
      },
      within(readGyro(), 93, 5), 2000);
  moveDrive(5, -5);
  delay(500);
  moveDrive(0, 0);

  resetRightDriveFeedback();
  resetLeftDriveFeedback();
  moveDrive(90, 90);
  waitUntil(readRightDrive() > 600, 3000);
  openMobileGoal(127);
  delay(900);
  moveDrive(-60, -60);
  closeMobileGoal(127);
  waitUntil(readMobileGoalPot() < 620, 1000);
  openMobileGoal(30);
  delay(200);
  openMobileGoal(10);

  resetDrive();
  writeJINXMessage("begin backing up");
  moveDrive(-70, -70);
  waitUntil(readRightDrive() < -500, 1000);
  moveDrive(40, 40);
  delay(200);
  moveDrive(0, 0);
}

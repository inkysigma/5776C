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
        moveDrive(upperBound(2 * (92 - readGyro()), 60),
                  upperBound(-2 * (95 - readGyro()), 60));
      },
      !within(readGyro(), 94, 5), 1500);
  moveDrive(-30, 30);
  delay(100);
  moveDrive(0, 0);

  resetRightDriveFeedback();
  executeUntil(
      {
        moveDrive(upperBound(235 - readRightDrive(), 80),
                  upperBound(235 - readRightDrive(), 80));
      },
      !within(readRightDrive(), 245, 10), 2000);
  resetGyro();
  executeUntil(
      {
        moveDrive(upperBound(2 * (95 - readGyro()), 60),
                  upperBound(-2 * (95 - readGyro()), 60));
      },
      !within(readGyro(), 95, 5), 1700);
  moveDrive(-30, 30);
  delay(100);
  moveDrive(0, 0);

  resetRightDriveFeedback();
  moveDrive(90, 90);
  waitUntil(readRightDrive() > 600, 3000);
  openMobileGoal(127);
  delay(900);
  moveDrive(-60, -60);
  startMobileGoalDriveFeedback();
  setMobileGoalDriveGoal(620);
  moveDrive(-127, -127);
  waitUntil(readRightDrive() < 50, 1000);
  moveDrive(10, 10);
  delay(200);
  moveDrive(0, 0);

  // begin to rotate again to get the second into the ten point zone
  resetGyro();
  executeUntil(
      {
        moveDrive(upperBound(-90 - readGyro(), 80),
                  -upperBound(-90 - readGyro(), 80));
      },
      !within(readGyro(), 92, 5), 1700);
  moveDrive(10, -10);
  delay(200);
  moveDrive(0, 0);

  // move forward into position
  resetRightDrive();
  executeUntil({ moveDrive(240 - readRightDrive(), 240 - readRightDrive()); },
               !within(readRightDrive(), 250, 10), 1500);
  moveDrive(-10, -10);
  delay(200);
  moveDrive(0, 0);

  // rotate
  resetGyro();
  executeUntil(
      {
        moveDrive(upperBound(2 * (-85 - readGyro()), 70),
                  -upperBound(2 * (-85 - readGyro()), 70));
      },
      !within(readGyro(), 90, 5), 1700);

  // try to get the other middle mobile goal cone
  middle();
  executeUntil(
      {
        moveDrive(upperBound(-10 - readRightDrive(), 60),
                  upperBound(-10 - readRightDrive(), 60));
      },
      !within(readRightDrive(), -5, 10), 1000);

  // rotate and deposit
  rotateDeposit(true);
}

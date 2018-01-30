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

#include "core/motors.h"
#include "core/sensors.h"
#include "main.h"
#include "pid/left.h"
#include "pid/mobile.h"
#include "pid/right.h"
#include "util/concurrency.h"
#include "util/jinx.h"
#include "util/math.h"
#include "JINX.h"

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
  // reset the encoder values so we have a better base to work from
  resetLeftDriveFeedback();
  resetRightDriveFeedback();

  // startLeftDriveFeedback();
  // startRightDriveFeedback();

  // begin opening the mobile goal and wait 200 milliseconds to ensure that we have enough
  // time to reach the target value
  openMobileGoal(127);
  delay(400);

  moveDrive(127, 127);
  executeUntil({
    openMobileGoal(1900 - readMobileGoalPot());
  }, !(readMobileGoalPot() > 1960), 1000);
  closeMobileGoal(5);

  setRightDriveGoal(1300);
  executeUntil({
    moveDrive(1300 - readRightDrive(), 1300 - readRightDrive());
  }, readRightDrive() < 1300, 2000);
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

  // stopRightDriveFeedback();
}

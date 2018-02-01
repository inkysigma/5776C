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
  startMobileGoalDriveFeedback();
  middle();
  resetGyro();
  executeUntil({ moveDrive(upperBound(92 - readGyro(), 60), upperBound(-(92 - readGyro()), 60)); },
               !within(readGyro(), 90, 5), 1500);
  moveDrive(-30, 30);
  delay(100);
  moveDrive(0, 0);

  resetRightDriveFeedback();
  executeUntil({ moveDrive(100 - readRightDrive(), 100 - readRightDrive()); },
               !within(readRightDrive(), 120, 10), 600)

  resetGyro();
  executeUntil({ moveDrive(upperBound(87 - readGyro(), 60), upperBound(-(87 - readGyro()), 60)); },
               !within(readGyro(), 90, 5), 1500);

  resetRightDriveFeedback();
  moveDrive(60, 60);
  waitUntil(readRightDrive() > 800, 3000);
  openMobileGoal(100);
  delay(600);
  moveDrive(-60, -60);
  closeMobileGoal(40);
  delay(800);
  moveDrive(-127, -127);
  waitUntil(readRightDrive() < 20, 1000);
  moveDrive(10, 10);
  delay(200);
  moveDrive(0, 0);
}

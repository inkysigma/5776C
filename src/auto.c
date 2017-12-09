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
#include "main.h"
#include "ops/motors.h"
#include "ops/auto.h"
#include "pid/lift.h"
#include "pid/vertibar.h"
#include "pid/drive.h"
#include "util/math.h"

/*
 * Runs the user autonomous code. This function will be started in its own task
 * with the default
 * priority and stack size whenever the robot is enabled via the Field
 * Management System or the
 * VEX Competition Switch in the autonomous mode. If the robot is disabled or
 * communications is
 * lost,  the autonomous task will be stopped by the kernel. Re-enabling the
 * robot will restart
 * the task, not re-start it from where it left off.
 *
 * Code running in the autonomous task cannot access information from the VEX
 * Joystick. However,
 * the autonomous function can be invoked from another task if a VEX Competition
 * Switch is not
 * available, and it can access joystick information if called in this way.
 *
 * The autonomous task may exit, unlike operatorControl() which should never
 * exit. If it does
 * so, the robot will await a switch to another mode or disable/enable cycle.
 */

#define FIRST_STEP 1600
#define SECOND_STEP 1600
#define MOVE_BACK -100

void stationary_goal_auton() {
  startLiftPid();
  startVertibarPid();
  setLiftTarget(2175);
  setVertibarTarget(300);
  moveDrive(-127, -127);
  delay(1700);
  moveDrive(0, 0);
  setVertibarTarget(150);
  executeUntil({}, !within(getChainLift(), 150, 10), 2000);
  openClawFully();
  delay(300);
  stopClaw();
  moveDrive(127, 0);
  delay(600);
  moveDrive(127, 100);
  delay(600);
  moveDrive(0, 0);
}

void mogo_auton() {
  startVertibarPid();
  startDrivePid();
  openGoal();
  setDriveTarget(FIRST_STEP, FIRST_STEP);
  executeUntil({}, !within(getRightDrive(), FIRST_STEP, 10), 5000);
  delay(100);
  retractGoal();
  rotate(180);
  resetDrive();
  setDriveTarget(SECOND_STEP, SECOND_STEP);
  executeUntil({}, !within(getRightDrive(), SECOND_STEP, 10), 6000);
  openGoal();
  resetDrive();
  setDriveTarget(MOVE_BACK, MOVE_BACK);
  executeUntil({}, !within(getRightDrive(), MOVE_BACK, 10), 700);
}

void autonomous() { mogo_auton(); }

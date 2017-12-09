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
#include "core/robot.h"
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
void programmingSkills() {

}

void stationaryGoalDisable() {
  setLiftTarget(2175);
  setVertibarTarget(300);
  moveDrive(-127, -127);
  delay(1400);
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

void defensive() {
  moveDrive(127, 127);
  delay(2500);
  moveDrive(0, 0);
}

void mobileGoal() {
  setDriveTarget(1400, -1400);
}

void autonomous() {

  if (autonomousSelect == 0) {
    defensive();
  } else if (autonomousSelect == 1) {
    mobileGoal();
  } else if (autonomousSelect == 2) {
    programmingSkills();
  }
}

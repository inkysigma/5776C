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
#include "ops/motor_ops.h"
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
bool isKill(int current, int target, int time, int max) {
  if (abs(current) < target && time > max) {
    return true;
  }
  return false;
}

void pickUpCone(int level) {}

void rotate(int degrees) {
  // Remember to scale the degree value by 1000
  degrees *= 1000;
  int first_pause = degrees * 0.6;
  int second_pause = degrees * 0.75;
  int third_pause = degrees * 0.9;
  while (getPrimaryGyro() < first_pause) {
    rotateDrive(sgn(degrees) * 100);
  }

  while (getPrimaryGyro() < second_pause) {
    rotateDrive(sgn(degrees) * 70);
  }

  while (getPrimaryGyro() < third_pause) {
    rotateDrive(sgn(degrees) * 50);
  }

  while (getPrimaryGyro() < degrees) {
    rotateDrive(sgn(degrees) * 10);
  }
  rotateDrive(0);
}

void setDrive(int ticks) {
  resetIme();
  int timePassed = 0;
  while ((abs(getRightIme()) < 0.7 * ticks) &&
         !isKill(getRightIme(), ticks, timePassed, 2500)) {
    moveDrive(100, 100);
    delay(20);
    timePassed += 20;
  }
  moveDrive(0, 0);

  while (abs(getRightIme()) < 0.8 * ticks &&
         !isKill(getRightIme(), ticks, timePassed, 2500)) {
    moveDrive(70, 70);
    delay(20);
    timePassed += 20;
  }

  while (abs(getRightIme()) < ticks &&
         !isKill(getRightIme(), ticks, timePassed, 2500)) {
    moveDrive(10, 10);
    delay(20);
    timePassed += 20;
  }
  moveDrive(0, 0);
}

void pickUpMobileGoal() {}

void putDownMobileGoal() {}

void auto1() {
  // TODO: Implement the actual methods and find the associated values
  int ticks = 0;

  // NOTE: Don't use tile. Apparently is inaccurate to convert due to momentum
  // and inertia
  setDrive(ticks);
  rotate(90);
  pickUpCone(0);
  rotate(-90);
  setDrive(ticks);
  rotate(90);
  setDrive(ticks);
  rotate(90);
  pickUpMobileGoal();
  setDrive(ticks);
  rotate(90);
  pickUpCone(1);
  setDrive(ticks);
  pickUpCone(2);
  setDrive(ticks);
  rotate(-90);
  setDrive(ticks);
  rotate(45);
  setDrive(ticks);
  putDownMobileGoal();
}

void auto2() {
  int ticks = 1000;

  setDrive(ticks);
  rotate(90);
  setDrive(ticks);
  rotate(90);
  setDrive(ticks);
  pickUpMobileGoal();
  rotate(90);
  setDrive(ticks);
  pickUpCone(0);
  setDrive(ticks);
  pickUpCone(1);
  rotate(-90);
  setDrive(ticks);
  pickUpCone(2);
  rotate(90);
  setDrive(ticks);
  rotate(-90);
  setDrive(ticks);
  rotate(45);
  setDrive(ticks);
  putDownMobileGoal();
}
void autonomous() {}

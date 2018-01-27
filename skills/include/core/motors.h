/**
 * @file core/motors.h
 *
 * @brief This file contains the core functionality of the motors by creating
 *        methods to interact with components rather than motors directly.
 *
 *        e.g moveMotor(int left, int right) will move the left and right sides
 *            with the power supplied.
 *
 *        This file is not recompiled when you change it. Thus running make clean
 *        is necessary.
 *
 *        IMPORTANT: If you change this file, run make clean to delete old
 *                   binaries. Given that this problem has occurred multiple
 *                   times, I cannot stress that you need to run make clean
 *
 *        TL;DR make clean
**/
#include "configuration/motors.h"

#ifndef _CORE_MOTORS_H
#define _CORE_MOTORS_H
#include "API.h"

/**
 * @brief Sets the speed of the left side of the drive.
 * @param The speed to set the left drive to.
 **/
inline void moveLeftDrive(int power) {
  motorSet(LeftDriveFront, -power);
  motorSet(LeftDriveBack, power);
}


/**
 * @brief Sets the speed of the right side of the drive.
 * @param power The speed to set the right drive to.
 **/
inline void moveRightDrive(int power) {
  motorSet(RightDriveFront, power);
  motorSet(RightDriveBack, -power);
}

/**
 * @brief Sets the speed of the left and right side of the drive.
 * @param left The speed to set the left side to
 * @param right The Speed to set the right drive to.
 **/
inline void moveDrive(int left, int right) {
  moveLeftDrive(left);
  moveRightDrive(right);
}

/**
 * @brief Sets the speed of the left and right side of the drive to rotate
 * @param power The speed to rotate at
 **/
inline void moveRotate(int power) {
  moveDrive(power, -power);
}

/**
 * @brief Sets the power to open the mobile goal.
 * @param The power to open the mobile goal at.
 **/
inline void openMobileGoal(int power) {
  motorSet(LeftMobileGoal, power);
  motorSet(RightMobileGoal, -power);
}

/**
 * @brief Sets the power to close the mobile goal.
 * @param The power to close the mobile goal at.
 **/
inline void closeMobileGoal(int power) {
  openMobileGoal(-power);
}

void setLeftDrive(int power);
void setRightDrive(int power);
void setMobileGoal(int power);
void setRotate(int power);

#endif

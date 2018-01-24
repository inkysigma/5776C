/**
 * @file configuration/motors.h
 *
 * @brief This file contains the configuration of the motors by defining a
 *        variable to mean to the expected port. This file, when included,
 *        will ensure that the variable name is replaced by the extension.
 *
 *        e.g #define DriveMotor 1 in this file will change
 *          motorSet(DriveMotor, 2) to motorSet(1, 2) during COMPILE time.
 *
 *        IMPORTANT: If you change this file, run make clean to delete old
 *                   binaries. Given that this problem has occurred multiple
 *                   times, I cannot stress that you need to run make clean
 *
 *        TL;DR make clean
**/
#ifndef _MOTORS_H
#define _MOTORS_H

#define Claw 2
#define LeftDriveBack 3
#define LeftDriveFront 4
#define LeftMobileGoal 5
#define RightMobileGoal 6
#define RightDriveBack 7
#define RightDriveFront 8
#define Miscellaneous 9

#endif

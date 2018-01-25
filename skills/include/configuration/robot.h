/**
 * @file configuration/robot.h
 *
 * @brief This file contains the configuration of the robot. This file has one
 *        single definition switching between DEBUG mode and RELEASE mode. To
 *        turn debugging on, set DEBUG to 1. This will enable JINX to run and
 *        print sensor values. Leave this at 1 by default.
 *
 *        IMPORTANT: If you change this file, run make clean to delete old
 *                   binaries. Given that this problem has occurred multiple
 *                   times, I cannot stress that you need to run make clean
 *
 *        TL;DR make clean
**/
#ifndef _CONFIGURATION_SENSORS_H
#define _CONFIGURATION_SENSORS_H

/** Digital sensor ports **/
#define RightEncoder 2
#define LeftEncoder 4

/** Analog sensor ports **/
#define MobileGoalPot 1
#define MainGyro 2
#define SecondaryGyro 3

#endif

/**
 * @file configuration/sensors.h
 *
 * @brief This file contains the configuration of the sensors by defining a
 *        variable to mean to the expected port. This file, when included,
 *        will ensure that the variable name is replaced by the extension.
 *
 *        e.g #define LiftPot 1 in this file will change
 *          analogRead(LiftPot, 2) to analogRead(1, 2) during COMPILE time.
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
#define LEFT_ENCODER 2
#define LEFT_ENCODER_SECONDARY 3
#define RIGHT_ENCODER 4
#define RIGHT_ENCODER_SECONDARY 5

/** Analog sensor ports **/
#define MAIN_GYRO 1
#define SECONDARY_GYRO 2
#define MOBILE_GOAL_POT 3

#endif

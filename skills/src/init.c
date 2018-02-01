/** @file init.c
 * @brief File for initialization code
 *
 * This file should contain the user initialize() function and any functions
 * related to it.
 *
 * Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "configuration/pid.h"
#include "configuration/sensors.h"
#include "core/motors.h"
#include "core/sensors.h"
#include "debug/sensors.h"
#include "fbc.h"
#include "fbc_pid.h"
#include "main.h"
#include "pid/left.h"
#include "pid/right.h"
#include "pid/mobile.h"
#include "pid/rotate.h"

Encoder leftEncoder;
Encoder rightEncoder;
Gyro mainGyro;

/*
 * Runs pre-initialization code. This function will be started in kernel mode
 * one time while the VEX Cortex is starting up. As the scheduler is still
 * paused, most API functions will fail.
 *
 * The purpose of this function is solely to set the default pin modes
 * (pinMode()) and port states (digitalWrite()) of limit switches, push buttons,
 * and solenoids. It can also safely configure a UART port (usartOpen()) but
 * cannot set up an LCD (lcdInit()).
 */
void initializeIO() { watchdogInit(); }

/*
 * Runs user initialization code. This function will be started in its own task
 * with the default priority and stack size once when the robot is starting up.
 * It is possible that the VEXnet communication link may not be fully
 * established at this time, so reading from the VEX Joystick may fail.
 *
 * This function should initialize most sensors (gyro, encoders, ultrasonics),
 * LCDs, global variables, and IMEs.
 *
 * This function must exit relatively promptly, or the operatorControl() and
 * autonomous() tasks will not start. An autonomous mode selection menu like the
 * pre_auton() in other environments can be implemented in this task if desired.
 */
void initialize() {
  analogCalibrate(MAIN_GYRO);
  analogCalibrate(SECONDARY_GYRO);
  analogCalibrate(MOBILE_GOAL_POT);

  mainGyro = gyroInit(MAIN_GYRO, 0);

  leftEncoder = encoderInit(LEFT_ENCODER, LEFT_ENCODER_SECONDARY, false);
  rightEncoder = encoderInit(RIGHT_ENCODER, RIGHT_ENCODER_SECONDARY, true);


  initLeftDriveFeedback(LEFT_DRIVE_KP, LEFT_DRIVE_KI, LEFT_DRIVE_KD,
                        LEFT_DRIVE_MIN_I, LEFT_DRIVE_MAX_I);
  initRightDriveFeedback(RIGHT_DRIVE_KP, RIGHT_DRIVE_KI,
                       RIGHT_DRIVE_DT, RIGHT_DRIVE_MIN_I, RIGHT_DRIVE_MAX_I);
  initMobileGoalFeedback(MOBILE_GOAL_KP, MOBILE_GOAL_KI,
                       MOBILE_GOAL_KD, MOBILE_GOAL_MIN_I, MOBILE_GOAL_MAX_I);
  initRotateFeedback(ROTATE_KP, ROTATE_KI, ROTATE_KD,
                       ROTATE_MIN_I, ROTATE_MAX_I);
  
  delay(1000);

#if DEBUG
  taskCreate(JINXRun, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
  taskCreate(writeSensors, TASK_DEFAULT_STACK_SIZE, NULL,
             TASK_PRIORITY_DEFAULT);
#endif
}

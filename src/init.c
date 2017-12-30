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

#include "main.h"

#include "configuration/pid/lift.h"
#include "configuration/pid/drive.h"
#include "configuration/pid/vertibar.h"
#include "pid/lift.h"
#include "pid/drive.h"
#include "pid/vertibar.h"
#include "debug/sensors.h"

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
 void initializeIO() {
   watchdogInit();
 }

 int autonomousSelect = 0;
 TaskHandle jinx;
 TaskHandle debug;

 Gyro mainGyro;

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
  setTeamName("5776C");
  setLiftPidConfig(LIFT_KP, LIFT_KI, LIFT_KD);
  setVertibarConfig(VERT_KP, VERT_KI, VERT_KD);
  setLeftDrivePid(LEFT_DRIVE_KP, LEFT_DRIVE_KI, LEFT_DRIVE_KD, LEFT_DRIVE_DT);
  setRightDrivePid(RIGHT_DRIVE_KP, RIGHT_DRIVE_KI, RIGHT_DRIVE_KD, RIGHT_DRIVE_DT);

  imeInitializeAll();

  mainGyro = gyroInit(MainGyro, 0);

#if DEBUG
  jinx = taskCreate(JINXRun, TASK_DEFAULT_STACK_SIZE, NULL,
                    (TASK_PRIORITY_DEFAULT));
  debug = taskCreate(writeSensors, TASK_DEFAULT_STACK_SIZE, NULL,
                     TASK_PRIORITY_DEFAULT);
#endif
}

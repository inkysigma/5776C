/** @file init.c
 * @brief File for initialization code
 *
 * This file should contain the user initialize() function and any functions related to it.
 *
 * Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"
#include "core/robot.h"
#include "JINX.h"
#include "debug/pot.h"
#include "pid/lift_pid.h"
#include "configuration/pid/lift.h"
/*
 * Runs pre-initialization code. This function will be started in kernel mode one time while the
 * VEX Cortex is starting up. As the scheduler is still paused, most API functions will fail.
 *
 * The purpose of this function is solely to set the default pin modes (pinMode()) and port
 * states (digitalWrite()) of limit switches, push buttons, and solenoids. It can also safely
 * configure a UART port (usartOpen()) but cannot set up an LCD (lcdInit()).
 */
void initializeIO() {
    watchdogInit();
}

TaskHandle jinx;
TaskHandle debug;

/*
 * Runs user initialization code. This function will be started in its own task with the default
 * priority and stack size once when the robot is starting up. It is possible that the VEXnet
 * communication link may not be fully established at this time, so reading from the VEX
 * Joystick may fail.
 *
 * This function should initialize most sensors (gyro, encoders, ultrasonics), LCDs, global
 * variables, and IMEs.
 *
 * This function must exit relatively promptly, or the operatorControl() and autonomous() tasks
 * will not start. An autonomous mode selection menu like the pre_auton() in other environments
 * can be implemented in this task if desired.
 */
void initialize() {
    imeInitializeAll();
    analogCalibrate(LeftLiftPot);
    analogCalibrate(RightLiftPot);
    setInit(analogReadCalibrated(LeftLiftPot), analogReadCalibrated(RightLiftPot));
    analogCalibrate(SwitchLiftPot);
    setTeamName("5776C");
    initPid(*leftConfig, LEFT_KP, LEFT_KI, LEFT_KD, LEFT_DT, LeftLiftPot);
    initPid(*rightConfig, RIGHT_KP, RIGHT_KI, RIGHT_KD, RIGHT_DT, RightLiftPot);
    jinx = taskCreate(JINXRun, TASK_DEFAULT_STACK_SIZE, NULL, (TASK_PRIORITY_DEFAULT));
    debug = taskCreate(writePots, TASK_DEFAULT_STACK_SIZE / 2, NULL, (TASK_PRIORITY_DEFAULT));
}

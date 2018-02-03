/** @file opcontrol.c
 * @brief File for operator control code
 *
 * This file should contain the user operatorControl() function and any
 * functions related to it.
 *
 * Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */
#include "JINX.h"
#include "configuration/robot.h"
#include "configuration/sensors.h"
#include "core/controls.h"
#include "core/motors.h"
#include "fbc.h"
#include "main.h"
#include "pid/left.h"
#include "pid/mobile.h"
#include "pid/right.h"
#include "pid/rotate.h"
#include "pid/drive.h"
#include "util/concurrency.h"
#include "util/math.h"

/*
 * Runs the user operator control code. This function will be started in its own
 * task with the default priority and stack size whenever the robot is enabled
 * via the Field Management System or the VEX Competition Switch in the operator
 * control mode. If the robot is disabled or communications is lost, the
 * operator control task will be stopped by the kernel. Re-enabling the robot
 * will restart the task, not resume it from where it left off.
 *
 * If no VEX Competition Switch or Field Management system is plugged in, the
 * VEX Cortex will run the operator control task. Be warned that this will also
 * occur if the VEX Cortex is tethered directly to a computer via the USB A to A
 * cable without any VEX Joystick attached.
 *
 * Code running in this task can take almost any action, as the VEX Joystick is
 * available and the scheduler is operational. However, proper use of delay() or
 * taskDelayUntil() is highly recommended to give other tasks (including system
 * tasks such as updating LCDs) time to run.
 *
 * This task should never exit; it should end with some kind of infinite loop,
 * even if empty.
 */
bool running = false;
void operatorControl() {
  while (1) {
    int turn = (getLeftTurn() + getRightTurn()) / 2;
    if (!getTaskRunning()) {
      if (!running) {
        moveDrive(lowerBound(getLeftJoystick() + turn, 20),
                  lowerBound(getRightJoystick() - turn, 20));
      }

      if (running) {
        updateDriveTargets();
      }
      if (getOpenMobileGoal()) {
        openMobileGoal(100);
      } else if (getCloseMobileGoal()) {
        closeMobileGoal(100);
      } else {
        openMobileGoal(0);
      }

      if (getTestFeedback()) {
        running = true;
        setDriveTarget(300, 300);
        waitUntil(!getTestFeedback(), 1000);
      }

      if (getStopTestFeedback()) {
        running = false;
        resetDriveFeedback();
        openMobileGoal(0);
        moveDrive(0, 0);
      }
    }
    delay(20);
  }
}

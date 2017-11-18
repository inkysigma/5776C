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
#include "auto/build.h"
#include "configuration/pid/lift.h"
#include "configuration/pid/vertibar.h"
#include "main.h"

#include "core/controls.h"
#include "core/motors.h"
#include "core/sensors.h"

#include "pid/lift.h"
#include "pid/vertibar.h"
#include "pid/pidlib.h"

#include "ops/motor_ops.h"
#include "util/math.h"

#include "JINX.h"

pid leftConfig;
pid rightConfig;
pid vertibarConfig;

/*
 * Runs the user operator control code. This function will be started in its own
 * task with the
 * default priority and stack size whenever the robot is enabled via the Field
 * Management System
 * or the VEX Competition Switch in the operator control mode. If the robot is
 * disabled or
 * communications is lost, the operator control task will be stopped by the
 * kernel. Re-enabling
 * the robot will restart the task, not resume it from where it left off.
 *
 * If no VEX Competition Switch or Field Management system is plugged in, the
 * VEX Cortex will
 * run the operator control task. Be warned that this will also occur if the VEX
 * Cortex is
 * tethered directly to a computer via the USB A to A cable without any VEX
 * Joystick attached.
 *
 * Code running in this task can take almost any action, as the VEX Joystick is
 * available and
 * the scheduler is operational. However, proper use of delay() or
 * taskDelayUntil() is highly
 * recommended to give other tasks (including system tasks such as updating
 * LCDs) time to run.
 *
 * This task should never exit; it should end with some kind of infinite loop,
 * even if empty.
 */
void operatorControl() {
  initPid(&leftConfig, LEFT_KP, LEFT_KI, LEFT_KD, LEFT_DT, &getLeftPot);
  initPid(&rightConfig, RIGHT_KP, RIGHT_KI, RIGHT_KD, RIGHT_DT, &getRightPot);
  initPid(&vertibarConfig, VERT_KP, VERT_KI, VERT_KD, VERT_DT, &getSwitchLiftPot);
  setLiftPidConfig(&leftConfig, &rightConfig);
  // startLiftPid();
  int cones = 0;
  while (true) {
    int turn = (getJoystickLeftTurn() + getJoystickRightTurn()) / 2.5;
    moveDrive(getJoystickLeft() + turn, getJoystickRight() - turn);

    if (!getAutoBuildRunning() && !getDebugTaskRunning()) {
      if (getRaiseLift()) {
        moveLift(127);
      } else if (getLowerLift()) {
        moveLift(-127);
      } else {
        if (getRightPot() < 300) {
          moveLift(0);
        } else {
          moveLift(30);
        }
      }

      if (getRaiseClaw()) {
        raiseSwitchLift(100);
      } else if (getLowerClaw()) {
        lowerSwitchLift(100);
      } else {
        raiseSwitchLift(0);
      }

      if (getToggleClaw()) {
        toggleClawOpen(true);
      }

      if (getOpenGoal()) {
        moveGoal(100);
      } else if (getRetractGoal()) {
        moveGoal(-100);
      } else {
        moveGoal(0);
      }

      if (getBuildStack()) {
        buildStack(cones);
        cones++;
      } else if (getIncreaseStack()) {
        cones++;
      } else if (getDecreaseStack()) {
        cones--;
      } else if (getResetStack()) {
        cones = 0;
      }
    }
    delay(40);
  }
}

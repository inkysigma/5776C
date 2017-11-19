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

#include "core/controls.h"
#include "core/motors.h"
#include "core/sensors.h"
#include "main.h"
#include "util/jinx.h"

#include "ops/userops.h"

#include "JINX.h"

#include "auto/build.h"
#include "configuration/pid/lift.h"
#include "configuration/pid/vertibar.h"

#include "pid/lift.h"
#include "pid/pidlib.h"

#include "ops/motor_ops.h"
#include "util/math.h"

pid liftConfig;

bool isClawPartial = false;

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
  initPid(&liftConfig, LEFT_KP, LEFT_KI, LEFT_KD, LEFT_DT, &getLeftPot);
  setLiftPidConfig(&liftConfig);
  startLiftPid();
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
        } else if (!getAutoBuildRunning()) {
          moveLift(30);
        }
      }

      if (getRaiseClaw()) {
        isClawPartial = false;
        raiseSwitchLift(100);
      } else if (getLowerClaw()) {
        isClawPartial = false;
        lowerSwitchLift(100);
      } else if (getRaiseClawPartial()) {
        isClawPartial = true;
        raiseClawPartial(true);
      } else {
        if (!isClawPartial)
          raiseSwitchLift(0);
      }

      if (getToggleClaw()) {
        toggleClawOpen(true);
      }

      if (getToggleGoal()) {
        moveGoal(100);
      } else if (getBuildStackPartial()) {
        moveGoal(-100);
      } else {
        moveGoal(0);
      }

      if (getBuildStack()) {
        buildStack(getConeCount());
        incrementConeCount();
      } else if (getIncreaseStack()) {
        if (getConeCount() < 14)
          incrementConeCount();
      } else if (getDecreaseStack()) {
        if (getConeCount() > 0)
          decrementConeCount();
      } else if (getResetStack()) {
        resetConeCount();
      }
    }
    delay(40);
  }
}

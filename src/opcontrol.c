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
#include "core/robot.h"

#include "main.h"

#include "ops/motors.h"
#include "ops/user.h"

#if DEBUG
#include "JINX.h"
#endif

#include "auto/build.h"
#include "configuration/pid/lift.h"
#include "configuration/pid/vertibar.h"

#include "pid/lift.h"
#include "pid/pidlib.h"
#include "pid/vertibar.h"

#include "util/jinx.h"
#include "util/math.h"

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
  bool isClawPartial = false;
  setLiftTarget(getLiftPot());
  startLiftPid();
  startVertibarPid();
  while (true) {
    int turn = (getJoystickLeftTurn() + getJoystickRightTurn()) / 2.5;
    moveDrive(getJoystickLeft() + turn, getJoystickRight() - turn);
<<<<<<< HEAD
    if (digitalRead(EncoderButton)) {
        encoderReset(chainEncoder);
=======
    if (!digitalRead(EncoderButton)) {
        resetChainLift();
>>>>>>> bec0f3a53dd4e37d8654f19b5ab1b7dfa94db9ad
    }

    if (!getAutoBuildRunning()
#if DEBUG
        && !getDebugTaskRunning()
#endif
    ) {
      if (getRaiseLift()) {
        incrementLift();
      } else if (getLowerLift()) {
        decrementLift();
      }

      if (getToggleClaw()) {
        toggleClawOpen(true);
      }

      if (getRaiseClaw()) {
        incrementVertibar();
      } else if (getLowerClaw()) {
        decrementVertibar();
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

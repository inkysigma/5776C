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
#include "configuration/pid/lift.h"
#include "configuration/robot.h"
#include "configuration/sensors.h"
#include "core/controls.h"
#include "core/motors.h"
#include "core/robot.h"
#include "core/sensors.h"
#include "debug/pot.h"
#include "main.h"
#include "ops/build_stack.h"
#include "ops/motor_ops.h"
// #include "pid/lift_pid.h"
// #include "pid/pidlib.h"

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
TaskHandle jinx;
TaskHandle debug;
void operatorControl() {
  printf("This code is working\n");
  int cone_counter = 0;
  // pid leftConfig, rightConfig;
  /**setLiftPidConfig(&leftConfig, &rightConfig);
  initPid(&leftConfig, LEFT_KP, LEFT_KI, LEFT_KD, LEFT_DT, &getLeftPot);
  initPid(&rightConfig, RIGHT_KP, RIGHT_KI, RIGHT_KD, RIGHT_DT, &getRightPot);**/

  // jinx = taskCreate(JINXRun, TASK_DEFAULT_STACK_SIZE, NULL,
  //                    (TASK_PRIORITY_DEFAULT));
  // debug = taskCreate(writePots, TASK_MINIMAL_STACK_SIZE * 4, NULL,
  //                 TASK_PRIORITY_DEFAULT);
  // startLeftPid();
  // startRightPid();
  bool liftMoving = false;
  int timeSinceMoving = 0;
  while (true) {
    // drive code
    moveDrive(getJoystickRight(), getJoystickLeft());

    // lift control with 5U/D
    if (getRaiseLift()) {
      /**if (!liftMoving) {
        stopLeftPid();
        stopRightPid();
      }
      liftMoving = true;
      timeSinceMoving = 0;*/
      moveLift(100);
    } else if (getLowerLift()) {
      /**if (!liftMoving) {
        stopLeftPid();
        stopRightPid();
      }
      liftMoving = true;
      timeSinceMoving = 0;**/
      moveLift(-100);
  } else {
      moveLift(0);
  }/**else if (liftMoving && timeSinceMoving > 400) {
      setLiftTargets(getLeftPot(), getRightPot());
      startLeftPid();
      startRightPid();
      liftMoving = false;
  }**/ /**else {
        applyStall();
    }**/

    if (liftMoving) {
      timeSinceMoving += 60;
    }

    // Btn6U/D should be assigned to switch lift and functionality
    if (getRaiseClaw()) {
      raiseClaw(127);
    } else if (getLowerClaw()) {
      lowerClaw(127);
    } else {
      raiseClaw(0);
    }

    if (getOpenClaw()) {
      openClawFully();
    }

    else if (getCloseClaw()) {
      closeClawFully();
    }

    if (getOpenGoal()) {
      moveGoal(70);
    }

    else if (getRetractGoal()) {
      moveGoal(-127);
    }

    else {
      moveGoal(0);
    }

    // Btn8U/D should be used for buildStack control
    /**if (getBuildStack()) {
      buildStack(cone_counter);
      cone_counter = cone_counter + 1;
    } else if (getDecreaseStack()) {
      if (cone_counter > 0) {
        cone_counter = cone_counter - 1;
      }
    } else if (getResetStack()) {
      cone_counter = 0;
  }**/

    delay(60);
  }
}

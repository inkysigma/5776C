#include "configuration/robot.h"
#if MODE == 1
#include "main.h"
#include "core/motors.h"
#include "core/controls.h"

void operatorControl() {
  printf("WARNING-TESTING MOTOR FUNCTIONALITY\r\n");
  while (true) {
    int turn = (getJoystickLeftTurn() + getJoystickRightTurn()) / 2.5;
    moveDrive(getJoystickLeft() + turn, getJoystickRight() - turn);
    if (getRaiseLift()) {
      moveLift(100);
    } else if (getLowerLift()) {
      moveLift(-100);
    } else {
      moveLift(0);
    }

    if (getRaiseClaw()) {
      raiseSwitchLift(100);
    } else if (getLowerClaw()) {
      lowerSwitchLift(100);
    } else {
      lowerSwitchLift(0);
    }

    if (getOpenGoal()) {
      moveGoal(100);
    } else if (getRetractGoal()) {
      moveGoal(-100);
    } else {
      moveGoal(0);
    }
    delay(50);
  }
}

#endif

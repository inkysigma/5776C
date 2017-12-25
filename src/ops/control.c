#include "ops/motors.h"

int claw_state = 0;
bool mobile_goal_state = false;

void toggleClaw() {
  switch (claw_state) {
    case 0:
      openClawFully();
      claw_state = 1;
      break;
    case 1:
      closeClawFully();
      claw_state = 0;
      break;
  }
}

void toggleGoal() {
    if (!mobile_goal_state)
        openGoal();
    else
        retractGoal();
    mobile_goal_state = !mobile_goal_state;
}

void resetClawState() {
  claw_state = 0;
}

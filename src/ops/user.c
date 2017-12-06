#include "ops/user.h"
#include "core/robot.h"
#if DEBUG
#include "JINX.h"
#endif
#include "auto/build.h"
#include "configuration/led.h"
#include "pid/pidlib.h"
#include "util/concurrency.h"
#include "util/math.h"

TaskHandle goal;
pid goalPid;
bool goalRunning = true;
bool expand = true;

int getMobileGoal() { return getMobileGoalPot(); }

void initGoal(float kp, float ki, float kd, float dt) {
  initPid(&goalPid, kp, ki, kd, dt, &getMobileGoal);
  setBounds(&goalPid, -40, 40, -50, 50, 10, -10);
}

void openGoal(void *args) {
  goalRunning = true;
  expand = false;
  setTarget(&goalPid, 1100);
  executeUntil(
      {
        moveGoal(pidStep(&goalPid, true));
        updateValue("mobile_output", pidStep(&goalPid, true));
      },
      !withinf(getMobileGoalPot(), 1100, 10), 3000);
  moveGoal(0);
  taskDelete(NULL);
}

void retractGoal(void *args) {
  goalRunning = true;
  expand = true;
  setTarget(&goalPid, 15);
  executeUntil({ moveGoal(pidStep(&goalPid, true)); },
               !withinf(getMobileGoalPot(), 14, 8) && getMobileGoalPot() > 11,
               2000);
  moveGoal(0);
  taskDelete(NULL);
}

void toggleGoal() {
  writeJINXMessage("toggling goal");
  if (goalRunning && taskGetState(goal) == TASK_SUSPENDED &&
      taskGetState(goal) == TASK_RUNNING) {
    taskDelete(goal);
  }
  if (expand) {
    writeJINXMessage("opening");
    goal = taskCreate(openGoal, TASK_DEFAULT_STACK_SIZE, NULL,
                      TASK_PRIORITY_DEFAULT);
  } else {
    goal = taskCreate(retractGoal, TASK_DEFAULT_STACK_SIZE, NULL,
                      TASK_PRIORITY_DEFAULT);
  }
}

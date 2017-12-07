
/**
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
bool goalRunning = false;
bool expand = true;
int prev = 0;

int getMobileGoal() { return getMobileGoalPot(); }

void initGoal(float kp, float ki, float kd, float dt) {
  initPid(&goalPid, kp, ki, kd, dt, &getMobileGoal);
  setBounds(&goalPid, -40, 40, -50, 50, 10, -10);
}

int getSpeed(int dt) { return (getMobileGoal() - prev) / dt; }

void openGoal(void *args) {
  goalRunning = true;
  expand = false;
  setTarget(&goalPid, 1316);
  executeUntil(
      {
        float total = pidStep(&goalPid, false);
        // moveGoal(total);
        updateValue("mobile_output", total);
        updateValue("mobile_target", goalPid.target);
        updateValue("mobile_current", getMobileGoalPot());
      },
      !withinf(getMobileGoalPot(), 1316, 10) || getSpeed(5) < 5, 2000);
  goalRunning = false;
  moveGoal(0);
  taskDelete(NULL);
}

void retractGoal(void *args) {
  goalRunning = true;
  expand = true;
  setTarget(&goalPid, 15);
  executeUntil(
      {
        float total = pidStep(&goalPid, false);
        // moveGoal(total);
        updateValue("mobile_output", total);
      },
      !withinf(getMobileGoalPot(), 14, 8) || getSpeed(5) < 5, 2000);
  moveGoal(0);
  goalRunning = false;
  taskDelete(NULL);
}

void toggleGoal() {
  writeJINXMessage("toggling goal");
  updateValue("something", taskGetCount());
  if (goalRunning) {
    taskSuspend(goal);
    taskDelete(goal);
  }
  if (expand) {
    writeJINXMessage("opening");
    goal = taskCreate(openGoal, TASK_DEFAULT_STACK_SIZE, NULL,
                      TASK_PRIORITY_DEFAULT);
  } else {
    writeJINXMessage("retracting");
    goal = taskCreate(retractGoal, TASK_DEFAULT_STACK_SIZE, NULL,
                      TASK_PRIORITY_DEFAULT);
  }
}
**/

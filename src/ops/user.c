#include "ops/user.h"
#include "core/robot.h"
#if DEBUG
#include "JINX.h"
#endif
#include "auto/build.h"
#include "configuration/led.h"
#include "util/concurrency.h"
#include "util/math.h"

TaskHandle open;
TaskHandle close;
bool goalRunning = true;
bool expand = true;

void openGoal(void *args) {
  goalRunning = true;
  expand = false;
  executeUntil({ moveGoal(100); },
               !withinf(getMobileGoalPot(), 1179, 50) &&
                   getMobileGoalPot() < 1000,
               2000);
  executeUntil({
    moveGoal((1179 - getMobileGoalPot()) * 0.6);
  }, !withinf(getMobileGoalPot(), 1179, 10) && getMobileGoalPot() < 1179, 2000);
	moveGoal(0);
  taskDelete(NULL);
}

void retractGoal(void *args) {
  goalRunning = true;
  expand = true;
  executeUntil({
    moveGoal(-100);
  }, !withinf(getMobileGoalPot(), 50, 10) && getMobileGoalPot() > 50, 2000);
  executeUntil( {
    moveGoal(-(getMobileGoalPot() - 11) * 0.6);
  }, !withinf(getMobileGoalPot(), 14, 30) && getMobileGoalPot() > 11, 2000);
	moveGoal(0);
  taskDelete(NULL);
}

void toggleGoal() {
  if (expand) {
    open = taskCreate(openGoal, TASK_DEFAULT_STACK_SIZE, NULL,
                      TASK_PRIORITY_DEFAULT);
  } else {
    close = taskCreate(retractGoal, TASK_DEFAULT_STACK_SIZE, NULL,
                       TASK_PRIORITY_DEFAULT);
  }
}

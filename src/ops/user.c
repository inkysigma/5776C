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

void flashLed(void *args) {
  while (true) {
    int cones = getConeCount();
    for (int i = 0; i < cones; i++) {
      delay(200);
      digitalWrite(GREEN_LED, 0);
      digitalWrite(RED_LED, 0);
      delay(200);
      digitalWrite(GREEN_LED, 1);
      digitalWrite(RED_LED, 1);
    }
    delay(2000);
  }
}

void openGoal(void *args) {
  executeUntil({ moveGoal(100); },
               !withinf(getMobileGoalPot(), 1370, 50) &&
                   getMobileGoalPot() < 1400,
               2000);
  executeUntil({
    moveGoal((1385 - getMobileGoalPot()) * 0.6);
  }, !withinf(getMobileGoalPot(), 1445, 10) && getMobileGoalPot() < 1460, 2000);
	moveGoal(0);
  taskDelete(NULL);
}

void retractGoal(void *args) {
  executeUntil({
    moveGoal(-100);
  }, !withinf(getMobileGoalPot(), 300, 10) && getMobileGoalPot() > 230, 2000);
  executeUntil( {
    moveGoal(-(getMobileGoalPot() - 250) * 0.6);
  }, !withinf(getMobileGoalPot(), 270, 30) && getMobileGoalPot() > 230, 2000);
	moveGoal(0);
  taskDelete(NULL);
}

bool expand = true;
void toggleGoal() {
  if (expand) {
    goalRunning = true;
    open = taskCreate(openGoal, TASK_DEFAULT_STACK_SIZE, NULL,
                      TASK_PRIORITY_DEFAULT);
    expand = false;
  } else {
    goalRunning = true;
    close = taskCreate(retractGoal, TASK_DEFAULT_STACK_SIZE, NULL,
                       TASK_PRIORITY_DEFAULT);
    expand = true;
  }
}

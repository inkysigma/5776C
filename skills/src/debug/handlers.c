#include "configuration/robot.h"
#if DEBUG
#include "JINX.h"
#include "configuration/sensors.h"
#include "core/sensors.h"
#include "main.h"
#include "pid/left.h"
#include "pid/mobile.h"
#include "pid/right.h"
#include "core/motors.h"

bool taskRunning = false;
bool autonomous_running = false;
TaskHandle autonomousTask;

void autonomousRun(void *args) {
  autonomous();
  autonomous_running = false;
}

void parseMessage(JINX *inStr) {
  taskRunning = true;
  getToken(inStr, 0);
  if (strcmp(inStr->token, "calibrate") == 0) {
    analogCalibrate(MOBILE_GOAL_POT);
    resetLeftDriveEncoder();
    resetRightDriveEncoder();
  } else if (strcmp(inStr->token, "auto") == 0) {
    autonomous_running = true;
    autonomousTask = taskCreate(&autonomousRun, TASK_DEFAULT_STACK_SIZE, NULL,
                               TASK_PRIORITY_DEFAULT);
  } else if (strcmp(inStr->token, "stop") == 0) {
    autonomous_running = false;
    taskDelete(autonomousTask);
    moveDrive(0, 0);
    openMobileGoal(0);
  }

  if (autonomous_running)
    return;
  taskRunning = false;
}

bool getTaskRunning() { return taskRunning; }

#endif

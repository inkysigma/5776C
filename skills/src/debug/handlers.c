#include "configuration/robot.h"
#if DEBUG
#include "JINX.h"
#include "configuration/sensors.h"
#include "main.h"
#include "pid/left.h"
#include "pid/right.h"
#include "pid/mobile.h"

bool taskRunning = false;

bool autonStarted = false;
TaskHandle autoTaskHandle;

void autotask(void *args) { autonStarted = false; }

void parseMessage(JINX *inStr) {
  taskRunning = true;
  getToken(inStr, 0);
  if (strcmp(inStr->token, "calibrate") == 0) {
    analogCalibrate(MOBILE_GOAL_POT);
  } else if (strcmp(inStr->token, "auto") == 0) {
    autonomous();
  } else if (strcmp(inStr->token, "stop_pid") == 0) {
    stopMobileGoalDriveFeedback();
  } else if (strcmp(inStr->token, "stop") == 0) {
    autonStarted = false;
    taskDelete(autoTaskHandle);
  } else if (strcmp(inStr->token, "opcontrol") == 0) {
    autonStarted = false;
  } else if (strcmp(inStr->token, "right") == 0) {
    getToken(inStr, 1);
    int right = atoi(inStr->token);
    setRightDriveGoal(right);
    while (!isRightConfident()) {
      updateRightDriveCompletion();
    }
  }

  if (!autonStarted)
    taskRunning = false;
}

bool getTaskRunning() { return taskRunning; }

#endif

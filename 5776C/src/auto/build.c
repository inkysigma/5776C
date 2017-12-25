#include "auto/build.h"
#include "core/robot.h"
#include "ops/motors.h"
#include "pid/lift.h"
#include "pid/vertibar.h"
#include "util/concurrency.h"
#include "util/jinx.h"
#include "JINX.h"

bool getConfirmed = true;
bool autoBuildRunning = false;
int cone_count = 0;

const int lift[12] = {1760, 1880, 1778, 1872, 1484,
                      1976, 2175, 2084, 2284, 2300};

const int vertbarHigh[12] = {-1107, -1200, -1080, -1120, -912,
                             -1058, -1043, -1002, -1060, -1020};

const int intraDelay[12] = {0, 0, 0, 0, 0, 0, 0, 800, 900, 1000, 1000, 1000};

int liftHeight;
int vert;
int delayTime;
bool partial;

TaskHandle buildStackH;

void buildStackHelper(void *config) {
  autoBuildRunning = true;
  writeJINXMessage("entering build stack");
  if (!partial) {
    resetClaw();
    delay(200);
  }
  setLiftTarget(liftHeight);
  delay(delayTime);
  setClaw(vert);
  openClawFully();
  delay(300);
  writeJINXMessage("resetting build");
  autoBuildRunning = false;
  if (!partial) {
    resetClaw();
  } else {
    setLiftTarget(1530);
    setVertibarTarget(-42);
  }
  stopClaw();
  resetClawState();
  taskDelete(NULL);
}

void buildStack(int cone_level) {
  writeJINXMessage("build stack called");
  liftHeight = lift[cone_level];
  vert = vertbarHigh[cone_level];
  delayTime = intraDelay[cone_level];
  partial = false;
  buildStackH = taskCreate(buildStackHelper, TASK_DEFAULT_STACK_SIZE, NULL,
                           TASK_PRIORITY_DEFAULT);
}

void buildPartialStack(int cone_level) {
  if (taskGetState(buildStackH) == TASK_SUSPENDED ||
      taskGetState(buildStackH) == TASK_SLEEPING) {
    taskSuspend(buildStackH);
    taskDelete(buildStackH);
  }
  disableConfirm();
  liftHeight = lift[cone_level];
  vert = vertbarHigh[cone_level];
  delayTime = intraDelay[cone_level];
  partial = true;
  buildStackH = taskCreate(buildStackHelper, TASK_DEFAULT_STACK_SIZE, NULL,
                           TASK_PRIORITY_DEFAULT);
}

bool getAutoBuildRunning() {
  return autoBuildRunning;
}

void stopStack() {
  autoBuildRunning = false;
  taskSuspend(buildStackH);
  taskDelete(buildStackH);
}

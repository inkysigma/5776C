#include "auto/build.h"
#include "core/robot.h"
#include "ops/motors.h"
#include "pid/lift.h"
#include "pid/vertibar.h"
#include "util/concurrency.h"
#include "util/jinx.h"

bool getConfirmed = true;
bool autoBuildRunning = false;
int cone_count = 0;

const int lift[12] = {1660, 1700, 1824, 1530, 1580,
                      1900, 2170, 2427, 2270, 2450};

const int vertbarHigh[12] = {-655, -665, -732, -560, -502,
                             -650, -595, -550, -605, -615};

const int intraDelay[12] = {0, 0, 0, 0, 0, 0, 0, 800, 900, 1000, 1000, 1100};

int liftHeight;
int vert;
int delayTime;
bool partial;

TaskHandle buildStackH;

void buildStackHelper(void *config) {
  autoBuildRunning = true;
  if (!partial) {
    resetClaw();
    delay(200);
  }
  setLiftTarget(liftHeight);
  delay(delayTime);
  setClaw(vert);

  openClawFully();
  delay(300);
  incrementVertibar();
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
  if (taskGetState(buildStackH) == TASK_SUSPENDED ||
      taskGetState(buildStackH) == TASK_SLEEPING) {
    taskSuspend(buildStackH);
    taskDelete(buildStackH);
  }
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

void stopStack() {
  autoBuildRunning = false;
  taskSuspend(buildStackH);
  taskDelete(buildStackH);
}

#include "auto/build.h"
#include "core/robot.h"
#include "ops/motors.h"
#include "pid/lift.h"
#include "pid/vertibar.h"
#include "util/concurrency.h"
#include "util/jinx.h"

bool getConfirmed = true;

const int lift[12] = {1660, 1700, 1824, 1530, 1580,
                      1900, 2170, 2427, 2270, 2450};

const int vertbarHigh[12] = {-655, -665, -732, -560, -502,
                             -650, -595, -550, -605, -615};

const int intraDelay[12] = {0, 0, 0, 0, 0, 0, 0, 800, 900, 1000, 1000, 1100};

typedef struct {
  int lift;
  int vert;
  int delay;
  bool partial;
} StackConfig;

StackConfig stackConfig;

TaskHandle buildStackH;

bool autoBuildRunning = false;

void buildStackHelper(void *config) {
  autoBuildRunning = true;
  if (!stackConfig.partial) {
    resetClaw();
    delay(200);
  }
  setLiftTarget(stackConfig.lift);
  delay(stackConfig.delay);
  setClaw(stackConfig.vert);

  openClawFully();
  delay(300);
  incrementVertibar();
  autoBuildRunning = false;
  if (!stackConfig.partial) {
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
  stackConfig.lift = lift[cone_level];
  stackConfig.vert = vertbarHigh[cone_level];
  stackConfig.delay = intraDelay[cone_level];
  stackConfig.partial = false;
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
  stackConfig.lift = lift[cone_level];
  stackConfig.vert = vertbarHigh[cone_level];
  stackConfig.delay = intraDelay[cone_level];
  stackConfig.partial = true;
  buildStackH = taskCreate(buildStackHelper, TASK_DEFAULT_STACK_SIZE, NULL,
                           TASK_PRIORITY_DEFAULT);
}

int cone_count = 0;
void incrementConeCount() { cone_count++; }

void decrementConeCount() { cone_count--; }

void resetConeCount() { cone_count = 0; }

int getConeCount() { return cone_count; }

void stopStack() {
  autoBuildRunning = false;
  taskSuspend(buildStackH);
  taskDelete(buildStackH);
}

int getAutoBuildRunning() { return autoBuildRunning; }

void enableConfirm() {
  getConfirmed = true;
}

void disableConfirm() {
  getConfirmed = false;
}

bool getConfirm() {
  return getConfirmed;
}

#include "auto/build.h"
#include "core/robot.h"
#if DEBUG
#include "JINX.h"
#endif
#include "ops/motors.h"
#include "pid/vertibar.h"
#include "pid/lift.h"
#include "util/concurrency.h"
#include "util/jinx.h"

const int lift[12] = {1660, 1700, 1824, 1530, 1580,
                      1900, 2170, 2427, 2270, 2450};

const int vertbarHigh[12] = {-670, -665, -732, -560, -427,
                             -650, -609, -550, -605, -615};

const int intraDelay[12] = {0, 0, 0, 0, 0, 0, 0, 800, 900, 1000, 1100, 1200};

typedef struct {
  int lift;
  int vert;
  int delay;
} StackConfig;

StackConfig stackConfig;

TaskHandle buildStackH;

bool autoBuildRunning = false;

void buildStackHelper(void *config) {
  autoBuildRunning = true;
  resetClaw();
  delay(200);
  setLiftTarget(stackConfig.lift);
  delay(stackConfig.delay);
  raiseClaw(stackConfig.vert);
  incrementVertibar();
  openClawFully();
  delay(200);
  autoBuildRunning = false;
  resetClaw();
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
  buildStackH = taskCreate(buildStackHelper, TASK_DEFAULT_STACK_SIZE, NULL,
                           TASK_PRIORITY_HIGHEST - 2);
}

void buildPartialStack(int cone_level) {
  stackConfig.lift = lift[cone_level];
  stackConfig.vert = vertbarHigh[cone_level];
  stackConfig.delay = intraDelay[cone_level];
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
  writeJINXMessage("Cancelled build");
}

int getAutoBuildRunning() { return autoBuildRunning; }

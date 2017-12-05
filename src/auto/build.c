#include "auto/build.h"
#include "core/robot.h"
#if DEBUG
#include "JINX.h"
#endif
#include "pid/lift.h"
#include "ops/motors.h"
#include "util/concurrency.h"
#include "util/jinx.h"

int lift[12] = {1600, 1660, 1774, 1530, 1530, 1900, 1987, 2127, 2250, 2350};

int liftLower[12] = {1600, 1660, 1774, 1530, 1530, 1900, 1520, 1520};

int vertbarHigh[12] = {-740, -700, -772, -630, -580,
                       -730, -1504, -730, -730, -745};

typedef struct {
  int lift;
  int lift_lower;
  int vert;
} StackConfig;

StackConfig stackConfig;

TaskHandle buildStackH;

bool autoBuildRunning = false;

void buildStackHelper(void *config) {
  updateValue("autoBuildRunning", autoBuildRunning);
  autoBuildRunning = true;
  resetClaw();
  delay(400);
  setLiftTarget(stackConfig.lift);
  executeUntil({}, !withinf(getLiftPot(), stackConfig.lift, 5), 1000);
  delay(500);
  raiseClaw(stackConfig.vert);
  openClawFully();
  delay(1000);
  resetClaw();
  stopClaw();
  autoBuildRunning = false;
  resetClawState();
}

void buildStack(int cone_level) {
  stackConfig.lift = lift[cone_level];
  stackConfig.lift_lower = liftLower[cone_level];
  stackConfig.vert = vertbarHigh[cone_level];
  buildStackH = taskCreate(buildStackHelper, TASK_DEFAULT_STACK_SIZE, NULL,
                           TASK_PRIORITY_HIGHEST - 2);
}

void buildPartialStack(int cone_level) {
  stackConfig.lift = lift[cone_level];
  stackConfig.lift_lower = liftLower[cone_level];
  stackConfig.vert = vertbarHigh[cone_level];
  buildStackH = taskCreate(buildStackHelper, TASK_DEFAULT_STACK_SIZE, NULL,
                           TASK_PRIORITY_HIGHEST - 1);
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

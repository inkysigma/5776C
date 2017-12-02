#include "auto/build.h"
#include "core/robot.h"
#if DEBUG
#include "JINX.h"
#endif
#include "pid/lift.h"
#include "ops/motors.h"
#include "util/concurrency.h"
#include "util/jinx.h"

int lift[12] = {1520, 1520, 1570, 212, 222, 386, 484, 509, 573, 686};

int liftLower[12] = {1520, 1520, 1520, 1520, 1520, 1520, 1520, 1520};

int vertbarHigh[12] = {-950, -950, -950, -950, 3225,
                       3230, 3225, 3220, 3210, 3205};

typedef struct {
  int lift;
  int lift_lower;
  int vert;
} StackConfig;

StackConfig stackConfig;

TaskHandle buildStackH;

bool autoBuildRunning = false;

void buildStackHelper(void *config) {
  autoBuildRunning = true;
  resetClaw();
  closeClawFully(true);
  delay(400);
  setLiftTarget(stackConfig.lift);
  raiseClaw(stackConfig.vert);

  // lowerLiftTo(stackConfig.lift_lower);
  openClawFully();
  setLiftTarget(stackConfig.lift);
  autoBuildRunning = false;
}

void buildStack(int cone_level) {
  stackConfig.lift = lift[cone_level];
  stackConfig.lift_lower = liftLower[cone_level];
  stackConfig.vert = vertbarHigh[cone_level];
  buildStackH = taskCreate(buildStackHelper, TASK_DEFAULT_STACK_SIZE, NULL,
                           TASK_PRIORITY_HIGHEST - 1);
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

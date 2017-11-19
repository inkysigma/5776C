#include "auto/build.h"
#include "JINX.h"
#include "ops/auto_ops.h"
#include "ops/motor_ops.h"
#include "util/concurrency.h"
#include "util/jinx.h"

int left[12] = {0, 0, 140, 212, 222, 386, 484, 509, 573, 686};

int right[12] = {0, 0, 140, 212, 222, 515, 505, 622, 751, 800};

int leftLower[12] = {0, 0, 20, 20, 100, 300, 400, 480, 540, 640};

int rightLower[12] = {0, 0, 20, 20, 100, 260, 425, 600, 520, 870};

int vertbarHigh[12] = {3450, 3500, 3445, 3240, 3225, 3230, 3225, 3220, 3210, 3205};

typedef struct {
  int left;
  int right;
  int left_lower;
  int right_lower;
  int vert;
} StackConfig;

StackConfig stackConfig;

TaskHandle buildStackH;

bool autoBuildRunning = false;

void buildStackHelper(void *config) {
  bool full_lower = true;
  if (config != NULL)
    full_lower = *((bool *)config);
  autoBuildRunning = true;
  closeClawFully(true);
  raiseClawPartial(true);
  raiseLift(stackConfig.left, stackConfig.right, true);
  raiseClawPid(stackConfig.vert);
  lowerLiftTo(stackConfig.left_lower, stackConfig.right_lower);
  openClawFully();
  raiseLift(stackConfig.left, stackConfig.right, true);
  lowerClawPartial();
  autoBuildRunning = false;
  if (full_lower) {
    lowerLift();
    lowerClawPid(1750);
  } else {
    lowerLiftTo(126, 126);
    lowerClaw(1750);
  }
}

void buildStack(int cone_level) {
  stackConfig.left = left[cone_level];
  stackConfig.right = right[cone_level];
  stackConfig.left_lower = leftLower[cone_level];
  stackConfig.right_lower = rightLower[cone_level];
  stackConfig.vert = vertbarHigh[cone_level];
  buildStackH = taskCreate(buildStackHelper, TASK_DEFAULT_STACK_SIZE, NULL,
                           TASK_PRIORITY_HIGHEST - 1);
}

void buildPartialStack(int cone_level) {
  stackConfig.left = left[cone_level];
  stackConfig.right = right[cone_level];
  stackConfig.left_lower = leftLower[cone_level];
  stackConfig.right_lower = rightLower[cone_level];
  stackConfig.vert = vertbarHigh[cone_level];
  buildStackH = taskCreate(buildStackHelper, TASK_DEFAULT_STACK_SIZE, NULL,
                           TASK_PRIORITY_HIGHEST - 1);
}

int cone_count = 0;
void incrementConeCount() {
  cone_count++;
}

void decrementConeCount() {
  cone_count--;
}

void resetConeCount() {
  cone_count = 0;
}

int getConeCount() {
  return cone_count;
}

void stopStack() {
  autoBuildRunning = false;
  writeJINXMessage("stopping stack building");
  taskSuspend(buildStackH);
  taskDelete(buildStackH);
  writeJINXMessage("stopped build stack");
}

int getAutoBuildRunning() { return autoBuildRunning; }

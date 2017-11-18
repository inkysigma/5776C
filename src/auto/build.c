#include "auto/build.h"
#include "JINX.h"
#include "ops/motor_ops.h"
#include "util/concurrency.h"
#include "util/jinx.h"

int left[12] = {0, 0, 120, 120, 190, 386, 484, 509, 573, 686};

int right[12] = {0, 0, 120, 120, 222, 515, 505, 622, 751, 800};

int leftLower[12] = {0, 0, 20, 20, 100, 300, 400, 480, 540, 640};

int rightLower[12] = {0, 0, 20, 20, 100, 260, 425, 600, 520, 870};

int vertbarHigh[12] = {3330, 3330, 3310, 3230, 3225, 3230, 3220, 3210, 3210, 3205};

struct StackConfig {
  int left;
  int right;
  int left_lower;
  int right_lower;
  int vert;
};

struct StackConfig stackConfig;

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
  raiseClaw(stackConfig.vert);
  delay(200);
  lowerLiftTo(stackConfig.left_lower, stackConfig.right_lower);
  openClawFully();
  raiseLift(stackConfig.left, stackConfig.right, false);
  lowerClawPartial();
  lowerClaw(1750);
  if (full_lower) {
    lowerLift();
    moveLift(-127);
    delay(400);
    moveLift(0);
  } else {
    lowerLiftTo(126, 126);
  }
  autoBuildRunning = false;
  taskDelete(NULL);
}

void buildStack(int cone_level) {
  stackConfig.left = left[cone_level];
  stackConfig.right = right[cone_level];
  stackConfig.left_lower = leftLower[cone_level];
  stackConfig.right_lower = rightLower[cone_level];
  stackConfig.vert = vertbarHigh[cone_level];
  buildStackH = taskCreate(buildStackHelper, TASK_DEFAULT_STACK_SIZE, NULL,
                           TASK_PRIORITY_HIGH);
}

void buildPartialStack(int cone_level) {
  stackConfig.left = left[cone_level];
  stackConfig.right = right[cone_level];
  stackConfig.left_lower = leftLower[cone_level];
  stackConfig.right_lower = rightLower[cone_level];
  stackConfig.vert = vertbarHigh[cone_level];
  buildStackH = taskCreate(buildStackHelper, TASK_DEFAULT_STACK_SIZE, NULL,
                           TASK_PRIORITY_HIGH);
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

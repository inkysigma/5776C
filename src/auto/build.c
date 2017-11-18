#include "JINX.h"
#include "auto/build.h"
#include "ops/motor_ops.h"
#include "util/jinx.h"

int left[12] = {0, 0, 60, 120, 170, 436, 570, 717, 0, 0};

int right[12] = {0, 0, 60, 120, 202, 565, 700, 911, 0, 0};

int leftLower [12] = {0, 0, 0, 20, 70, 300, 350, 650};

int rightLower [12] = {0, 0, 0, 20, 70, 260, 450, 800};

struct StackConfig {
  int left;
  int right;
  int left_lower;
  int right_lower;
};

struct StackConfig stackConfig;

TaskHandle buildStackH;

bool autoBuildRunning = false;

void buildStackHelper(void* config) {
  autoBuildRunning = true;
  int left = stackConfig.left;
  int right = stackConfig.right;
  int left_lower = stackConfig.left_lower;
  int right_lower = stackConfig.right_lower;
  updateValue("left_height", left);
  updateValue("right_height", right);
  closeClawFully(true);
  raiseClawPartial(true);
  raiseLift(left, right, true);
  raiseClaw();
  delay(300);
  lowerLiftTo(left_lower, right_lower);
  openClawFully();
  moveLift(100);
  delay(400);
  moveLift(40);
  lowerClawPartial();
  lowerLift();
  lowerClaw();
  moveLift(-127);
  delay(350);
  moveLift(0);
  autoBuildRunning = false;
}

void buildStack(int cone_level) {
  buildStackH = taskCreate(buildStackHelper, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
}

void stopStack() {
  autoBuildRunning = false;

  taskSuspend(buildStackH);
  taskDelete(buildStackH);
}

int getAutoBuildRunning() {
  return autoBuildRunning;
}

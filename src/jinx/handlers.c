#include "JINX.h"
#include "auto/build.h"
#include "ops/motors.h"
#include "ops/user.h"
#include "pid/lift.h"

bool taskRunning = false;

bool getDebugTaskRunning() { return taskRunning; }

void parseMessage(JINX *inStr) {
  taskRunning = true;
  getToken(inStr, 0);
  if (strcmp(inStr->token, "set_target") == 0) {
    getToken(inStr, 1);
    int pos = atoi(inStr->token);
    raiseClaw(pos);
  } else if (strcmp(inStr->token, "set_lift") == 0) {
    getToken(inStr, 1);
    int left = atoi(inStr->token);
    getToken(inStr, 2);
    int right = atoi(inStr->token);
    setLiftTarget(left, right);
  } else if (strcmp(inStr->token, "build") == 0) {
    getToken(inStr, 1);
    buildStack(atoi(inStr->token));
    executeUntil({ delay(100); }, getAutoBuildRunning(), 4000);
  } else if (strcmp(inStr->token, "tog_goal") == 0) {
    writeJINXMessage("toggle goal received");
    toggleGoal();
  }
  taskRunning = false;
}

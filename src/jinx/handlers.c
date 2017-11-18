#include "JINX.h"
#include "auto/build.h"
#include "ops/motor_ops.h"
#include "ops/userops.h"

bool taskRunning = false;

bool getDebugTaskRunning() { return taskRunning; }

void parseMessage(JINX *inStr) {
  taskRunning = true;
  getToken(inStr, 0);
  if (strcmp(inStr->token, "raise") == 0) {
    getToken(inStr, 1);
    int pos = atoi(inStr->token);
    raiseClaw(pos);
  } else if (strcmp(inStr->token, "lower") == 0) {
    getToken(inStr, 2);
    int pos = atoi(inStr->token);
    lowerClaw(pos);
  } else if (strcmp(inStr->token, "lower_lift") == 0) {
    lowerLift();
  } else if (strcmp(inStr->token, "raise_lift") == 0) {
    getToken(inStr, 1);
    int left = atoi(inStr->token);
    getToken(inStr, 2);
    int right = atoi(inStr->token);
    raiseLift(left, right, true);
  } else if (strcmp(inStr->token, "open") == 0) {
    openClawFully();
  } else if (strcmp(inStr->token, "close") == 0) {
    closeClawFully(true);
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

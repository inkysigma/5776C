#include "JINX.h"
#include "auto/build.h"
#include "ops/motor_ops.h"

void parseMessage(JINX *inStr) {
  getToken(inStr, 0);
  if (strcmp(inStr->token, "raise") == 0) {
    raiseClaw();
  }
  else if (strcmp(inStr->token, "lower") == 0) {
    lowerClaw();
  }
  else if (strcmp(inStr->token, "lower_lift") == 0) {
    lowerLift();
  }
  else if (strcmp(inStr->token, "raise_lift") == 0) {
    getToken(inStr, 1);
    int left = atoi(inStr->token);
    getToken(inStr, 2);
    int right = atoi(inStr->token);
    raiseLift(left, right, true);
  }
  else if (strcmp(inStr->token, "open") == 0) {
    openClawFully();
  }
  else if (strcmp(inStr->token, "close") == 0) {
    closeClawFully(true);
  }
  else if (strcmp(inStr->token, "build") == 0) {
    getToken(inStr, 1);
    buildStack(atoi(inStr->token));
  }
}

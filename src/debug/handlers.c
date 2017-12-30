#include "configuration/robot.h"
#if DEBUG
#include "JINX.h"
#include "util/JINX.h"

#include "ops/build.h"
#include "ops/motors.h"
#include "pid/lift.h"
#include "pid/drive.h"
#include "pid/vertibar.h"
#include "main.h"

#include "ops/build.h"

bool taskRunning = false;

void parseMessage(JINX *inStr) {
  taskRunning = true;
  getToken(inStr, 0);

  if (strcmp(inStr->token, "build") == 0) {
    getToken(inStr, 1);
    int size = atoi(inStr->token);
    buildStack(size);
  } else if (strcmp(inStr->token, "auto") == 0) {
    autonomous();
  } else if (strcmp(inStr->token, "resetd") == 0) {
    resetDrive();
  } else if (strcmp(inStr->token, "resetg") == 0) {
    resetGyro();
  } else if (strcmp(inStr->token, "drive") == 0) {
    int left, right;
    getToken(inStr, 1);
    left = atoi(inStr->token);
    getToken(inStr, 2);
    right = atoi(inStr->token);
    setDriveTarget(left, right);
  }

  taskRunning = false;
}
#endif

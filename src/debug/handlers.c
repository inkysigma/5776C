#include "configuration/robot.h"
#if DEBUG
#include "JINX.h"
#include "util/JINX.h"

#include "ops/build.h"
#include "ops/motors.h"
#include "pid/lift.h"
#include "pid/vertibar.h"

#include "ops/build.h"

bool taskRunning = false;

void parseMessage(JINX *inStr) {
  taskRunning = true;
  getToken(inStr, 0);

  if (strcmp(inStr->token, "build") == 0) {
    getToken(inStr, 1);
    int size = atoi(inStr->token);
    buildStack(size);
  }

  taskRunning = false;
}
#endif

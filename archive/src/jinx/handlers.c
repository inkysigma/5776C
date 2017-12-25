#include "core/robot.h"
#if DEBUG
#include "JINX.h"
#include "util/JINX.h"

#include "auto/build.h"
#include "ops/motors.h"
#include "pid/lift.h"
#include "pid/vertibar.h"

bool taskRunning = false;

void parseMessage(JINX *inStr) {
  taskRunning = true;
  getToken(inStr, 0);
  taskRunning = false;
}
#endif

#include "configuration/robot.h"
#if DEBUG
#include "JINX.h"
#include "pid/left.h"
#include "pid/right.h"
#include "configuration/sensors.h"

bool taskRunning = false;

void parseMessage(JINX *inStr) {
  taskRunning = true;
  writeJINXMessage("parsing message");
  getToken(inStr, 0);
  if (strcmp(inStr->token, "calibrate") == 0) {
    analogCalibrate(MOBILE_GOAL_POT);
  }
  taskRunning = false;
}
#endif

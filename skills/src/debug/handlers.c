#include "configuration/robot.h"
#if DEBUG
#include "JINX.h"
#include "configuration/sensors.h"
#include "main.h"
#include "pid/left.h"
#include "pid/right.h"


bool taskRunning = false;

void parseMessage(JINX *inStr) {
  taskRunning = true;
  writeJINXMessage("parsing message");
  getToken(inStr, 0);
  if (strcmp(inStr->token, "calibrate") == 0) {
    analogCalibrate(MOBILE_GOAL_POT);
  }
  if (strcmp(inStr->token, "auto") == 0) {
    autonomous();
  }
  taskRunning = false;
}
#endif

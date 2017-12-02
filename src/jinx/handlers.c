#include "core/robot.h"
#if DEBUG
#include "JINX.h"
#include "util/JINX.h"

#include "auto/build.h"
#include "ops/motors.h"
#include "ops/user.h"
#include "pid/lift.h"
#include "pid/vertibar.h"

bool taskRunning = false;

bool getDebugTaskRunning() { return taskRunning; }

void parseMessage(JINX *inStr) {
  taskRunning = true;
  getToken(inStr, 0);
  if (strcmp(inStr->token, "vertibar") == 0) {
    getToken(inStr, 1);
    int vert = atoi(inStr->token);
    setVertibarTarget(vert);
  } else if (strcmp(inStr->token, "sub") == 0) {
    getToken(inStr, 1);
    int a = atoi(inStr->token);
    getToken(inStr, 2);
    int b = atoi(inStr->token);
    updateValue("sub_test", a - b);
  } else if (strcmp(inStr->token, "lift") == 0) {
    getToken(inStr, 1);
    int lift = atoi(inStr->token);
    setLiftTarget(lift);
  } else if (strcmp(inStr->token, "vres") == 0) {
    stopVertibarPid();
  } else if (strcmp(inStr->token, "sres") == 0) {
    startVertibarPid();
  } else if (strcmp(inStr->token, "build") == 0) {
    getToken(inStr, 1);
    buildStack(atoi(inStr->token));
    executeUntil({ delay(100); }, getAutoBuildRunning(), 4000);
  }
  taskRunning = false;
}
#endif

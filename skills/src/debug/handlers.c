#include "configuration/robot.h"
#if DEBUG
#include "JINX.h"
#include "util/JINX.h"
#include "pid/left.h"

bool taskRunning = false;

void parseMessage(JINX *inStr) {
  taskRunning = true;
  bool running = true;
  getToken(inStr, 0);
  if (strcmp(inStr->token, "left") == 0) {
    resetLeftDriveFeedback();
    setLeftDriveGoal(200);
    while (running) {
      updateLeftDriveCompletion();
      if (isLeftConfident()) running = false;
      delay(40);
    }
  }
  taskRunning = false;
}
#endif

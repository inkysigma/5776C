#include "configuration/robot.h"
#if DEBUG
#include "JINX.h"
#include "util/JINX.h"
#include "pid/left.h"
#include "pid/right.h"

bool taskRunning = false;

void parseMessage(JINX *inStr) {
  taskRunning = true;
  bool running = true;
  getToken(inStr, 0);
  if (strcmp(inStr->token, "right") == 0) {
    resetRightDriveFeedback();
    setRightDriveGoal(200);
    while (running) {
      updateRightDriveCompletion();
      if (isRightConfident()) running = false;
      delay(40);
    }
  }
  taskRunning = false;
}
#endif

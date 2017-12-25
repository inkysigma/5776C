#include "ops/build.h"
#include "configuration/robot.h"
#include "ops/motors.h"
#include "pid/lift.h"
#include "pid/vertibar.h"
#include "util/concurrency.h"
#include "util/jinx.h"
#include "JINX.h"

bool getConfirmed = true;
bool autoBuildRunning = false;
int cone_count = 0;

const int lift[12] = {1610, 1750, 1880, 1890, 1950,
                      2020, 2180, 2190, 2000, 2000};

const int vertbarHigh[12] = {1900, 1960, 2065, 1990, 1983,
                             1950, 1660, 1900, -1060, -1020};

const int liftDelayValues[12] = {1580, 1590, 1780, 1780, 1880, 1900, 2070, 2080};

const int lowerLift[12] = {1520, 1540, 1650, 1680, 1800, 1890, 2040, 2060};

int liftHeight;
int vert;
int liftDelay;
int lowerLiftHeight;
bool partial;

TaskHandle buildStackH;

void buildStackHelper(void *config) {
  autoBuildRunning = true;
  setClaw(3890);
  closeClawFully();
  setLiftTarget(liftHeight);
  executeUntil({}, getVertibarPot() < liftDelay, 3000);
  setClaw(vert);
  delay(200);
  setLift(lowerLiftHeight);
  openClawFully();
  setLift(liftHeight);
  setClaw(3890);
  autoBuildRunning = false;
  writeJINXMessage("exiting jinx");
}

void buildStack(int cone_level) {
  liftHeight = lift[cone_level];
  vert = vertbarHigh[cone_level];
  liftDelay = liftDelayValues[cone_level];
  lowerLiftHeight = lowerLift[cone_level];
  partial = false;
  buildStackH = taskCreate(buildStackHelper, TASK_DEFAULT_STACK_SIZE, NULL,
                           TASK_PRIORITY_DEFAULT);
}

bool getAutoBuildRunning() {
  return autoBuildRunning;
}

void stopStack() {
  autoBuildRunning = false;
  taskSuspend(buildStackH);
  taskDelete(buildStackH);
}

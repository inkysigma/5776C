#include "JINX.h"
#include "configuration/tasks.h"
#include "configuration/motors.h"
#include "core/motors.h"
#include "core/sensors.h"
#include "pid/pidlib.h"

pid *vertibarConfig;
TaskHandle vertibarPid;

bool vertibarRunning = false;
bool vertibarCreated = false;

void setVertTarget(int target) {
  setTarget(vertibarConfig, target);
}

void setVertibarPidConfig(pid* vertibar) {
  vertibarConfig = vertibar;
}

float getVertibarPid() {
  //return pidStep(vertibarConfig);
  return 0;
}

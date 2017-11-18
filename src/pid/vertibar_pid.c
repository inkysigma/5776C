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

void holdVertibar(void *arguments) {
  float total = 0;
  char buffer [20];
  while (vertibarRunning) {
    total = pidStep(vertibarConfig);
    sprintf(buffer, "%f", total);
    writeJINXData("switch_lift", buffer);
    moveSwitchLift(total);
    waitPid(vertibarConfig);
  }
}

float getVertibarPid() {
  return pidStep(vertibarConfig);
}

void startVertibarPid() {
  if (vertibarCreated) {
      if (vertibarRunning) {
        vertibarRunning = true;
        taskResume(vertibarPid);
      }
      return;
  }
  vertibarPid = taskCreate(holdVertibar, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_HIGH);
  vertibarCreated = true;
}

void stopVertibarPid() {
  taskSuspend(vertibarPid);
  vertibarRunning = false;
}

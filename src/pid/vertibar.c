#include "pid/vertibar.h"
#include "core/motors.h"
#include "core/robot.h"
#include "core/sensors.h"
#include "pid/pidlib.h"
#if DEBUG
#include "util/jinx.h"
#endif

pid vertibarPid;
TaskHandle vertibarHandle;

int switchPot() {
  return getChainLift();
}

void initVertibarPid(float kp, float ki, float kd) {
  initPid(&vertibarPid, kp, ki, kd, 40, &switchPot);
}

void setVertibarTarget(float target) {
  resetPid(&vertibarPid);
  setTarget(&vertibarPid, target);
}

void vertibarTarget(void *args) {
  while (true) {
    raiseSwitchLift(pidStep(&vertibarPid));
#if DEBUG
    updateValue("vertibar_lift", pidStep(&vertibarPid));
#endif
    waitPid(&vertibarPid);
  }
}

void startVertibarPid() {
  if (taskGetState(vertibarHandle) == TASK_SUSPENDED) {
    taskResume(vertibarHandle);
    return;
  }
  vertibarHandle = taskCreate(vertibarTarget, TASK_MINIMAL_STACK_SIZE, NULL,
                           TASK_PRIORITY_DEFAULT);
}
void stopVertibarPid() {
  if (taskGetState(vertibarHandle) == TASK_RUNNING)
    taskSuspend(vertibarHandle);
}

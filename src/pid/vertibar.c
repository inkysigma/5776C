#include "pid/vertibar.h"
#include "core/motors.h"
#include "core/robot.h"
#include "core/sensors.h"
#include "pid/pidlib.h"
#if DEBUG
#include "JINX.h"
#include "util/jinx.h"
#endif

pid vertibarPid;
TaskHandle vertibarHandle;

int switchPot() {
  return getChainLift();
}

void initVertibarPid(float kp, float ki, float kd) {
  initPid(&vertibarPid, kp, ki, kd, 120, &switchPot);
}

void setVertibarTarget(float target) {
  setTarget(&vertibarPid, target);
}

void vertibarTarget(void *args) {
    int vertibarPidVal;
  while (true) {
    vertibarPidVal = pidStep(&vertibarPid, true);
    raiseSwitchLift(vertibarPidVal);
#if DEBUG
    updateValue("vert_error", vertibarPid.target - getChainLift());
    updateValue("vert_lift", vertibarPidVal);
#endif
    waitPid(&vertibarPid);
  }
}

void startVertibarPid() {
  if (taskGetState(vertibarHandle) == TASK_SUSPENDED) {
    taskResume(vertibarHandle);
    return;
  }
  vertibarHandle = taskCreate(vertibarTarget, TASK_DEFAULT_STACK_SIZE, NULL,
                           TASK_PRIORITY_DEFAULT);
}
void stopVertibarPid() {
  taskSuspend(vertibarHandle);
}

void resetVertibarPid() {
  setTarget(&vertibarPid, getChainLift());
  resetPid(&vertibarPid);
}

void incrementVertibar() {
  incrementTarget(&vertibarPid, 2);
}

void decrementVertibar() {
  incrementTarget(&vertibarPid, -2);
}

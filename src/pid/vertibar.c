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
  setBounds(&vertibarPid, 20, -20, 110, -110, 10, -10);
  setVertibarTarget(switchPot());
  setTarget(&vertibarPid, switchPot());
}

void setVertibarTarget(float target) {
  setTarget(&vertibarPid, target);
}

void vertibarTarget(void *args) {
  float vertibarPidVal;
  while (true) {
    vertibarPidVal = pidStep(&vertibarPid, false);
    raiseSwitchLift(vertibarPidVal);
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
  resetPid(&vertibarPid);
}

void resetVertibarPid() {
  setTarget(&vertibarPid, 0);
  resetPid(&vertibarPid);
}

void incrementVertibar() {
  incrementTarget(&vertibarPid, 35);
}

void decrementVertibar() {
  incrementTarget(&vertibarPid, -35);
}

int getVertibarTarget() {
  return vertibarPid.target;
}

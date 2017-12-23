#include "pid/vertibar.h"
#include "core/motors.h"
#include "core/robot.h"
#include "core/sensors.h"
#include "pid/pidlib.h"
#if DEBUG
#include "util/jinx.h"
#include "JINX.h"
#endif

pid vertibarPid;
TaskHandle vertibarHandle;

int readVertPot() {
  return getVertibarPot();
}

void initVertibarPid(float kp, float ki, float kd) {
  initPid(&vertibarPid, kp, ki, kd, 50, &readVertPot);
  setBounds(&vertibarPid, 20, -20, 110, -110, 10, -10);
}

void setVertibarTarget(float target) {
  setTarget(&vertibarPid, target);
}

void vertibarTarget(void *args) {
  float vertibarPidVal = 0;
  setExternalControl(&vertibarPid, true);
  while (true) {
    setCurrent(&vertibarPid, readVertPot());
    updateValue("vert_pot_read", readVertPot());
    vertibarPidVal = pidStep(&vertibarPid, false);
    // raiseSwitchLift(vertibarPidVal);
    updateValue("vert_out", vertibarPidVal);
    updateValue("vert_target", vertibarPid.target);
    waitPid(&vertibarPid);
    delay(40);
  }
}

void printFunctionLocation() {
  updateValue("mem_loc", (unsigned int) &readVertPot);
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

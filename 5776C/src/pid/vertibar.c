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

void setVertibarConfig(float kp, float ki, float kd) {
  initPid(&vertibarPid, kp, ki, kd, 20, &readVertPot);
  setBounds(&vertibarPid, 40, -40, 120, -120, 10, -10);
}

void setVertibarTarget(float target) {
  setTarget(&vertibarPid, target);
}

void vertibarTarget(void *args) {
  float vertibarPidVal = 0;
  while (true) {
    vertibarPidVal = pidStep(&vertibarPid, false);
    lowerSwitchLift(vertibarPidVal);
    if (!within(vertibarPid.target, readVertPot(), 400)) {
      vertibarPidVal = sgn(vertibarPid.target - readVertPot()) * 127;
    }
    if (within(vertibarPid.target, readVertPot(), 40))
      vertibarPid.accumulation = 0;
    updateValue("vert_out", vertibarPidVal);
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
  incrementTarget(&vertibarPid, 90);
}

void decrementVertibar() {
  incrementTarget(&vertibarPid, -90);
}

int getVertibarTarget() {
  return vertibarPid.target;
}

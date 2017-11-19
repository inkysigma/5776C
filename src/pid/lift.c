#include "core/motors.h"
#include "core/sensors.h"
#include "configuration/tasks.h"
#include "configuration/motors.h"
#include "pid/pidlib.h"
#include "pid/lift.h"
#if DEBUG
#include "JINX.h"
#include "util/jinx.h"
#endif

bool liftCreated = false;
bool liftRunning = true;
TaskHandle liftPid;

pid lliftConfig;
pid rliftConfig;

// setConfig sets the left and right pid configuration. use initPid(kp, ki, kd,
// dt, sensor) to create a configuration. pass the reference to config.
void setLiftPidConfig(float lkp, float lki, float lkd, float rkp, float rki, float rkd) {
  initPid(&lliftConfig, lkp, lki, lkd, 40, &getLeftPot);
  initPid(&rliftConfig, rkp, rki, rkd, 40, &getRightPot);
}

void setLiftTarget(int left, int right) {
  setTarget(&lliftConfig, left);
  setTarget(&rliftConfig, right);
}

// holdLift holds the lift at a specific position using a PID loop. This should
// target the right side
void holdLift(void *arguments) {
  float ltotal = 0;
  float rtotal = 0;
  while (liftRunning) {
    ltotal = pidStep(&lliftConfig);
    rtotal = pidStep(&rliftConfig);
    #if DEBUG
    updateValue("right_lift_pid", total);
    #endif
    moveLeftLift(ltotal);
    moveRightLift(rtotal);
    waitPid(&lliftConfig);
  }
}

void startLiftPid() {
  if (taskGetState(liftPid) == TASK_SUSPENDED) {
    resetPid(&lliftConfig);
    resetPid(&rliftConfig);
    taskResume(liftPid);
    return;
  }
  liftPid = taskCreate(holdLift, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
}

void incrementLift() {
  incrementTarget(&lliftConfig, 40);
  incrementTarget(&rliftConfig, 40);
}

void decrementLift() {
  incrementTarget(&lliftConfig, -40);
  incrementTarget(&rliftConfig, -40);
}

void stopLiftPid() {
  taskSuspend(liftPid);
}

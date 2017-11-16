#include "JINX.h"
#include "configuration/tasks.h"
#include "core/motors.h"
#include "core/sensors.h"
#include "pid/pidlib.h"

bool lir = false;
bool rir = false;
bool lcreated = false;
bool rcreated = false;
TaskHandle leftLiftPid;
TaskHandle rightLiftPid;

pid *leftConfig;
pid *rightConfig;

// setConfig sets the left and right pid configuration. use initPid(kp, ki, kd,
// dt, sensor) to create a configuration. pass the reference to config.
void setLiftPidConfig(pid *left, pid *right) {
  leftConfig = left;
  rightConfig = right;
}

void setLiftTargets(int left, int right) {
	setTarget(leftConfig, left);
  setTarget(rightConfig, right);
}

// holdLift holds the lift at a specific position using a PID loop. This should
// target the right side
void holdLeftLift(void *arguments) {
  float total = 0;
  while (lir) {
    setTarget(leftConfig, getRightPot());
    total = pidStep(leftConfig);
    moveLeftLift(total);
    waitPid(leftConfig);
  }
}

// holdRightLift should target some given target.
void holdRightLift(void *arguments) {
  float total = 0;
  while (rir) {
    total = pidStep(rightConfig);
    moveRightLift(total);
    waitPid(rightConfig);
  }
}

void startRightPid() {
  resetPid(rightConfig);
  setTarget(rightConfig, getRightPot());
  rir = true;
  if (!rcreated) {
    rightLiftPid = taskCreate(holdRightLift, TASK_DEFAULT_STACK_SIZE, NULL,
                              TASK_PRIORITY_MED);
    rcreated = true;
  } else {
    taskResume(rightLiftPid);
  }
}

void startLeftPid() {
  if (lir) {
    return;
  }
  resetPid(leftConfig);
  lir = true;
  if (!lcreated) {
    leftLiftPid = taskCreate(holdLeftLift, TASK_DEFAULT_STACK_SIZE, leftConfig,
                             TASK_PRIORITY_HIGH);
  } else {
    taskResume(leftLiftPid);
  }
}

void stopRightPid() {
  if (!rir) {
    return;
  }
  rir = false;
  taskSuspend(rightLiftPid);
}

void stopLeftPid() {
  if (!lir) {
    return;
  }
  lir = false;
  taskSuspend(leftLiftPid);
}

#include "JINX.h"
#include "configuration/tasks.h"
#include "core/motors.h"
#include "core/sensors.h"
#include "pid/pidlib.h"

bool lir = false;
bool rir = false;
bool rcreated = false;
bool lcreated = false;
TaskHandle leftLiftPid;
TaskHandle rightLiftPid;

pid *leftConfig;
pid *rightConfig;

// setConfig sets the left and right pid configuration. use initPid(kp, ki, kd,
// dt, sensor)
// to create a configuration. pass the reference to config.
void setLiftPidConfig(pid *left, pid *right) {
  leftConfig = left;
  rightConfig = right;
}

void setRightLiftTarget(int target) { setTarget(rightConfig, target); }

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
  resetPid(leftConfig);
  setTarget(leftConfig, getLeftPot());
	if (lir) {
		return;
	}
  lir = true;
  if (!lcreated) {
    leftLiftPid = taskCreate(holdLeftLift, TASK_DEFAULT_STACK_SIZE, NULL,
                             TASK_PRIORITY_HIGH);
    lcreated = true;
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
  lir = false;
  taskSuspend(leftLiftPid);
}

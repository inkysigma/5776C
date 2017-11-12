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
// dt, sensor)
// to create a configuration. pass the reference to config.
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
  char buffer[20];
  sprintf(buffer, "%f", leftConfig->kp);
  writeJINXData("lpid_kp", buffer);
  while (lir) {
    total = pidStep(leftConfig);
    moveLeftLift(total);
    sprintf(buffer, "%f", total);
    writeJINXData("lpid", buffer);
    waitPid(leftConfig);
    sprintf(buffer, "%f", leftConfig->target - leftConfig->func());
    writeJINXData("lpid_error", buffer);
  }
}

// holdRightLift should target some given target. Once the user moves up or
// down, this task should stop. Once movement stops,
// this ought to start running
void holdRightLift(void *arguments) {
  float total = 0;
  char buffer[20];
  while (rir) {
    total = pidStep(rightConfig);
    moveRightLift(total);
    sprintf(buffer, "%f", total);
    writeJINXData("rpid", buffer);
    waitPid(rightConfig);
  }
}

void startRightPid() {
    writeJINXMessage("PID is running");
    if (rir) {
        return;
    }
  resetPid(rightConfig);
  rir = true;
  if (!rcreated) {
    rightLiftPid = taskCreate(holdRightLift, TASK_DEFAULT_STACK_SIZE,
                              rightConfig, TASK_PRIORITY_HIGH);
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

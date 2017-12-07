#include "core/motors.h"
#include "core/sensors.h"
#include "core/robot.h"
#include "configuration/tasks.h"
#include "configuration/motors.h"
#include "configuration/pid/lift.h"
#include "pid/pidlib.h"
#include "pid/lift.h"

bool liftCreated = false;
bool liftRunning = true;
TaskHandle liftPid;

pid liftConfig;


int liftPot() {
  return getLiftPot();
}

// setConfig sets the left and right pid configuration. use initPid(kp, ki, kd,
// dt, sensor) to create a configuration. pass the reference to config.
void setLiftPidConfig(float kp, float ki, float kd) {
  initPid(&liftConfig, kp, ki, kd, 80, &liftPot);
  setBounds(&liftConfig, 7, -7, 120, -120, 5, -5);
  setMinimumOutput(&liftConfig, 25);
}


void setLiftTarget(int target) {
  if (target > 2760) {
    setTarget(&liftConfig, 2760);
  } else if (target < LIFT_MIN) {
    setTarget(&liftConfig, LIFT_MIN);
  } else {
    setTarget(&liftConfig, target);
  }
}

// holdLift holds the lift at a specific position using a PID loop. This should
// target the right side
void holdLift(void *arguments) {
  float total = 0;
  while (liftRunning) {
    total = pidStep(&liftConfig, false);
    moveLift(total);
    waitPid(&liftConfig);
  }
}

void startLiftPid() {
  if (taskGetState(liftPid) == TASK_SUSPENDED) {
    resetPid(&liftConfig);
    taskResume(liftPid);
    return;
  }
  liftPid = taskCreate(holdLift, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
}

void incrementLift() {
  if (liftConfig.target + 20 > 2760) {
    setTarget(&liftConfig, 2760);
  } else {
    incrementTarget(&liftConfig, 40);
  }
}

void decrementLift() {
  if (liftConfig.target - 20 < LIFT_MIN) {
    setTarget(&liftConfig, LIFT_MIN);
  } else {
    incrementTarget(&liftConfig, -40);
  }
}

void stopLiftPid() {
  taskSuspend(liftPid);
}

#include "core/motors.h"
#include "core/sensors.h"
#include "core/robot.h"
#include "configuration/tasks.h"
#include "configuration/motors.h"
#include "configuration/pid/lift.h"
#include "pid/pidlib.h"
#include "pid/lift.h"
#if DEBUG
#include "JINX.h"
#include "util/jinx.h"
#endif

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
  setBounds(&liftConfig, 40, -40, 120, -120, 10, -10);
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
  updateValue("lift_target", liftConfig.target);
}

// holdLift holds the lift at a specific position using a PID loop. This should
// target the right side
void holdLift(void *arguments) {
  float total = 0;
  while (liftRunning) {
    total = pidStep(&liftConfig, false);
    #if DEBUG
    updateValue("lift_output", total);
    #endif
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

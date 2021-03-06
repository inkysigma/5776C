#include "core/motors.h"
#include "core/sensors.h"
#include "configuration/robot.h"
#include "configuration/motors.h"
#include "configuration/pid/lift.h"
#include "pid/pidlib.h"
#include "pid/lift.h"
#if DEBUG
#include "util/jinx.h"
#endif

bool liftRunning = true;
TaskHandle liftPid;

pid liftConfig;


int liftPot() {
  return getLiftPot();
}

// setConfig sets the left and right pid configuration. use initPid(kp, ki, kd,
// dt, sensor) to create a configuration. pass the reference to config.
void setLiftPidConfig(float kp, float ki, float kd) {
  initPid(&liftConfig, kp, ki, kd, 30, &liftPot);
  setBounds(&liftConfig, 110, -110, 30, -30, 12, -12);
}


void setLiftTarget(int target) {
  setTarget(&liftConfig, target);
}

// holdLift holds the lift at a specific position using a PID loop. This should
// target the right side
void holdLift(void *arguments) {
  float total = 0;
  while (true) {
    total = pidStep(&liftConfig, false);
    if (within(liftConfig.target, liftPot(), 10))
      liftConfig.accumulation = 0;
    if (liftPot() < 1430 && total < -60) {
      total = -60;
    }
    moveLift(total);
    updateValue("lift_out", total);
    waitPid(&liftConfig);
  }
}

void startLiftPid() {
  if (taskGetState(liftPid) != TASK_DEAD && taskGetState(liftPid) == TASK_SUSPENDED) {
    resetPid(&liftConfig);
    taskResume(liftPid);
    return;
  }
  liftPid = taskCreate(holdLift, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
}

void incrementLift() {
  if (liftConfig.target + 100 > 2500) {
    setTarget(&liftConfig, 2500);
  } else {
    incrementTarget(&liftConfig, 70);
  }
}

void decrementLift() {
  if (liftConfig.target - 100 < LIFT_MIN) {
    setTarget(&liftConfig, LIFT_MIN);
  } else {
    incrementTarget(&liftConfig, -70);
  }
}

void stopLiftPid() {
  taskSuspend(liftPid);
}

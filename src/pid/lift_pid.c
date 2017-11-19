#include "JINX.h"
#include "configuration/tasks.h"
#include "configuration/motors.h"
#include "core/motors.h"
#include "core/sensors.h"
#include "util/jinx.h"
#include "pid/pidlib.h"

bool liftCreated = false;
bool liftRunning = true;
TaskHandle liftPid;

pid* liftConfig;

// setConfig sets the left and right pid configuration. use initPid(kp, ki, kd,
// dt, sensor) to create a configuration. pass the reference to config.
void setLiftPidConfig(pid *lift) {
  liftConfig = lift;
}

void setLiftTarget(int target) {
  setTarget(liftConfig, target);
}

// holdLift holds the lift at a specific position using a PID loop. This should
// target the right side
void holdLift(void *arguments) {
  float total = 0;
  while (liftRunning) {
    total = pidStep(liftConfig);
    updateValue("lift_pid", total);
    updateValue("lift_kp", liftConfig->kp);
    moveLift(total);
    delay(40);
  }
}

void startLiftPid() {
  updateValue("kp_start", liftConfig->kp);
  if (taskGetState(liftPid) == TASK_SUSPENDED) {
    resetPid(liftConfig);
    taskResume(liftPid);
    return;
  }
  liftPid = taskCreate(holdLift, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
}

void stopLiftPid() {
  taskSuspend(liftPid);
}

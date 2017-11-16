#include "JINX.h"
#include "configuration/tasks.h"
#include "configuration/motors.h"
#include "core/motors.h"
#include "core/sensors.h"
#include "pid/pidlib.h"

bool liftCreated = false;
bool liftRunning = true;
TaskHandle liftPid;

pid *leftConfig;
pid *rightConfig;

// setConfig sets the left and right pid configuration. use initPid(kp, ki, kd,
// dt, sensor) to create a configuration. pass the reference to config.
void setLiftPidConfig(pid *left, pid *right) {
  leftConfig = left;
  rightConfig = right;
}

void setLiftTargets(int target) {
  setTarget(leftConfig, target);
	setTarget(rightConfig, target);
}

// holdLift holds the lift at a specific position using a PID loop. This should
// target the right side
void holdLeftLift(void *arguments) {
  float total = 0;
  char buffer [20];
  while (liftRunning) {
    total = pidStep(leftConfig);
    moveLeftLift(total);
    sprintf(buffer, "%f", total);
    writeJINXData("left_lift", buffer);
    total = pidStep(rightConfig);
    sprintf(buffer, "%f", total);
    writeJINXData("right_lift", buffer);
    moveRightLift(total);
    waitPid(leftConfig);
  }
}

void startLiftPid() {
  if (liftCreated) {
      if (liftRunning) {
        liftRunning = true;
        taskResume(liftPid);
      }
      return;
  }
  liftPid = taskCreate(holdLeftLift, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_HIGH);
  liftCreated = true;
}

void stopLiftPid() {
  taskSuspend(liftPid);
  liftRunning = false;
}

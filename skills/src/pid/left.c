#include "pid/left.h"
#include "core/motors.h"
#include "core/sensors.h"
#include "fbc.h"
#include "fbc_pid.h"
#include "JINX.h"

fbc_t leftDriveControl;
fbc_pid_t leftDrivePid;
bool leftRunning = false;
TaskHandle leftTask;

void initLeftDriveFeedback(float kp, float ki, float kd, float min_i,
                           float max_i) {
  fbcPIDInitializeData(&leftDrivePid, kp, ki, kd, min_i, max_i);
  fbcInit(&leftDriveControl, &setLeftDrive, &getLeftDrive, &resetLeftDrive,
          &fbcStallDetect, -127, 127, 20, 3);
  fbcPIDInit(&leftDriveControl, &leftDrivePid);
}

void setLeftDriveGoal(float target) { fbcSetGoal(&leftDriveControl, target); }

void resetLeftDriveFeedback() { fbcReset(&leftDriveControl); }

void updateLeftDriveCompletion() { fbcRunContinuous(&leftDriveControl); }

void startLeftDriveFeedback() {
  leftRunning = true;

  if (taskGetState(leftTask) == TASK_SUSPENDED) {
    taskResume(leftTask);
    return;
  }
  if (taskGetState(leftTask) == TASK_RUNNING) {
    taskDelete(leftTask);
  }
  writeJINXMessage("creating left drive");
  leftTask = fbcRunParallel(&leftDriveControl);
}

void stopLeftDriveFeedback() {
  leftRunning = false;
  taskSuspend(leftTask);
  taskDelete(leftTask);
}

bool isLeftConfident() {
  return fbcIsConfident(&leftDriveControl);
}

bool isLeftRunning() {
  return leftRunning;
}

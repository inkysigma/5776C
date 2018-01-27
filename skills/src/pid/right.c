#include "pid/right.h"
#include "fbc.h"
#include "fbc_pid.h"
#include "core/sensors.h"
#include "core/motors.h"

fbc_t rightDriveControl;
fbc_pid_t rightDrivePid;
TaskHandle rightTask;
bool rightRunning;

void initRightDriveFeedback(float kp, float ki, float kd, float min_i,
                            float max_i) {
  fbcPIDInitializeData(&rightDrivePid, kp, ki, kd, min_i, max_i);
  fbcInit(&rightDriveControl, &setRightDrive, &getRightDrive, &resetRightDrive,
          NULL, -120, 120, 5, 3);
  fbcPIDInit(&rightDriveControl, &rightDrivePid);
}

void setRightDriveGoal(float target) { fbcSetGoal(&rightDriveControl, target); }
void resetRightDriveFeedback() { fbcReset(&rightDriveControl); }
void updateRightDriveCompletion() { fbcRunContinuous(&rightDriveControl); }

void runRightDrive(void* args) {
  while (rightRunning) {
    if (isRightConfident()) fbcReset(&rightDriveControl);
    fbcRunContinuous(&rightDriveControl);
  }
}

void startRightDriveFeedback() {
  rightRunning = true;
  if (taskGetState(rightTask) == TASK_SUSPENDED) {
    taskResume(rightTask);
    return;
  }
  if (taskGetState(rightTask) == TASK_RUNNING) {
    return;
  }
  rightTask = taskCreate(&runRightDrive, TASK_DEFAULT_STACK_SIZE,
    NULL, TASK_PRIORITY_DEFAULT);
}

void stopRightDriveFeedback() {
  rightRunning = false;
  taskSuspend(rightTask);
  taskDelete(rightTask);
}

bool isRightConfident() { return fbcIsConfident(&rightDriveControl); }
bool isRightRunning() { return rightRunning; }

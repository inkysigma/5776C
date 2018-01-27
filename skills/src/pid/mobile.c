#include "core/motors.h"
#include "core/sensors.h"
#include "fbc.h"
#include "fbc_pid.h"
#include "pid/mobile.h"

fbc_t mobileGoalControl;
fbc_pid_t mobileGoalPid;
TaskHandle mobileGoalTask;
bool mobileRunning = false;

void initMobileGoalFeedback(float kp, float ki, float kd, float min_i,
                            float max_i) {
  fbcPIDInitializeData(&mobileGoalPid, kp, ki, kd, min_i, max_i);
  fbcInit(&mobileGoalControl, &setMobileGoal, &getMobileGoal, NULL, NULL, -127,
          127, 20, 3);
}


void setMobileGoalDriveGoal(float target) { fbcSetGoal(&mobileGoalControl, target); }

void resetMobileGoalDriveFeedback() { fbcReset(&mobileGoalControl); }

void updateMobileGoalDriveCompletion() { fbcRunContinuous(&mobileGoalControl); }

void runMobileGoalDrive(void* args) {
  while (mobileRunning) {
    if (isMobileGoalConfident()) fbcReset(&mobileGoalControl);
    fbcRunContinuous(&mobileGoalControl);
  }
}

void startMobileGoalDriveFeedback() {
  mobileRunning = true;
  if (taskGetState(mobileGoalTask) == TASK_SUSPENDED) {
    taskResume(mobileGoalTask);
    return;
  }
  if (taskGetState(mobileGoalTask) == TASK_RUNNING) {
    return;
  }
  mobileGoalTask = taskCreate(&runMobileGoalDrive, TASK_DEFAULT_STACK_SIZE,
    NULL, TASK_PRIORITY_DEFAULT);
}

void stopMobileGoalDriveFeedback() {
  mobileRunning = false;
  taskSuspend(mobileGoalTask);
  taskDelete(mobileGoalTask);
}

bool isMobileGoalConfident() {
  return fbcIsConfident(&mobileGoalControl);
}

bool isMobileGoalRunning() {
  return mobileRunning;
}

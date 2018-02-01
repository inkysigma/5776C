#include "core/motors.h"
#include "core/sensors.h"
#include "pid/pidlib.h"
#include "pid/mobile.h"
#include "util/math.h"

pid mobileGoalPid;
TaskHandle mobileGoalTask;
bool mobileRunning = false;

void initMobileGoalFeedback(float kp, float ki, float kd, float min_i,
                            float max_i) {
  initPid(&mobileGoalPid, kp, ki, kd, 20, &getMobileGoal);
  setBounds(&mobileGoalPid, max_i, min_i, 120, -120, 50, -50);
}

void setMobileGoalDriveGoal(float target) { setTarget(&mobileGoalPid, target); }

void resetMobileGoalDriveFeedback() { resetPid(&mobileGoalPid); }

void updateMobileGoalDriveCompletion() { openMobileGoal(pidStep(&mobileGoalPid, false)); }

void runMobileGoalDrive(void* args) {
  while (mobileRunning) {
    updateMobileGoalDriveCompletion();
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
  return within(mobileGoalPid.target, readMobileGoalPot(), 10);
}

bool isMobileGoalRunning() {
  return mobileRunning;
}

#include "pid/mobile.h"
#include "core/motors.h"
#include "core/sensors.h"
#include "pid/pidlib.h"
#include "util/jinx.h"
#include "util/math.h"


pid mobileGoalPid;
TaskHandle mobileGoalTask;
bool mobileRunning = false;
int confidence = 0;

void initMobileGoalFeedback(float kp, float ki, float kd, float min_i,
                            float max_i) {
  pidInit(&mobileGoalPid, kp, ki, kd, 20, &getMobileGoal);
  pidBound(&mobileGoalPid, max_i, min_i, 120, -120, 50, -50);
}

void setMobileGoalDriveGoal(float target) { pidTarget(&mobileGoalPid, target); }

void resetMobileGoalDriveFeedback() { pidReset(&mobileGoalPid); }

void updateMobileGoalDriveCompletion() {
  int total = pidStep(&mobileGoalPid, false);
  openMobileGoal(total);
}

void runMobileGoalDrive(void *args) {
  while (mobileRunning) {
    if (within(mobileGoalPid.target, readMobileGoalPot(), 20))
      confidence++;
    updateMobileGoalDriveCompletion();
    pidWait(&mobileGoalPid);
  }
}

void startMobileGoalDriveFeedback() {
  mobileRunning = true;
  if (taskGetState(mobileGoalTask) == TASK_SUSPENDED) {
    taskResume(mobileGoalTask);
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

void pauseMobileGoalDriveFeedback() {
  mobileRunning = false;
  taskSuspend(mobileGoalTask);
}

bool isMobileGoalConfident() {
  return pidConfident(&mobileGoalPid, 6);
}

bool isMobileGoalRunning() { return mobileRunning; }

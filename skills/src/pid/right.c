#include "pid/right.h"
#include "JINX.h"
#include "core/motors.h"
#include "core/sensors.h"
#include "fbc.h"
#include "fbc_pid.h"
#include "pid/pidlib.h"
#include "util/JINX.h"

pid rightDrivePid;
TaskHandle rightTask;
bool rightRunning;
int confidence;

void initRightDriveFeedback(float kp, float ki, float kd, float min_i,
                            float max_i) {
  pidInit(&rightDrivePid, kp, ki, kd, 20, &getRightDrive);
  pidBound(&rightDrivePid, max_i, min_i, 35, -35, -60, 60);
  pidMinimumOutput(&rightDrivePid, 20);
}

void setRightDriveGoal(float target) { pidTarget(&rightDrivePid, target); }

void resetRightDriveFeedback() {
  pidTarget(&rightDrivePid, 0);
  pidReset(&rightDrivePid);
  resetRightDriveEncoder();
}

void updateRightDriveCompletion() {
  int update = pidStep(&rightDrivePid, false);
  moveRightDrive(update);
}

void runRightDrive(void *args) {
  while (rightRunning) {
    updateRightDriveCompletion();
    pidWait(&rightDrivePid);
  }
}

void startRightDriveFeedback() {
  rightRunning = true;
  pidReset(&rightDrivePid);
  if (taskGetState(rightTask) == TASK_SUSPENDED) {
    taskResume(rightTask);
    return;
  }
  rightTask = taskCreate(&runRightDrive, TASK_DEFAULT_STACK_SIZE, NULL,
                         TASK_PRIORITY_DEFAULT);
}

void stopRightDriveFeedback() {
  rightRunning = false;
  taskSuspend(rightTask);
  taskDelete(rightTask);
}

bool isRightConfident() { return pidConfident(&rightDrivePid, 8); }

bool isRightRunning() { return rightRunning; }

float stepRightPid() { return pidStep(&rightDrivePid, false); }

bool isRightWithin(int distance) { return pidWithin(&rightDrivePid, distance); }

void pauseRightDriveFeedback() {
  rightRunning = false;
  taskSuspend(rightTask);
}
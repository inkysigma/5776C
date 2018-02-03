#include "pid/left.h"
#include "JINX.h"
#include "core/motors.h"
#include "core/sensors.h"
#include "fbc.h"
#include "fbc_pid.h"
#include "pid/pidlib.h"

pid leftDrivePid;
bool leftRunning = false;
TaskHandle leftTask;

void initLeftDriveFeedback(float kp, float ki, float kd, float min_i,
                           float max_i) {
  pidInit(&leftDrivePid, kp, ki, kd, 20, &getLeftDrive);
  pidBound(&leftDrivePid, max_i, min_i, 120, -120, -60, 60);
}

void setLeftDriveGoal(float target) { pidTarget(&leftDrivePid, target); }

void resetLeftDriveFeedback() {
  pidReset(&leftDrivePid);
  resetLeftDriveEncoder();
}

void updateLeftDriveCompletion() {
  moveLeftDrive(pidStep(&leftDrivePid, false));
}

void runLeftDrive(void *argument) {
  while (leftRunning) {
    updateLeftDriveCompletion();
    pidWait(&leftDrivePid);
  }
}

void startLeftDriveFeedback() {
  leftRunning = true;

  if (taskGetState(leftTask) == TASK_SUSPENDED) {
    taskResume(leftTask);
    return;
  }
  leftTask = taskCreate(&runLeftDrive, TASK_DEFAULT_STACK_SIZE, NULL,
                        TASK_PRIORITY_DEFAULT);
}

void stopLeftDriveFeedback() {
  leftRunning = false;
  taskSuspend(leftTask);
  taskDelete(leftTask);
}

bool isLeftConfident() { return pidConfident(&leftDrivePid, 5); }

bool isLeftWithin(int distance) { return pidWithin(&leftDrivePid, distance); }

bool isLeftRunning() { return leftRunning; }

float stepLeftPid() { return pidStep(&leftDrivePid, false); }

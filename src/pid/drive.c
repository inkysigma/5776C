#include "pid/drive.h"
#include "core/motors.h"
#include "core/sensors.h"
#include "pid/pidlib.h"
#include "JINX.h"

pid leftPid;
pid rightPid;
TaskHandle driveHandle;

int right() {
  return getRightDrive();
}

int left() {
  return getLeftDrive();
}

void setRightDrivePid(float kp, float ki, float kd, float dt) {
  initPid(&leftPid, kp, ki, kd, dt, &right);
}

void setLeftDrivePid(float kp, float ki, float kd, float dt) {
  initPid(&rightPid, kp, ki, kd, dt, &left);
}

void setDriveTarget(float left, float right) {
  setTarget(&leftPid, left);
  setTarget(&rightPid, right);
}

void drivePid(void *args) {
  float leftTotal;
  float rightTotal;
  while (true) {
    leftTotal = pidStep(&leftPid, true);
    rightTotal = pidStep(&rightPid, true);
    moveDrive(leftTotal, rightTotal);
    writeJINXMessage("driving pid");
    waitPid(&leftPid);
  }
}

void startDrivePid() {
  writeJINXMessage("setting pid target");
  driveHandle = taskCreate(drivePid, TASK_DEFAULT_STACK_SIZE, NULL,
                           TASK_PRIORITY_DEFAULT);
}

void stopDrivePid() {
  if (taskGetState(driveHandle) == TASK_DEAD)
    return;
  taskSuspend(driveHandle);
  taskDelete(driveHandle);
}

void resetDrivePid() {
  resetPid(&leftPid);
  resetPid(&rightPid);
  resetDrive();
}

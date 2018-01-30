#include "pid/right.h"
#include "fbc.h"
#include "fbc_pid.h"
#include "core/sensors.h"
#include "core/motors.h"
#include "JINX.h"

fbc_t rightDriveControl;
fbc_pid_t rightDrivePid;
TaskHandle rightTask;
bool rightRunning;

void initRightDriveFeedback(float kp, float ki, float kd, float min_i,
                            float max_i) {
  fbcPIDInitializeData(&rightDrivePid, kp, ki, kd, min_i, max_i);
  fbcInit(&rightDriveControl, &setDrive, &getRightDrive, &resetRightDrive,
          NULL, -120, 120, 10, 2);
  fbcPIDInit(&rightDriveControl, &rightDrivePid);
}

void setRightDriveGoal(float target) { fbcSetGoal(&rightDriveControl, target); }
void resetRightDriveFeedback() { fbcReset(&rightDriveControl); }
void updateRightDriveCompletion() { fbcRunContinuous(&rightDriveControl); }

void runRightDrive(void* args) {
	unsigned long now = millis();
  while (rightRunning) {
    if (isRightConfident()) fbcReset(&rightDriveControl);
    fbcRunContinuous(&rightDriveControl);
    taskDelayUntil(&now, FBC_LOOP_INTERVAL);
  }
}

void startRightDriveFeedback() {
  rightRunning = true;
  rightTask = fbcRunParallel(&rightDriveControl);
}

void stopRightDriveFeedback() {
  rightRunning = false;
  taskSuspend(rightTask);
  taskDelete(rightTask);
}

bool isRightConfident() { return fbcIsConfident(&rightDriveControl); }
bool isRightRunning() { return rightRunning; }

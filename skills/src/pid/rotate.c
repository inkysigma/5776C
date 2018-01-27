#include "core/motors.h"
#include "core/sensors.h"
#include "fbc.h"
#include "fbc_pid.h"
#include "pid/rotate.h"

fbc_t rotateControl;
fbc_pid_t rotatePid;
TaskHandle rotateTask;
bool rotateRunning;

void initRotateFeedback(float kp, float ki, float kd, float min_i,
                        float max_i) {
  fbcPIDInitializeData(&rotatePid, kp, ki, kd, min_i, max_i);
  fbcInit(&rotateControl, &setRotate, &getGyro, &resetGyro, NULL, -127, 127, 1, 3);
  fbcPIDInit(&rotateControl, &rotatePid);
}

void initRotateDriveFeedback(float kp, float ki, float kd, float min_i,
                            float max_i) {
  fbcPIDInitializeData(&rotatePid, kp, ki, kd, min_i, max_i);
  fbcInit(&rotateControl, &setRotate, &getGyro, &resetGyro,
          NULL, -127, 127, 10, 3);
}

void setRotateDriveGoal(float target) { fbcSetGoal(&rotateControl, target); }
void resetRotateDriveFeedback() { fbcReset(&rotateControl); }
void updateRotateDriveCompletion() { fbcRunContinuous(&rotateControl); }

void runRotateDrive(void* args) {
  while (rotateRunning) {
    fbcRunContinuous(&rotateControl);
  }
}

void startRotateFeedback() {
  rotateRunning = true;
  if (taskGetState(rotateTask) == TASK_SUSPENDED) {
    taskResume(rotateTask);
    return;
  }
  if (taskGetState(rotateTask) == TASK_RUNNING) {
    return;
  }
  rotateTask = taskCreate(&runRotateDrive, TASK_DEFAULT_STACK_SIZE,
    NULL, TASK_PRIORITY_DEFAULT);
}

void stopRotateFeedback() {
  rotateRunning = false;
  taskSuspend(rotateTask);
  taskDelete(rotateTask);
}

bool isRotateConfident() { return fbcIsConfident(&rotateControl); }
bool isRotateRunning() { return rotateRunning; }

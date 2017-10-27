#include "pid/pidlib.h"
#include "core/motors.h"
#include "core/sensors.h"
#include "configuration/tasks.h"

bool lir = false;
bool rir = false;
TaskHandle leftLiftPid;
TaskHandle rightLiftPid;

pid *leftConfig;
pid *rightConfig;

// setConfig sets the left and right pid configuration. use initPid(kp, ki, kd, dt, sensor)
// to create a configuration. pass the reference to config.
void setConfig(pid *left, pid *right) {
	leftConfig = left;
	rightConfig = right;
}

// holdLift holds the lift at a specific position using a PID loop. This should target the right side
void holdLeftLift(void* arguments) {
	float total = 0;
	while (lir) {
		setTarget(leftConfig, getRightPot());
		total = pidStep(leftConfig);
		moveLeftLift(total);
		waitPid(leftConfig);
	}
}

// holdRightLift should target some given target. Once the user moves up or down, this task should stop. Once movement stops,
// this ought to start running
void holdRightLift(void* arguments) {
	float total = 0;
	while (rir) {
		total = pidStep(rightConfig);
		moveRightLift(total);
		waitPid(rightConfig);
	}
}

void startRightPid(int t) {
	resetPid(rightConfig);
	setTarget(rightConfig, t);
	rir = true;
	rightLiftPid = taskCreate(holdRightLift, TASK_MINIMAL_STACK_SIZE * 2, rightConfig, TASK_PRIORITY_MED);
}

void startLeftPid() {
	resetPid(leftConfig);
	lir = true;
  leftLiftPid = taskCreate(holdLeftLift, TASK_MINIMAL_STACK_SIZE * 2,
    leftConfig, TASK_PRIORITY_HIGH);
}

void stopRightPid() {
	rir = false;
  taskSuspend(rightLiftPid);
}

void stopLeftPid() {
	lir = false;
  taskSuspend(leftLiftPid);
}

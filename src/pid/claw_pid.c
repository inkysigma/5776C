#include "pid/pidlib.h"
#include "core/motors.h"
#include "core/sensors.h"
#include "configuration/tasks.h"
#include "JINX.h"

bool cir = false; //claw is running
TaskHandle clawPid;

pid *clawConfig;

// setConfig sets the pid configuration. use initPid(kp, ki, kd, dt, sensor)
// to create a configuration. pass the reference to config.
void setClawPidConfig(pid *value) {
	clawConfig = value;
}

// holdRightLift should target some given target. Once the user moves up or down, this task should stop. Once movement stops,
// this ought to start running
void holdClaw(void* arguments) {
	float total = 0;
	char buffer[20];
	while (cir) {
		total = pidStep(clawConfig);
		raiseClaw(total);
		sprintf(buffer, "%f", total);
		waitPid(clawConfig);
	}
}

void startClawPid(int t) {
	resetPid(clawConfig);
	setTarget(clawConfig, t);
	cir = true;
	clawPid = taskCreate(holdClaw, TASK_MINIMAL_STACK_SIZE * 2, clawConfig, TASK_PRIORITY_MED);
}


void stopClawPid() {
	cir = false;
  taskSuspend(clawPid);
}

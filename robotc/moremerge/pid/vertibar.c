#ifndef PID_VERT_C
#define PID_VERT_C
#ifndef MOTOR_H
#include "../motors.h"
#endif

#define VERT_KP 0.23
#define VERT_KI 0.15
#define VERT_KD 0.012

float vert_target = 0;
float vert_prev_error = 0;
float vert_integral = 0;
float vert_total_cap = 120;
float vert_integral_cap = 40;
float vert_derivative_cap = 12;

bool vert_pid_running = false;

task vertpid()
{
	vert_pid_running = true;
	while (true) {
		float error = SensorValue[vertibar] - vert_target;
		float inte = vert_integral + error * 0.02;
		if (abs(inte) > vert_integral_cap)
			vert_integral = sgn(inte) * vert_integral_cap;
		float derivative = error - vert_prev_error;
		if (abs(derivative) > vert_derivative_cap)
			derivative = sgn(derivative) * vert_derivative_cap;
		int total = error * VERT_KP + vert_integral * VERT_KI + VERT_KD * derivative;
		if (abs(total) > vert_total_cap)
			total = sgn(total) * vert_total_cap;
		moveVertibar(total);
		delay(20);
	}
}

void setVertibarTarget(float t) {
	vert_target = t;
}

void incrementVert() {
	vert_target -= 43;
}

void decrementVert() {
	vert_target += 43;
}

bool getVertibarPidRunning() {
	return vert_pid_running;
}

void stopVertibarPid() {
	vert_pid_running = false;
	stopTask(vertpid);
}

#endif

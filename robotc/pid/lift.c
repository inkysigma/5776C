#ifndef PID_LIFT_C
#define PID_LIFT_C
#ifndef MOTOR_H
#include "../motors.h"
#endif
#include "../util/math.h"

#define LIFT_KP 0.8
#define LIFT_KI 0.4
#define LIFT_KD 0.012

float lift_target = 0;
float lift_prev_error = 0;
float lift_integral = 0;
float lift_total_cap = 120;
float lift_integral_cap = 60;
float lift_derivative_cap = 10;

bool lift_pid_running = false;

task liftpid()
{
	lift_pid_running = true;
	while (true) {
		float error = lift_target - SensorValue[lift];
		float inte = lift_integral + error * 0.02;
		if (abs(inte) > lift_integral_cap)
			lift_integral = sgn(inte) * lift_integral_cap;
		float derivative = error - lift_prev_error;
		if (abs(derivative) > lift_derivative_cap)
			derivative = sgn(derivative) * lift_derivative_cap;
		int total = error * LIFT_KP + lift_integral * LIFT_KI + LIFT_KD * derivative;
		if (abs(total) > lift_total_cap)
			total = sgn(total) * lift_total_cap;
		moveLift(total);
		delay(20);
	}
}

void setLiftTarget(float t) {
	lift_target = t;
}

void incrementLift() {
	if (lift_target + 23 > 2210) {
		lift_target = 2210;
		return;
	}
	lift_target += 23;
}

void incrementLiftBy(int inc) {
	if (lift_target + inc > 2210) {
		lift_target = 2210;
		return;
	}
	lift_target += inc;
}

void resetLiftPid() {
	lift_integral = 0;
	lift_prev_error = 0;
}

void decrementLift() {
	if (lift_target -23 < 1050) {
		lift_target = 1050;
		return;
	}
	lift_target -= 23;
}

bool withinLiftTarget(float margin) {
	return within(lift_target, SensorValue[lift], margin);
}

void stopLiftPid() {
	lift_pid_running = false;
	stopTask(liftpid);
}

bool getLiftPidRunning() {
	return lift_pid_running;
}


#endif

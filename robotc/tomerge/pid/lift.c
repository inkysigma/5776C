#ifndef PID_LIFT_C
#define PID_LIFT_C
#include "../motors.h"

#define LIFT_KP 0.8
#define LIFT_KI 0.2
#define LIFT_KD 0.15

float lift_target = 0;
float lift_prev_error = 0;
float lift_integral = 0;
float lift_total_cap = 120;
float lift_integral_cap = 30;
float lift_derivative_cap = 10;

task liftpid()
{
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

void decrementLift() {
	if (lift_target -23 < 1050) {
		lift_target = 1050;
		return;
	}
	lift_target -= 23;
}


#endif

#ifndef PID_VERT_C
#define PID_VERT_C
#include "../motors.h"

#define VERT_KP 0.35
#define VERT_KI 0.2
#define VERT_KD 0

float vert_target = 0;
float vert_prev_error = 0;
float vert_integral = 0;
float vert_total_cap = 120;
float vert_integral_cap = 20;
float vert_derivative_cap = 10;

task vertpid()
{
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


#endif

#ifndef PID_PIDLIB_H
#define PID_PIDLIB_H
#include "API.h"

typedef struct
{
	// constants used for the pid control
	float kp;
	float kd;
	float ki;

	// bounding the integral
	float min_int;
	float max_int;

	// bounding the total
	float min_total;
	float max_total;

	float max_der;
	float min_der;

	// delta time in milliseconds
	float dt;

	// used for holding state
	float accumulation;
	float prev_error;

	// the sensor the use and the target
	int (*func)();
	float target;
} pid;

// initialize a pid struct to the given values. the integral and total output
// are set by default to 10 and 110 respectively.
void initPid(pid* ref, float kp, float ki, float kd, int dt, int (*sensor)());

// set the max and min values of the integral and total output. this is optional.
void setBounds(pid *ref, int max_int, int min_int, int max_total,
               int min_total, int min_der, int max_der);

// reset the accumulator and previous error of the pid struct. use this to reuse
// a pid after it has been shut off and the target reset
void resetPid(pid *config);

// set the target of a pid. may be used continuously to set the target
void setTarget(pid *config, float target);

// get the pid output after one step. use continuously to power motors
float pidStep(pid *config);

// wait the time required by the pid configuration
void waitPid(pid *config);

void incrementTarget(pid* ref, int inc);

#endif

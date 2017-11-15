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

	// delta time in milliseconds
	float dt;

	// used for holding state
	float accumulation;
	float prev_error;

	// the sensor the use and the target
	int (*func)();
	float target;
} pid;

extern void initPid(pid* ref, float kp, float ki, float kd, int dt, int (*sensor)());
extern void setBounds(pid* ref, int max_int, int min_int, int max_total, int min_total);
extern void resetPid(pid *config);
extern void setTarget(pid *config, float target);
extern float pidStep(pid *config);
extern void waitPid(pid *config);

void incrementTarget(pid* ref, int inc);

#endif

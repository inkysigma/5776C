#ifndef PID_PIDLIB_H
#define PID_PIDLIB_H
#include "API.h"

typedef struct {
  bool digital;
  int port;
} sensor;

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
	sensor * read;
	float target;
} pid;

void loadSensor(sensor* ref, int port, bool digital);
void initPid(pid* ref, float kp, float ki, float kd, int dt, sensor* sensor);
void setBounds(pid* ref, int max_int, int min_int, int max_total, int min_total);
void resetPid(pid *config);
void setTarget(pid *config, float target);
float pidStep(pid *config);
void waitPid(pid *config);

#endif

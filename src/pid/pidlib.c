#include "pid/pidlib.h"

void initPid(pid *ref, float kp, float ki, float kd, int dt, int (*sensor)()) {
  // initialize the pid to some constants. for tSensors sensor, pass in
  // an actual sensor like initPid(kp, ki, kd, dt, in1) or
  // also initPid(kp, ki, kd, dt, LeftLiftPot)

  ref->kp = kp;
  ref->ki = ki;
  ref->kd = kd;
  ref->dt = dt;
  ref->min_int = -30;
  ref->max_int = 30;
  ref->min_total = -110;
  ref->max_total = 110;
  ref->func = sensor;
}

void setBounds(pid *ref, int max_int, int min_int, int max_total, int min_total) {
  ref->max_int = max_int;
  ref->min_int = min_int;
  ref->max_total = max_total;
  ref->min_total = min_total;
}

void incrementTarget(pid* ref, int inc) {
	ref->target += inc;
}

void resetPid(pid *config) {
  // reset the pid accumulator and prev_error
  config->accumulation = 0;
  config->prev_error = 0;
}

void setTarget(pid *config, float target) {
  // set the target of the pid for a given instance
  config->target = target;
}

float pidStep(pid *config) {
  // calculate the value derived by a pid
  float current_pos = config->func();
  float error = config->target - current_pos;
  float integral = config->accumulation + error * config->dt / 1000;
  float derivative = (error - config->prev_error) / (config->dt / 1000);
  config->accumulation = integral;
  float total =
      config->kp * error + config->ki * integral + config->kd * derivative;

  if (integral > config->max_int) {
    integral = config->max_int;
  } else if (integral < config->min_int) {
    integral = config->min_int;
  }

  if (total > config->max_total) {
    total = config->max_total;
  } else if (total < config->min_total) {
    total = config->min_total;
  }
  return total;
}

void waitPid(pid *config) {
  // wait the time of a pid
  delay(config->dt);
}

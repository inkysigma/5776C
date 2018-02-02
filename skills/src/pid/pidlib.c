#include "pid/pidlib.h"
#include "configuration/robot.h"
#include "util/math.h"
#if DEBUG
#include "util/JINX.h"
#endif

void pidInit(pid *ref, float kp, float ki, float kd, int dt, int (*sensor)()) {
  // initialize the pid to some constants. for tSensors sensor, pass in
  // an actual sensor like initPid(kp, ki, kd, dt, in1) or
  // also initPid(kp, ki, kd, dt, LeftLiftPot)
  ref->kp = kp;
  ref->ki = ki;
  ref->kd = kd;
  ref->dt = dt;
  ref->min_output = 0;
  ref->min_int = -20;
  ref->max_int = 20;
  ref->min_total = -110;
  ref->max_total = 110;
  ref->max_der = 10;
  ref->min_der = -10;
  ref->func = sensor;
  ref->externalCurrent = false;
}

void pidBound(pid *ref, int max_total, int min_total, int max_int, int min_int,
              int min_der, int max_der) {
  ref->max_int = max_int;
  ref->min_int = min_int;
  ref->max_total = max_total;
  ref->min_total = min_total;
  ref->min_der = min_der;
  ref->max_der = max_der;
}

void pidMinimumOutput(pid *ref, float min_output) {
  ref->min_output = min_output;
}

void pidIncrementTarget(pid *ref, int inc) { ref->target += inc; }

void pidReset(pid *config) {
  // reset the pid accumulator and prev_error
  config->accumulation = 0;
  config->prev_error = 0;
}

void pidTarget(pid *config, float target) {
  // set the target of the pid for a given instance
  config->target = target;
}

void pidSetExternalControl(pid *config, bool control) {
  config->externalCurrent = control;
}

void pidSetCurrent(pid *config, float current) {
  // set the value of the pid for a given instance
  config->current = current;
}

void pidSetFunction(pid *config, int (*sensor)()) { config->func = sensor; }

float pidStep(pid *config, bool reversed) {
  double current_pos;
  if (!config->externalCurrent)
    current_pos = config->func();
  else
    current_pos = config->current;

  double error;
  if (!reversed)
    error = config->target - current_pos;
  else
    error = current_pos - config->target;

  double integral = config->accumulation + error * config->dt / 1000;
  double derivative = (error - config->prev_error) / config -> dt;

  integral = bound(integral, config->max_int, config->min_int);
  derivative = bound(derivative, config->max_der, config->min_der);

  config->accumulation = integral;
  config->prev_error = error;

  double total =
      config->kp * error + config->ki * integral + config->kd * derivative;

  if (abs(error) <= config->error) {
    config->frames++;
  }

  if (absf(total) < config->min_output) {
    return 0;
  }
  updateValue("total", total);
  return total;
}

void pidWait(pid *config) { delay(config->dt); }

bool pidConfident(pid *config, int frames) { return config->frames >= frames; }

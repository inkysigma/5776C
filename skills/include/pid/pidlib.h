#ifndef PID_PIDLIB_H
#define PID_PIDLIB_H
#include "API.h"

typedef struct {
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

  // creating lowerbound for output
  float min_output;

  float max_der;
  float min_der;

  // delta time in milliseconds
  float dt;

  // used for holding state
  float accumulation;
  float prev_error;

  float error;
  int frames;

  // the sensor the use and the target
  int (*func)();

  bool externalCurrent;
  float target;
  float current;
} pid;

// initialize a pid struct to the given values. the integral and total output
// are set by default to 10 and 110 respectively.
void pidInit(pid *ref, float kp, float ki, float kd, int dt, int (*sensor)());

void pidMinimumOutput(pid *ref, float min_output);

// set the max and min values of the integral and total output. this is
// optional.
void pidBound(pid *ref, int max_int, int min_int, int max_total, int min_total,
              int min_der, int max_der);

// reset the accumulator and previous error of the pid struct. use this to reuse
// a pid after it has been shut off and the target reset
void pidReset(pid *config);

// set whether or not the current value will be set without func (if
// func is null or a pointer cannot be done)
void pidSetExternalControl(pid *config, bool control);

// set the current value of the sensor. use only if you have se external control
// to true. has no effect otherwise
void pidSetCurrent(pid *config, float current);

// set the target of a pid. may be used continuously to set the target
void pidTarget(pid *config, float target);

// get the pid output after one step. use continuously to power motors
float pidStep(pid *config, bool reversed);

// wait the time required by the pid configuration
void pidWait(pid *config);

/**
 * @method pidIncrementTarget(pid* ref, int inc)
 *
 * @brief Increment the target of the pid by a specified value.
 *
 * @param ref a reference to the pid structure
 * @param inc the amount to increment by
 *
 **/
void pidIncrementTarget(pid *ref, int inc);

/**
 * @method pidConfident(int frames)
 *
 * @brief Check if the pid is confident that the target has been reached
 *
 * @param ref a reference to the pid structure
 * @param frames the minimum number of frames necessary to be confident
 *
 **/
bool pidConfident(pid *config, int frames);

bool pidWithin(pid *config, float distance);

#endif

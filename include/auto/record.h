#ifndef AUTO_RECORD_H
#define AUTO_RECORD_H

#include "pid/pidlib.h"

typedef struct {
    pid* configuration;
    int* motorGroup;
    int motor;
} output;

typedef struct {
    int analog_sensor_count;
    int digital_sensor_count;
    output* outputs;
    const char* fname;
    int fnameLength;
} recorder;

void record(recorder* r);
void run(recorder* r);
void configure(int motors, ...);

#endif
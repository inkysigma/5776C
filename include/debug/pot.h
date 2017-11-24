#ifndef DEBUG_POT_H
#define DEBUG_POT_H

#include "core/robot.h"

#if DEBUG
#include "API.h"
#include "core/sensors.h"
#include "JINX.h"

void writePots(void* args);
#endif

#endif

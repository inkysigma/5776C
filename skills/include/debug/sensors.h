#include "configuration/robot.h"
#if DEBUG
#ifndef _DEBUG_POT_H
#define _DEBUG_POT_H

#include "API.h"
#include "JINX.h"
#include "configuration/sensors.h"
#include "core/sensors.h"

/**
 * @method writeSensors(void* args)
 * @brief This is a task that can be started with the PROS API that will write
 *        the values returned by the sensors for JINX. Use the JINX server to
 *        view these values on a computer
 **/
void writeSensors(void* args);

#endif
#endif

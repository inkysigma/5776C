#ifndef UTIL_JINX_H
#define UTIL_JINX_H

#include "API.h"
#include "JINX.h"

/**
* Update a value with JINX. This is usually used to update sensor values or
* values that usually change over time.
**/
void updateValue(const char* name, float value);

/**
* Writes a value with JINX to the console. This is usually used once to ensure
* some values is recorded. Values written like this WILL NOT be graphed.
**/
void writeValue(const char* name, float value);

#endif

#ifndef UTIL_MATH_H
#define UTIL_MATH_H

#include "API.h"

/**
* Returns the sgn of the value as either -1 for negative or 1 or positive
**/
inline int sgn(float value) {
  if (value < 0) {
    return -1;
  }
  return 1;
}

/**
* Returns the absolute value of a float.
**/
inline float absf(float a) {
  return sgn(a) * a;
}

/**
* Checks if the value is within @tolerance amount of the other. This method is
* symmetric (i.e. within(a, b, c) == within(b, a, c))
**/
inline bool within(float a, float b, float tolerance) {
  return absf(a - b) < tolerance;
}

/**
* Returns the maximum of two values
**/
inline int max(int a, int b) {
  return a > b ? a : b;
}

/**
* Returns the minimum of two values
**/
inline int min(int a, int b) {
  return a > b ? b : a;
}

/**
* Bounds a value within a maximum and minimum. If the value exceeds the maximum,
* it returns the maximum. If the value if below the minimum, it returns the
* minimum.
**/
inline float bound(float a, float maximum, float mininimum) {
  return max(min(a, maximum), mininimum);
}

#endif

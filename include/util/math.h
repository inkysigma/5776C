#ifndef UTIL_MATH_H
#define UTIL_MATH_H

#include "API.h"

inline int sgn(float value) {
  if (value < 0) {
    return -1;
  }
  return 1;
}

inline bool within(int a, int b, int tolerance) {
  return abs(a - b) < tolerance;
}

#endif

#ifndef UTIL_MATH_H
#define UTIL_MATH_H

#include "API.h"

inline int sgn(float value) {
  if (value < 0) {
    return -1;
  }
  return 1;
}

inline float absf(float a) {
  return sgn(a) * a;
}

inline bool within(float a, float b, float tolerance) {
  return absf(a - b) < tolerance;
}

inline int max(int a, int b) {
  return a > b ? a : b;
}

inline int min(int a, int b) {
  return a > b ? b : a;
}

inline float bound(float a, float maximum, float mininimum) {
  return max(min(a, maximum), mininimum);
}

#endif

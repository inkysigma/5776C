#ifndef UTIL_MATH_H
#define UTIL_MATH_H

inline int sgn(float value) {
  if (value < 0) {
    return -1;
  }
  return 1;
}

#endif

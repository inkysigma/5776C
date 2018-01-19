#ifndef UTIL_MATH_H
#define UTIL_MATH_H
bool within(float a, float b, float margin) {
	return sgn(a -b) * (a - b) < margin;
}
#endif

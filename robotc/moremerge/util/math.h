#ifndef UTIL_MATH_H
#define UTIL_MATH_H

//THIS ENTIRE FOLDER AND FILE IS FOR THIS ONE FUNCTION BELOW

//calculate within
bool within(float a, float b, float margin) {
	return abs(a - b) < margin;
}
#endif

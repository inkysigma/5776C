#ifndef CORE_SENSORS_H
#define CORE_SENSORS_H

#include "configuration/sensors.h"
#include "API.h"

void setInit(int left, int right);
int getLeftPot();
int getRightPot();



void setMobileGoalInit(int left, int right);
int getLeftMobilePot();
int getRightMobilePot();

inline int getSwitchLiftPot() {
	// return 0;
	return analogReadCalibrated(SwitchLiftPot);
}

void initPrimaryGyro(int port);
int getPrimaryGyro();
void resetPrimaryGyro();

inline int getLeftIme() {
	int pointer = 0;
	imeGet(LeftIME, &pointer);
	return pointer;
}

inline int getRightIme() {
	int pointer = 0;
	imeGet(RightIME, &pointer);
	return pointer;
}

inline void resetIme() {
	imeReset(LeftIME);
	imeReset(RightIME);
}

#endif

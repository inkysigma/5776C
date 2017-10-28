#ifndef CORE_SENSORS_H
#define CORE_SENSORS_H

#include "configuration/sensors.h"
#include "API.h"

extern int leftInit;
extern int rightInit;

inline void setInit(int left, int right) {
	leftInit = left;
	rightInit = right;
}

extern int getLeftPot() {
	return analogReadCalibrated(LeftLiftPot) - leftInit;
}

inline int getRightPot() {
	return analogReadCalibrated(RightLiftPot) - rightInit;
}


extern int mobileGoalLeftInit;
extern int mobileGoalRightInit;

inline void setMobileGoalInit(int left, int right) {
	mobileGoalLeftInit = left;
	mobileGoalRightInit = right;
}

inline int getLeftMobilePot() {
	return analogReadCalibrated(MogoLeftPot)- mobileGoalLeftInit;
}

inline int getRightMobilePot() {
	return analogReadCalibrated(MogoRightPot) - mobileGoalRightInit;
}

inline int getSwitchLiftPot() {
	return analogReadCalibrated(SwitchLiftPot);
}
extern Gyro primaryGyro;

inline void initPrimaryGyro(int port) {
	primaryGyro = gyroInit(port, 0);
}

inline int getPrimaryGyro() {
	return gyroGet(primaryGyro);
}

inline void resetPrimaryGyro() {
	gyroReset(primaryGyro);
}

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

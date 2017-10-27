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

inline int getLeftPot() {
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

#endif

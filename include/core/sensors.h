#ifndef CORE_SENSORS_H
#define CORE_SENSORS_H

#include "configuration/sensors.h"
#include "API.h"

int leftInit = 0;
int rightInit = 0;

void setInit(int left, int right) {
	leftInit = left;
	rightInit = right;
}

int getLeftPot() {
	return analogReadCalibrated(LeftLiftPot) - leftInit;
}

int getRightPot() {
	return analogReadCalibrated(RightLiftPot) - rightInit;
}


int mobileGoalLeftInit = 0;
int mobileGoalRightInit = 0;

void setMobileGoalInit(int left, int right) {
	mobileGoalLeftInit = left;
	mobileGoalRightInit = right;
}

int getLeftMobilePot() {
	return analogReadCalibrated(MogoLeftPot)- mobileGoalLeftInit;
}

int getRightMobilePot() {
	return analogReadCalibrated(MogoRightPot) - mobileGoalRightInit;
}

#endif

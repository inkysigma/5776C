#include "core/sensors.h"

int leftInit = 0;
int rightInit = 0;
int mobileGoalLeftInit = 0;
int mobileGoalRightInit = 0;
Gyro primaryGyro;

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

void initPrimaryGyro(int port) {
	primaryGyro = gyroInit(port, 0);
}

int getPrimaryGyro() {
	return gyroGet(primaryGyro);
}

void resetPrimaryGyro() {
	gyroReset(primaryGyro);
}

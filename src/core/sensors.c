#include "core/sensors.h"

int leftInit = 0;
int rightInit = 0;
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

void initPrimaryGyro(int port) {
	primaryGyro = gyroInit(port, 0);
}

int getPrimaryGyro() {
	return gyroGet(primaryGyro);
}

void resetPrimaryGyro() {
	gyroReset(primaryGyro);
}

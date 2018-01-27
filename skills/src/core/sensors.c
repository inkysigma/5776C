#include "core/sensors.h"

int getLeftDrive() { return readLeftDrive(); }

int getRightDrive() { return readRightDrive(); }

int getMobileGoal() { return readMobileGoalPot(); }

int getGyro() { return readGyro(); }

void resetGyro() { resetMainGyro(); }
void resetDrive() { resetDriveEncoder(); }
void resetLeftDrive() { resetLeftDriveEncoder(); }
void resetRightDrive() { resetRightDriveEncoder(); }

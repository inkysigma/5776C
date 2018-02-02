#include "configuration/robot.h"
#if DEBUG
#include "API.h"
#include "configuration/motors.h"
#include "configuration/sensors.h"
#include "debug/sensors.h"
#include "core/sensors.h"
#include "util/jinx.h"

void writeSensors(void* args) {
  while (true) {
    updateValue("left", readLeftDrive());
    updateValue("right", readRightDrive());
    updateValue("mobile_goal", readMobileGoalPot());
    updateValue("gyro", readGyro());
    delay(600);
  }
}
#endif

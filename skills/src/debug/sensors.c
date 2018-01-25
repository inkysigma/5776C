#include "configuration/robot.h"
#if DEBUG
#include "API.h"
#include "configuration/sensors.h"
#include "core/sensors.h"
#include "debug/sensors.h"
#include "util/jinx.h"

void writeSensors(void* args) {
  while (true) {
    updateValue("lift", getLiftPot());
    updateValue("vertibar", getVertibarPot());
    updateValue("motor", motorGet(5));
    updateValue("ldrive", getLeftDrive());
    updateValue("rdrive", getRightDrive());
    updateValue("rotation", getGyro());
    delay(500);
  }
}
#endif

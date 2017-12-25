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
    delay(1000);
  }
}
#endif

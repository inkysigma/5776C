#include "core/robot.h"
#if DEBUG
#include "API.h"
#include "configuration/sensors.h"
#include "core/sensors.h"
#include "debug/pot.h"
#include "util/jinx.h"

void writePots(void* args) {
  while (true) {
    updateValue("lift", getLiftPot());
    updateValue("vertibar", getVertibarPot());
    updateValue("motor", motorGet(5));
    delay(1000);
  }
}
#endif

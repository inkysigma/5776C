#include "core/robot.h"
#if DEBUG
#include "API.h"
#include "debug/pot.h"
#include "util/jinx.h"
#include "configuration/sensors.h"
#include "pid/pidlib.h"

void writePots(void *args) {
  while (true) {
    updateValue("lift", getLiftPot());
    updateValue("chain", getChainLift());
    delay(700);
  }
}
#endif

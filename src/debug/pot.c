#include "core/robot.h"
#if DEBUG
#include "API.h"
#include "configuration/sensors.h"
#include "debug/pot.h"
#include "pid/pidlib.h"
#include "util/jinx.h"

void writePots(void* args) {
  while (true) {
    updateValue("lift", getLiftPot());
    updateValue("button", digitalRead(3));
    updateValue("chain", getChainLift());
    delay(1000);
  }
}
#endif

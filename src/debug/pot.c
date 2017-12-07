#include "core/robot.h"
#if DEBUG
#include "API.h"
#include "configuration/sensors.h"
#include "debug/pot.h"
#include "pid/pidlib.h"
#include "util/jinx.h"

void writePots() {
  updateValue("lift", getLiftPot());
  updateValue("chain", getChainLift());
}
#endif

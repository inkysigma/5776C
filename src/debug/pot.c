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
    updateValue("chain", getChainLift());
    updateValue("left_d", getLeftDrive());
    updateValue("right_d", getRightDrive());
    delay(1000);
  }
}
#endif

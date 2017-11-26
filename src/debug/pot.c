#include "core/robot.h"
#if DEBUG
#include "debug/pot.h"
#include "util/jinx.h"
#include "configuration/sensors.h"
#include "configuration/motors.h"
#include "pid/pidlib.h"
#include "main.h"

void writePots(void *args) {
  while (true) {
    updateValue("lift", getLiftPot());
    updateValue("chain", getChainLift());
    updateValue("3", analogRead(3));
    updateValue("4", analogRead(4));
    updateValue("mobile", getMobileGoalPot());
    delay(700);
  }
}
#endif

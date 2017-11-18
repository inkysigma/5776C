#include "debug/pot.h"
#include "configuration/motors.h"
#include "pid/pidlib.h"
#include "util/jinx.h"
#include "pid/vertibar.h"

void writePots(void *args) {
  while (true) {
    updateValue("switch", getSwitchLiftPot());
    updateValue("left", getLeftPot());
    updateValue("right", getRightPot());
    updateValue("total", getVertibarPid());
    delay(700);
  }
}

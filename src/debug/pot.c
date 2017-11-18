#include "debug/pot.h"
#include "configuration/motors.h"
#include "pid/pidlib.h"
#include "pid/vertibar.h"
#include "main.h"

char buffer [10];
void writeValue(const char* name, float value) {
  sprintf(buffer, "%f", value);
  writeJINXData(name, buffer);
}

void writePots(void *args) {
  while (true) {
    writeValue("switch", getSwitchLiftPot());
    writeValue("left", getLeftPot());
    writeValue("right", getRightPot());
    writeValue("total", getVertibarPid());
    delay(700);
  }
}

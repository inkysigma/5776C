#include "debug/pot.h"
#include "configuration/motors.h"
#include "pid/pidlib.h"


char buffer[10];
void writeDebugValue(const char *name, float val) {
  sprintf(buffer, "%f", val);
  writeJINXData(name, buffer);
}

void writePots(void *args) {
  while (true) {
    writeDebugValue("switch", getSwitchLiftPot());
    writeDebugValue("left", getLeftPot());
    writeDebugValue("right", getRightPot());
    delay(700);
  }
}

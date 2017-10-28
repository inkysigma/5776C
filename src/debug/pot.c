#include "debug/pot.h"

char buffer[100];

void writeDebugValue(const char* name, float val) {
  sprintf(buffer, "%f", val);
  writeJINXData(name, buffer);
}

void writeAllPots() {
  writeDebugValue("SWITCH_LIFT_POT", getSwitchLiftPot());
  writeDebugValue("LEFT_LIFT_POT", getLeftPot());
  writeDebugValue("RIGHT_LIFT_POT", getRightPot());
}

void writeAllIme() {
}

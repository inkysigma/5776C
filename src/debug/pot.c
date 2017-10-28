#include "debug/pot.h"

char buffer[100];

void writeDebugValue(const char* name, float val) {
  sprintf(buffer, "%f", val);
  writeJINXData(name, buffer);
}

void writePots(void* args) {
    while (true) {
        writeDebugValue("sp", getSwitchLiftPot());
        delay(400);
        writeDebugValue("ll", getLeftPot());
        writeDebugValue("rl", getRightPot());
        delay(400);
    }
}

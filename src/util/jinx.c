#include "util/jinx.h"
#include "JINX.h"

char buffer [20];
void updateValue(const char* name, float value) {
  sprintf(buffer, "%f", value);
  writeJINXData(name, buffer);
}

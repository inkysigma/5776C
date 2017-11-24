#include "core/robot.h"
#if DEBUG
#include "util/jinx.h"
#include "JINX.h"

char buffer [10];
void updateValue(const char* name, float value) {
  sprintf(buffer, "%f", value);
  writeJINXData(name, buffer);
}
#endif

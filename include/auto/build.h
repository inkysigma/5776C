#ifndef AUTO_BUILD_H
#define AUTO_BUILD_H

#include "main.h"
extern bool getConfirmed;
extern int cone_count;
extern bool autoBuildRunning;

void buildStack(int cone_level);
void buildPartialStack(int cone_level);
inline int getConeCount() {
  return cone_count;
}
inline void incrementConeCount() {
  cone_count++;
}
inline void decrementConeCount() {
  cone_count--;
}
inline void resetConeCount() {
  cone_count = 0;
}

inline bool getAutoBuildRunning() {
  return autoBuildRunning;
}

void stopStack();

inline void enableConfirm() {
  getConfirmed = true;
}
inline void disableConfirm() {
  getConfirmed = false;
}
inline bool getConfirm() {
  return getConfirmed;
}

#endif

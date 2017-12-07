#ifndef AUTO_BUILD_H
#define AUTO_BUILD_H

#include "main.h"
extern bool getConfirmed;
void buildStack(int cone_level);
void buildPartialStack(int cone_level);
int getConeCount();
void incrementConeCount();
void decrementConeCount();
void resetConeCount();
int getAutoBuildRunning();
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

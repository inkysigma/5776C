#ifndef AUTO_BUILD_H
#define AUTO_BUILD_H

#include "main.h"

void buildStack(int cone_level);
void buildPartialStack(int cone_level);
int getConeCount();
void incrementConeCount();
void decrementConeCount();
void resetConeCount();
int getAutoBuildRunning();
void stopStack();

void enableConfirm();
void disableConfirm();
bool getConfirm();

#endif

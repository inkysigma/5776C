#ifndef AUTO_BUILD_H
#define AUTO_BUILD_H

void buildStack(int cone_level);
void buildPartialStack(int cone_level);
int getConeCount();
void incrementConeCount();
void decrementConeCount();
void resetConeCount();
int getAutoBuildRunning();
void stopStack();

#endif

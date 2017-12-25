#ifndef PID_VERTIBAR_H
#define PID_VERTIBAR_H

void setVertibarConfig(float kp, float ki, float kd);
void setVertibarTarget(float target);
void startVertibarPid();
void stopVertibarPid();
void resetVertibarPid();
void incrementVertibar();
void decrementVertibar();

#endif

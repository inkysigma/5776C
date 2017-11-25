#ifndef PID_VERTIBAR_H
#define PID_VERTIBAR_H

void initVertibarPid(float kp, float ki, float kd);
void setVertibarTarget(float target);
void startVertibarPid();
void stopVertibarPid();
void resetVertibarPid();

#endif

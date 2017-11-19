#ifndef OPS_AUTO_OPS_H
#define OPS_AUTO_OPS_H
#include "main.h"

void initVertibarPid(float kp, float ki, float kd);
void raiseClawPid(int pos);
void lowerClawPid(int pos);
#endif

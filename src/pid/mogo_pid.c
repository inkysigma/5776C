#include "pid/mogo_pid.h"

pid* leftMogo;
bool leftMogoRunning = false;

void setLeftMogoConfig(pid* config) {
  leftMogo = config;
}

void leftMogoControl(void* args) {
  while (leftMogoRunning) {
    setTarget(leftMogo, getRightMobilePot());
    moveLeftMogo(pidStep(leftMogo));
  }
}

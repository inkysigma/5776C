#include "ops/auto_ops.h"
#include "JINX.h"
#include "core/motors.h"
#include "core/sensors.h"
#include "pid/pidlib.h"
#include "util/concurrency.h"
#include "util/jinx.h"

pid vertibarPid;
void initVertibarPid(float kp, float ki, float kd) {
  initPid(&vertibarPid, kp, ki, kd, 20, &getSwitchLiftPot);
}

void raiseClawPid(int pos) {
  resetPid(&vertibarPid);
  setTarget(&vertibarPid, pos);
  executeUntil(
      {
        float total = -pidStep(&vertibarPid);
        updateValue("vertibar_pid", total);
        moveSwitchLift(total);
      },
      !withinf(getSwitchLiftPot(), pos, 10), 3000);
  raiseSwitchLift(35);
}

void lowerClawPid(int pos) {
  resetPid(&vertibarPid);
  setTarget(&vertibarPid, pos);
  executeUntil({ moveSwitchLift(-pidStep(&vertibarPid)); },
               !withinf(getSwitchLiftPot(), pos, 10), 3000);
  raiseSwitchLift(35);
}

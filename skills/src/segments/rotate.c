#include "core/motors.h"
#include "core/sensors.h"
#include "pid/left.h"
#include "segments.h"


#include "JINX.h"
#include "pid/right.h"
#include "util/concurrency.h"
#include "util/jinx.h"
#include "util/math.h"


void rotateDeposit(bool clockwise) {
  if (clockwise) {
    writeJINXMessage("entered rotate");
    executeUntil(
        {
          moveDrive(180 - readGyro(), -(180 - readGyro()));
          updateValue("gyro_auto", readGyro());
        },
        !within(readGyro(), 180, 5), 1500);
  } else {
    executeUntil({ moveDrive(-(180 + readGyro()), (180 + readGyro())); },
                 !within(readGyro(), 180, 5), 1500);
  }
  moveDrive(127, 127);
  delay(300);
  moveDrive(0, 0);
}
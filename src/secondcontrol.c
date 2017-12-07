#include "auto/build.h"
#include "core/controls.h"
#include "auto/build.h"
#include "secondop.h"

void checkIncrease() {
  if (getIncreaseStack()) {
    if (getConeCount() < 10) {
      incrementConeCount();
      enableConfirm();
    }
    delay(500);
  } else if (getDecreaseStack()) {
    if (getConeCount() > 0) {
      decrementConeCount();
      enableConfirm();
    }
    delay(500);
  } else if (getResetStack()) {
    resetConeCount();
    enableConfirm();
    delay(500);
  }

}

void second(void *args) {
  while (true) {

    checkIncrease();
    if (getBuildPartial()) {
      for (int i = 0; i < 10; i++) {
        buildPartialStack(getConeCount());
        while (getAutoBuildRunning()) {
          delay(800);
        }
        while (!getConfirm()) {
          checkIncrease();
        }
      }
    }
  }
}

#include "auto/build.h"
#include "core/controls.h"
#include "auto/build.h"

void second(void *args) {
  while (true) {

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

    if (getBuildPartial()) {
      for (int i = 0; i < 10; i++) {
        buildPartialStack(getConeCount());
        while (getAutoBuildRunning()) {
          delay(800);
        }
        while (!getConfirm()) {
          if (getIncreaseStack()) {
            if (getConeCount() < 10) {
              incrementConeCount();
              enableConfirm();
            }
            delay(300);
          } else if (getDecreaseStack()) {
            if (getConeCount() > 0) {
              decrementConeCount();
              enableConfirm();
            }
            delay(300);
          } else if (getResetStack()) {
            resetConeCount();
            enableConfirm();
            delay(300);
          }
        }
      }
    }
  }
}

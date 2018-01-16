#include "../motors.h"
void defensive() {
	openClaw(-30);
	moveDrive(110, 115);
	delay(2500);
	moveDrive(0, 0);
}

#include "ops/build_stack.h"
#include "ops/motor_ops.h"
#include "JINX.h"

void buildStack(int current_level) {

}

void buildStackHelper(int right_pot) {
	// start with claw at top and get cone and return to top to dispense
	// // writeJINXSerial("	raising lift {\n");
	raiseLiftTo(right_pot, true);
	// // writeJINXSerial("	}\n");

	// // writeJINXSerial("	lowering claw fully {\n");
	lowerClawPartial(true);
	// writeJINXSerial("	}\n");


	// writeJINXSerial("	lowering the lift to ground state {\n");
	lowerLiftTo(0, false);
	// // writeJINXSerial("	}\n");

	// writeJINXSerial("	lowering claw fully {\n");
	lowerClawFully();
	// // writeJINXSerial("	}\n");

	delay(750);

	// writeJINXSerial("	closing the claw fully {\n");
	closeClawFully();
	// writeJINXSerial("	}\n");

	// extend the claw a bit further so that we don't get caugh
	// writeJINXSerial("	raising the claw partially {\n");
	raiseClawPartial(true);
	// writeJINXSerial("	}\n");

	// swtich the claw back on top
	// writeJINXSerial("	raising the lift back up {");
	raiseLiftTo(right_pot, true);
	// writeJINXSerial("	}\n");

	// writeJINXSerial("	raising claw fully {\n");
	raiseClawFully(true);
	// writeJINXSerial("	}\n");

	// writeJINXSerial("	lowering lift {\n");
	lowerLiftTo(right_pot, true);
	// writeJINXSerial("	}\n");

	delay(400);

	// writeJINXSerial("	releasing cone {\n");
	releaseCone(false);
	// writeJINXSerial("	}\n");
}

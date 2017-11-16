#include "ops/motor_ops.h"
#include "ops/build_stack.h"

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

	// // writeJINXSerial("	lowering claw fully {\n");
	lowerClawPartial();
	// writeJINXSerial("	}\n");


	// writeJINXSerial("	lowering the lift to ground state {\n");
	lowerLiftTo(0);
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
	raiseClawPartial();
	// writeJINXSerial("	}\n");

	// swtich the claw back on top
	// writeJINXSerial("	raising the lift back up {");
	raiseLiftTo(right_pot);
	// writeJINXSerial("	}\n");

	// writeJINXSerial("	raising claw fully {\n");
	raiseClawFully();
	// writeJINXSerial("	}\n");

	// writeJINXSerial("	lowering lift {\n");
	lowerLiftTo(right_pot);
	// writeJINXSerial("	}\n");

	delay(400);

	// writeJINXSerial("	releasing cone {\n");
	releaseCone(false);
	// writeJINXSerial("	}\n");
}

void buildStack(int current_level) {
	// Lowers claw partially 
	lowerClawPartial();
	
	// Lowers lift 
	moveLiftTo(0);

	lowerClawFully();

	delay(750);

	closeClawFully();

	// Raises claw partially
	raiseClawPartial();
	
	// Raises lift to current cone level
	moveLiftTo(current_level);

	// Raise claw fully
	raiseClawFully();

	// Lowers lift
	moveLiftTo(current_level);

	delay(400);

	// Releases cone
	releaseCone(false);
}
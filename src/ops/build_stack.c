#include "ops/build_stack.h"
#include "ops/motor_ops.h"
#include "JINX.h"

void buildStack(int current_level) {

}

void buildStackHelper(int right_pot) {
	// start with claw at top and get cone and return to top to dispense
<<<<<<< HEAD
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
=======
	// printf("	raising lift {\n");
	raiseLiftTo(current_level, true);
	// printf("	}\n");

	// printf("	lowering claw fully {\n");
	lowerClawPartial(true);
	// printf("	}\n");


	// printf("	lowering the lift to ground state {\n");
	lowerLiftTo(0, false);
	// printf("	}\n");

	// printf("	lowering claw fully {\n");
	lowerClawFully();
	// printf("	}\n");

	delay(750);

	// printf("	closing the claw fully {\n");
	closeClawFully();
	// printf("	}\n");

	// extend the claw a bit further so that we don't get caugh
	// printf("	raising the claw partially {\n");
	raiseClawPartial(true);
	// printf("	}\n");

	// swtich the claw back on top
	// printf("	raising the lift back up {");
	raiseLiftTo(current_level, true);
	// printf("	}\n");

	// printf("	raising claw fully {\n");
	raiseClawFully(true);
	// printf("	}\n");

	// printf("	lowering lift {\n");
	lowerLiftTo(current_level, true);
	// printf("	}\n");

	delay(400);

	// printf("	releasing cone {\n");
	releaseCone(false);
	// printf("	}\n");
>>>>>>> ca56013c13a8d9129d5c2eab8e4cd090ff942577
}

#include "ops/build_stack.h"
#include "ops/motor_ops.h"

void buildStack(int current_level) {
	// start with claw at top and get cone and return to top to dispense
	printf("	raising lift {\n");
	raiseLiftTo(current_level, true);
	printf("	}\n");

	printf("	lowering claw fully {\n");
	lowerClawPartial(true);
	printf("	}\n");


	printf("	lowering the lift to ground state {\n");
	lowerLiftTo(0, false);
	printf("	}\n");

	printf("	lowering claw fully {\n");
	lowerClawFully();
	printf("	}\n");

	delay(750);

	printf("	closing the claw fully {\n");
	closeClawFully();
	printf("	}\n");

	// extend the claw a bit further so that we don't get caugh
	printf("	raising the claw partially {\n");
	raiseClawPartial(true);
	printf("	}\n");

	// swtich the claw back on top
	printf("	raising the lift back up {");
	raiseLiftTo(current_level, true);
	printf("	}\n");

	printf("	raising claw fully {\n");
	raiseClawFully(true);
	printf("	}\n");

	printf("	lowering lift {\n");
	lowerLiftTo(current_level, true);
	printf("	}\n");

	delay(400);

	printf("	releasing cone {\n");
	releaseCone(false);
	printf("	}\n");
}

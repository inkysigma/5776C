#include "ops/userops.h"

void openGoal() {
	if (getLeftMobilePot() > 1400) {
		// we need to resist gravity
		moveGoal(-100);
	}
	else if (getLeftMobilePot() > 1000) {
		// switch over to graivty aid
		moveGoal(-80);
	}
	else {
		// we need to slow the acceleration.
		moveGoal(10);
	}
}

void retractGoal() {
	if (getLeftMobilePot() < 1000) {
		// we need to resist gravity
		moveGoal(100);
	}
	else if (getLeftMobilePot() < 1400) {
		// switch over to graivty aid
		moveGoal(70);
	}
	else {
		// we need to slow the acceleration.
		moveGoal(-10);
	}
}

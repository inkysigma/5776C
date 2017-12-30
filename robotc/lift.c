void moveMainLift(int power) {
	motor[lLift] = power;
	motor[rLift] = -power;
}

void setLift(Lift l, int target, int timeout, int power) {
	l.target = target;
	l.timeout = timeout;
	l.power = power;
}

task autonMainLift() {
	int error = mainLift.target - SensorValue[lift];
	int timer = 0;

	if (error > 0) {
		while (error > 0 && timer < mainLift.timeout) {
			moveMainLift(mainLift.power);
			timer += 20;
			wait1Msec(20);
			error = mainLift.target - SensorValue[lift];
		}
	} else if (error < 0) {
		while (error < 0 && timer < mainLift.timeout) {
			moveMainLift(-mainLift.power);
			timer += 20;
			wait1Msec(20);
			error = mainLift.target - SensorValue[lift];
		}
	}

	moveMainLift(-sgn(error) * 30);
	wait1Msec(50);
	moveMainLift(0);
	stopTask(autonMainLift);
}

task mainLiftPI() {
	float kp = 0.35; float ki = 0.05;
	int error; int integral = 0;
	int integralCap = 30; int powerCap = 127;

	while (true) {
		// hold with PI
		error = mainLift.target - SensorValue[lift];
		integral += error;

		int integralPower = (abs(integral) < integralCap) ? integral : integralCap;

		int PIpower = kp * error + ki * integralPower;

		if (abs(error) < 30) {
			mainLift.power = 0;
		} else if (abs(error) < 500 && sgn(PIpower) == -1) {
			mainLift.power = sgn(PIpower) * 30;
		} else if (abs(error) < 200 && sgn(PIpower) == 1) {
			mainLift.power = sgn(PIpower) * 30;
		} else if (abs(PIpower) > powerCap) {
			mainLift.power = sgn(PIpower) * powerCap;
		} else {
			mainLift.power = PIpower;
		}

		moveMainLift(mainLift.power);
		wait1Msec(20);
	}
}

void moveTopLift(int power) {
	motor[vertibar] = power;
}

task autonTopLift() {
	int error = topLift.target - SensorValue[vertibar];
	int timer = 0;

	if (error > 0) {
		while (error > 0 && timer < topLift.timeout) {
			moveTopLift(topLift.power);
			wait1Msec(20);
			timer += 20;
			error = topLift.target - SensorValue[vertibar];
		}
	} else {
		while (error < 0 && timer < topLift.timeout) {
				moveTopLift(-topLift.power);
				wait1Msec(20);
				timer += 20;
				error = topLift.target - SensorValue[vertibar];
			}
	}

	if (topLift.target == 2750) {
		moveTopLift(35);
	} else {
		moveTopLift(0);
	}
}

task topLiftPI() {
	float kp = 0.18; float ki = 0.08;
	int error; int integral = 0;
	int integralCap = 15;	int powerCap = 127;

	while (true) {
		error = topLift.target - SensorValue[vertibar];
		integral += error;

		int integralPower = (abs(integral) < integralCap) ? integral : integralCap;

		int PIpower = kp * error + ki * integralPower;

		if (abs(error) < 20) {
			topLift.power = 0;
		} else if (abs(PIpower) > 5 && abs(PIpower) < 20) {
			topLift.power = sgn(PIpower) * 20;
		} else if (abs(PIpower) > powerCap) {
			topLift.power = sgn(PIpower) * powerCap;
		} else {
			topLift.power = PIpower;
		}

		moveTopLift(topLift.power);
		wait1Msec(20);
	}
}

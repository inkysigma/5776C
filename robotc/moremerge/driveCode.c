#pragma config(UART_Usage, UART2, uartNotUsed, baudRate4800, IOPins, None, None)
#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    lift,           sensorPotentiometer)
#pragma config(Sensor, in3,    gyro,           sensorGyro)
#pragma config(Sensor, in4,    mobogo,         sensorPotentiometer)
#pragma config(Sensor, in5,    vertibar,       sensorPotentiometer)
#pragma config(Sensor, dgtl10, matchloads,     sensorDigitalIn)
#pragma config(Sensor, I2C_1,  LeftDrive,      sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  RightDrive,     sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port2,           rGoal,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           lVertibar,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           lDrive,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           rDrive,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           claw,          tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           rVertibar,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           lLift,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           rLift,         tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"

// this, for historical reasons, holds the configuration for whether
// we are on the blue side. use the define header guard to ensure that
// this file is only included once
#include "configuration.h"

// motors.h contains some abstraction for motor control
// functions such as moveLift(int power) depend on this file.
// in general, move_x_(int power), sets the motors controlling x
// to the power given. this also ensures that polarity is really
// only ever flipped in this file
#ifndef MOTOR_H
#include "motors.h"
#endif


// this file contains the lift pid which uses define header guards in
// order to protect
#ifndef PID_LIFT_C
#include "pid/lift.c"
#endif
#ifndef PID_VERT_C
#include "pid/vertibar.c"
#endif
#ifndef OPERATIONS_AUTOBUILD_C
#include "operations/autobuild.c"
#endif
#ifndef OPERATIONS_AUTONOMOUS_H
#include "operations/autonomous.h"
#endif
#ifndef UTIL_MATH_H
#include "../util/math.h"
#endif

// this defines the number of points you want the autonomous to score
// most of these names are for legacy reasons.
// the currently supported ones are:
// 10: this is actually a 13 point autonomous that scores in the 5 point zone
// 20: this is a fully twenty four point autonomous that picks up two
// 27: this is a twenty seven point autonomous that needs more work but
//		 puts an item on the stationary goal and fetches the mogo in the twenty
#define AUTONOMOUS_GOAL 10

// the following files are included depending on the autonomous selected
#if AUTONOMOUS_GOAL==20
#include "autonomous/twentyauto.c"
#elif AUTONOMOUS_GOAL==24
// the twenty four auto is really contained by the twenty points file
#include "autonomous/twentyfourauto.c"
#elif AUTONOMOUS_GOAL==10
#include "autonomous/tenauto.c"
#elif AUTONOMOUS_GOAL==13
#include "autonomous/thirteenauto.c"
#elif AUTONOMOUS_GOAL==0
#include "autonomous/defensive.c"
#elif AUTONOMOUS_GOAL==27
#include "autonomous/stagoauto.c"
#endif

void pre_auton() {
	// clear the debug stream so that when debugging
	// there are no records of previous run to confuse person
	datalogClear();
	clearDebugStream();

	// reset the drive IME to ensure calibration
	resetDriveIME();

	// calibrate the gyro
	SensorType[gyro] = sensorNone;

	// we need to wait a full second before proceeding on
	wait1Msec(1000);
	SensorType[gyro] = sensorGyro;
	delay(1100);

	// reset the gyro to 0 to ensure calibration
	SensorValue[gyro] = 0;
}

task autonomous() {
	// autonomous will run different functions in different files
	// depending on the autonomous selection. see above for options
#if AUTONOMOUS_GOAL==10
	ten();
#elif AUTONOMOUS_GOAL==20
	twenty();
#elif AUTONOMOUS_GOAL==24
	twentyfour();
#elif AUTONOMOUS_GOAL==13
	thirteen();
#elif AUTONOMOUS_GOAL==0
	defensive();
#elif AUTONOMOUS_GOAL==27
	stago();
#endif
}


// number of cones on mogo, referenced in autostack functions
int coneCounter = 0;
// recount checks if we should increment the cone counter upon the next cycle.
// this is generally done because we want the ability to cancel and not increment.
// increment is checked by checking if recount is true and checking if the autostack
// task is no longer being done.
bool recount = false;
// check if we should set a stall on the lift. when using 8D in order to reach match
// loader height, we need to not continuously set a stall torque
bool stallLift = true;

task usercontrol()
{
	resetDriveIME();
	//current number of times claw has opened; used to keep track of current state
	int clawCounter = 0;

	// set vertibar target prior to setup the pid
	setVertibarTarget(SensorValue[vertibar]);

	// set the lift target prior to setup the pid
	setLiftTarget(SensorValue[lift]);

	// start the while loop for control
	while(true) {
		// create a small delay so that other tasks can run
		delay(60);

		// move the drive in a tank fasion
		// this may change to account for turn later on
		moveDrive(vexRT[Ch3], vexRT[Ch2]);

		// vertibar control
		// first check that the autostack is not running
		if (!getRunning()) {
			// ensure that the pid isn't runnng for some reason
			// this segment enables moving the motors directly rather
			// than setting the pid target
			if (!getVertibarPidRunning()) {
				// move the vertibar based on whether the up or down button
				// is pressed. this simply compressed it to one line
				moveVertibar(100 * vexRT[Btn6U] + -100 * vexRT[Btn6D]);
			}
			else {
				// if the pid is running, increment and decrement the vertibar
				// target.
				if (vexRT[Btn6U]) incrementVert();
				else if (vexRT[Btn6D]) decrementVert();
			}
		}


		//mobileBtn7D
		// this controls the mobile goal. positive power moves it out
		// while the opposite moves it in.
		motor[port2] = 100 * vexRT[Btn7U] + -90 * vexRT[Btn7L];


		// this is lift control which behaves similarly to the vertibar control
		if (vexRT[Btn5U]) {
			// increment the target if we are using the pid.
			// if we aren't, this has no effect
			incrementLift();

			// if the pid and autostack aren't running, then we can apply motor power
			// to raise the lift
			if (!getRunning() && !getLiftPidRunning()) moveLift(100);
		}
		else if (vexRT[Btn5D]) {
			// decrement the lift
			decrementLift();
			if (!getRunning() && !getLiftPidRunning()) moveLift(-100);
		}
		else {
			if (!getRunning() && !getLiftPidRunning() && stallLift) moveLift(0);
		}



		if (!getRunning() && recount) {
			coneCounter++;
			recount = false;
		}

		// counter control
		// decrement the counter if 8L is pressed
		if (vexRT[Btn8L] && coneCounter > 0) {
			// wait until release since we don't want to double click
			waitUntil(!vexRT[Btn8L]);
			// actually decrease the cone counter
			--coneCounter;
		}
		else if (vexRT[Btn8R]) {
			// we want to increment the cone counter
			// we should wait until release in order to avoid double counting
			waitUntil(!vexRT[Btn8R]);
			// actually increase the cone counter
			++coneCounter;
		}

		// check if the reset button was pressed
		// we do not need to wait for release because
		// we reset to 0 anyway
		if(vexRT[Btn8U]) coneCounter = 0;

		// match loads control. if the button is pressed during match loads,
		// cancel. if the second part of match loads is being done (i.e. the lift
		// is coming down) queue up another match load
		if (vexRT[Btn7R] && !getRunning() && !recount) {
			// stop the lift pid if it is running since our
			// auto stack requires no pid. having a pid will interfere with
			// functionality
			stopLiftPid();

			// start the task of building the match load.
			// this should return fairly quickly since it's only a function
			// that configures and starts the buildStack
			buildDriverLoads(coneCounter);

			// reset the claw counter so that we can close the claw when coming down
			// the autostack will automatically open the claw and apply necessary stall
			clawCounter = 0;

			// wait until we release the button since we don't want to automatically cancel
			// the function
			waitUntil(!vexRT[Btn7R]);

			// set recount to true so that when autostack finishes, we increment
			recount = true;
		}
		else if (vexRT[Btn7R] && getRunning()) {
			// set recount to false so we don't increment
			recount = false;

			// wait until we release so we don't automatically being trying to autostack
			waitUntil(!vexRT[Btn7R]);

			// stop the autobuild
			stopAutoBuild();
		}


		// claw control is mandated here
		// first check if the toggle button is pressed and check autostack is not running
		if(vexRT[Btn7D] && !getRunning())
		{
			// increment the cone counter. this can be placed after
			// but will reverse the effects. this also enables alternation
			++clawCounter;

			// this modulus allows double alternation
			if(clawCounter % 2 == 0) {
				motor[port6] = -100;
				wait1Msec(200);
				motor[port6] = -20;
			}
			else if(clawCounter % 2 == 1) {
				motor[port6] = 100;
				wait1Msec(200);
				motor[port6] = 5;
			}
		}


		if (vexRT[Btn8D] && !getRunning()) {
			delay(400);
			if (vexRT[Btn7R]) {
				buildMatchLoads(coneCounter);
				recount = true;
				waitUntil(!vexRT[Btn8D] && !vexRT[Btn7R]);
			}
			else {
				if (!SensorValue[matchloads]) {
					stallLift = false;
					moveLift(70);

					waitUntil(SensorValue[matchloads] || !vexRT[Btn8D]);
					moveLift(-10);
					delay(400);
					moveLift(30);
					stallLift = true;
				}
				else {
					moveLift(-70);
					waitUntil(!SensorValue[matchloads] || !vexRT[Btn8D]);
					moveLift(30);
					stallLift = true;
				}
			}
		}
	}
}

#pragma config(UART_Usage, UART2, uartNotUsed, baudRate4800, IOPins, None, None)
#pragma config(Sensor, in1,    lift,           sensorPotentiometer)
#pragma config(Sensor, in3,    gyro,           sensorGyro)
#pragma config(Sensor, in4,    mobogo,         sensorPotentiometer)
#pragma config(Sensor, in5,    vertibar,       sensorPotentiometer)
#pragma config(Sensor, I2C_1,  LeftDrive,      sensorNone)
#pragma config(Sensor, I2C_2,  RightDrive,     sensorNone)
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

#define AUTONOMOUS_GOAL 20

#if AUTONOMOUS_GOAL==20
#include "twentyauto.c"
#elif AUTONOMOUS_GOAL==24
#include "twentyfourauto.c"
#elif AUTONOMOUS_GOAL==10
#include "tenauto.c"
#elif AUTONOMOUS_GOAL==27
#include "supportauto.c"
#elif AUTONOMOUS_GOAL==-1
#endif


void pre_auton() {
	SensorType[gyro] = sensorNone;
	wait1Msec(1000);
	SensorType[gyro] = sensorGyro;
	delay(1100);
	SensorValue[gyro] = 0;
}

task autonomous() {
#if AUTONOMOUS_GOAL==10
	ten();
#elif AUTONOMOUS_GOAL==20
	twenty();
#elif AUTONOMOUS_GOAL==27
	twentyseven();
#elif AUTONOMOUS_GOAL==24
	twenty();
#endif
}

task alternateControl() {
	while (true) {
		if (vexRT[Btn7R] && !getRunning()) {
			waitUntil(!vexRT[Btn7R]);
			startTask(liftpid);
			setLift(1600, 800);
			int prevPosition =  SensorValue[lift];
			delay(200);
			while (SensorValue[lift] - prevPosition > 20) {
				prevPosition = SensorValue[lift];
				delay(200);
			}
			delay(400);
			stopLiftPid();
	}}
}

task usercontrol()
{
	resetDriveIME();
	startTask(alternateControl);
	//current number of times claw has opened; used to keep track of current state
	int clawCounter = 0;

	//number of cones on mogo, referenced in autostack function
	int coneCounter = 0;

	// are we going to increment when it switches
	bool recount = false;

	//used to detect change of state of claw input button
	bool isClaw = false;
	setVertibarTarget(SensorValue[vertibar]);
	setLiftTarget(SensorValue[lift]);

	while(true) {
		delay(20);
		motor[port4] = -vexRT[Ch2];
		motor[port5] = vexRT[Ch3];

		//vertibar
		if (!getRunning()) {
			if (!getVertibarPidRunning()) {
				moveVertibar(100 * vexRT[Btn6U] + -100 * vexRT[Btn6D]);
				} else {
				if (vexRT[Btn6U]) incrementVert();
				else if (vexRT[Btn6D]) decrementVert();
			}
		}



		//mobileBtn7D
		motor[port2] = 100 * vexRT[Btn7U] + -90 * vexRT[Btn7L];

		if (vexRT[Btn5U]) {
			incrementLift();
			if (!getRunning() && !getLiftPidRunning()) moveLift(100);
		}
		else if (vexRT[Btn5D]) {
			decrementLift();
			if (!getRunning() && !getLiftPidRunning()) moveLift(-100);
		}
		else {
			if (!getRunning() && !getLiftPidRunning()) moveLift(0);
		}


		// counter control
		if (vexRT[Btn8L] && coneCounter > 0) {
			waitUntil(!vexRT[Btn8L]);
			--coneCounter;
			} else if (vexRT[Btn8R]) {
			waitUntil(!vexRT[Btn8R]);
			++coneCounter;
		}

		if(vexRT[Btn8U]) coneCounter = 0;

		if (vexRT[Btn8D] && !getVertibarPidRunning()) {
			startTask(vertpid);
			setVertibarTarget(2900);
			waitUntil(!vexRT[Btn8D]);
		}
		else if (vexRT[Btn8D] && getVertibarPidRunning()) {
			setVertibarTarget(3600);
			delay(500);
			stopVertibarPid();
			waitUntil(!vexRT[Btn8D]);
		}


		if (!getRunning() && recount) {
			coneCounter++;
			recount = false;
		}

		if(vexRT[Btn7D]) {
			if(!isClaw) {
				++clawCounter;
				isClaw = true;
				if(clawCounter % 2 == 0) {
					motor[port6] = -100;
					wait1Msec(200);
					motor[port6] = -20;
				}
				else if(clawCounter % 2 == 1) {
					motor[port6] = 100;
					wait1Msec(200);
					motor[port6] = 30;
				}

			}
		}
		else {
			isClaw = false;
		}
	}
}

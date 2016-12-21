/** @file auto.c
 * @brief File for autonomous code
 *
 * This file should contain the user autonomous() function and any functions

related to it.
 *
 * Copyright (c) 2011-2014, Purdue University ACM SIG BOTS.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of Purdue University ACM SIG BOTS nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL PURDUE UNIVERSITY ACM SIG BOTS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Purdue Robotics OS contains FreeRTOS (http://www.freertos.org) whose source

code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"

/*
 * Runs the user autonomous code. This function will be started in its own task

with the default
 * priority and stack size whenever the robot is enabled via the Field Management

System or the
 * VEX Competition Switch in the autonomous mode. If the robot is disabled or

communications is
 * lost, the autonomous task will be stopped by the kernel. Re-enabling the robot

will restart
 * the task, not re-start it from where it left off.
 *
 * Code running in the autonomous task cannot access information from the VEX

Joystick. However,
 * the autonomous function can be invoked from another task if a VEX Competition

Switch is not
 * available, and it can access joystick information if called in this way.
 *
 * The autonomous task may exit, unlike operatorControl() which should never exit.

If it does
 * so, the robot will await a switch to another mode or disable/enable cycle.
 */

/**
 * This is where you declare all of the actions the robot will take.
 * The options are DriveForTime which is useful for driving into something
 * but shouldn't be used elsewhere, DriveToWayPoint, which will handle
 * driving forward and back, strafing, and turning (turning must be in
 * its own step) and AutoLiftToHeight which will bring the lift to a
 * specified height (Note: Once the step where this function is used has
 * completed, the lift will move down due to gravity. To avoid this,
 * create a new AutoLiftToHeight function to keep the lift at the desired
 * height. Also, the lift to height code isn't perfectly tuned yet,
 * if the autonomous stalls with the autoLiftToHeight function, help the
 * lift up.)
 *
 * Running the pickup or spinner does not require an object to be declared
 * or instantiated, an example is shown below.
 */

int isAuto = 1;

long int stepStartTime;

int globalTimeout;

/**
 * Runs at the start of autonomous. Steps should be initialized here.
 */
DriveToWPProperties *defaultProps;
// START OF DECLARATIONS

DriveToWP * command1;
DriveToWP * command2;

AutoLiftLock * command3;
Timeout * command4;
AutoLiftLock * command5;
DriveToWP * command6;
DriveToWP * command7;
DriveToWP * command8;
DriveToWP * command9;
DriveToWP * command10;
DriveToWP * command11;
DriveToWP * command12;
DriveToWP * command13;
DriveToWP * command14;
DriveToWP * command15;

AutoLiftLock * command16;
Timeout * command17;
AutoLiftLock * command18;
AutoDumper * command19;
DriveToWP * command20;
Timeout * command21;

DriveToWP * command22;
DriveToWP * command23;
DriveToWP * command24;
DriveToWP * command25;
DriveToWP * command26;
Timeout * command27;

DriveToWP * command28;
DriveToWP * command29;
DriveToWP * command30;
AutoDumper * command31;
Timeout * command32;

Timeout * command33;
AutoDumper * command34;

// END OF DECLARATIONS

void autonomousInit()
{
	defaultProps = initDriveToWPProperties(robotDrive, 0.5, 18, 500, 100, 40, 2, 40,
			70, 40, 3.25, 1, 500);
	// START OF INSTANTIATIONS
if(autonomousSelection == DO_NOTHING)
{
}
if(autonomousSelection == MODE_1)
{
	command1 = initDriveToWP(defaultProps,24,0);
	command2 = initDriveToWP(defaultProps,0,90);
}
if(autonomousSelection == FENCE)
{
	command3 = initAutoLiftLock(robotLiftLock,IN);
	command4 = initTimeout(500);
	command5 = initAutoLiftLock(robotLiftLock,OUT);
	command6 = initDriveToWP(defaultProps,52,0);
	command7 = initDriveToWP(defaultProps,0,90);
	command8 = initDriveToWP(defaultProps,-18,0);
	command9 = initDriveToWP(defaultProps,30,0);
	command10 = initDriveToWP(defaultProps,0,-30);
	command11 = initDriveToWP(defaultProps,18,0);
	command12 = initDriveToWP(defaultProps,0,30);
	command13 = initDriveToWP(defaultProps,18,0);
	command14 = initDriveToWP(defaultProps,0,-30);
	command15 = initDriveToWP(defaultProps,36,0);
}
if(autonomousSelection == RAM)
{
	command16 = initAutoLiftLock(robotLiftLock,IN);
	command17 = initTimeout(500);
	command18 = initAutoLiftLock(robotLiftLock,OUT);
	command19 = initAutoDumper(robotDumper,DUMPER_AUTO_HEIGHT);
	command20 = initDriveToWP(defaultProps,54,0);
	command21 = initTimeout(6000);

	command22 = initDriveToWP(defaultProps,-24,0);
	command23 = initDriveToWP(defaultProps,0,-25);
	command24 = initDriveToWP(defaultProps,24,0);
	command25 = initDriveToWP(defaultProps,0,-20);
	command26 = initDriveToWP(defaultProps,12,0);
	command27 = initTimeout(2000);

	command28 = initDriveToWP(defaultProps,-24,0);
	command29 = initDriveToWP(defaultProps,0,-135);
	command30 = initDriveToWP(defaultProps,-20,0);
	command31 = initAutoDumper(robotDumper,DUMPER_HIGH);
	command32 = initTimeout(4000);

	command33 = initTimeout(2000);
	command34 = initAutoDumper(robotDumper,DUMPER_AUTO_HEIGHT);
}
	// END OF INSTANTIATIONS
	/**
	 * Here, the different steps are instantiated and details are
	 * given about them. By hovering over the function name, you can see a
	 * list of the arguments to pass in.
	 */

	globalTimeout = 6000;

	autonomousInfo.lastStep = 0;
	autonomousInfo.step = 1;
	autonomousInfo.isFinished = 0;

	stepStartTime = millis();
}

/**
 * Runs continuously during autonomous, should exit relatively promptly.
 */
void autonomousPeriodic()
{
	if(autonomousInfo.step != autonomousInfo.lastStep)
	{
		stepStartTime = millis();
	}

	autonomousInfo.elapsedTime = millis() - stepStartTime;

	//lcdPrint(uart1, 1, "Step: %d", autonomousInfo.step);

	switch(autonomousSelection)
	{
	// START OF EXECUTIONS
		case(DO_NOTHING):
		switch(autonomousInfo.step)
		{


			default:
				isAuto = 0;
				break;
		}
		break;
		case(MODE_1):
		switch(autonomousInfo.step)
		{
			case(1):
				driveToWP(command1);

				autonomousInfo.isFinished = (*command1).isFinished;
				break;
			case(2):
				driveToWP(command2);

				autonomousInfo.isFinished = (*command2).isFinished;
				break;


			default:
				isAuto = 0;
				break;
		}
		break;
		case(FENCE):
		switch(autonomousInfo.step)
		{
			case(1):
				autoLiftLock(command3);

				autonomousInfo.isFinished = (*command3).isFinished;
				break;
			case(2):
				timeout(command4);

				autonomousInfo.isFinished = (*command4).isFinished;
				break;
			case(3):
				autoLiftLock(command5);

				autonomousInfo.isFinished = (*command5).isFinished;
				break;
			case(4):
				driveToWP(command6);

				autonomousInfo.isFinished = (*command6).isFinished;
				break;
			case(5):
				driveToWP(command7);

				autonomousInfo.isFinished = (*command7).isFinished;
				break;
			case(6):
				driveToWP(command8);

				autonomousInfo.isFinished = (*command8).isFinished;
				break;
			case(7):
				driveToWP(command9);

				autonomousInfo.isFinished = (*command9).isFinished;
				break;
			case(8):
				driveToWP(command10);

				autonomousInfo.isFinished = (*command10).isFinished;
				break;
			case(9):
				driveToWP(command11);

				autonomousInfo.isFinished = (*command11).isFinished;
				break;
			case(10):
				driveToWP(command12);

				autonomousInfo.isFinished = (*command12).isFinished;
				break;
			case(11):
				driveToWP(command13);

				autonomousInfo.isFinished = (*command13).isFinished;
				break;
			case(12):
				driveToWP(command14);

				autonomousInfo.isFinished = (*command14).isFinished;
				break;
			case(13):
				driveToWP(command15);

				autonomousInfo.isFinished = (*command15).isFinished;
				break;


			default:
				isAuto = 0;
				break;
		}
		break;
		case(RAM):
		switch(autonomousInfo.step)
		{
			case(1):
				autoLiftLock(command16);

				autonomousInfo.isFinished = (*command16).isFinished;
				break;
			case(2):
				timeout(command17);

				autonomousInfo.isFinished = (*command17).isFinished;
				break;
			case(3):
				autoLiftLock(command18);

				autonomousInfo.isFinished = (*command18).isFinished;
				break;
			case(4):
				autoDumper(command19);
				driveToWP(command20);
				timeout(command21);
				autonomousInfo.isFinished = (*command19).isFinished && (*command20).isFinished || (*command21).isFinished;
				break;
			case(5):
				driveToWP(command22);

				autonomousInfo.isFinished = (*command22).isFinished;
				break;
			case(6):
				driveToWP(command23);

				autonomousInfo.isFinished = (*command23).isFinished;
				break;
			case(7):
				driveToWP(command24);

				autonomousInfo.isFinished = (*command24).isFinished;
				break;
			case(8):
				driveToWP(command25);

				autonomousInfo.isFinished = (*command25).isFinished;
				break;
			case(9):
				driveToWP(command26);
				timeout(command27);
				autonomousInfo.isFinished = (*command26).isFinished || (*command27).isFinished;
				break;
			case(10):
				driveToWP(command28);

				autonomousInfo.isFinished = (*command28).isFinished;
				break;
			case(11):
				driveToWP(command29);

				autonomousInfo.isFinished = (*command29).isFinished;
				break;
			case(12):
				driveToWP(command30);
				autoDumper(command31);
				timeout(command32);
				autonomousInfo.isFinished = (*command30).isFinished && (*command31).isFinished || (*command32).isFinished;
				break;
			case(13):
				timeout(command33);

				autonomousInfo.isFinished = (*command33).isFinished;
				break;
			case(14):
				autoDumper(command34);

				autonomousInfo.isFinished = (*command34).isFinished;
				break;


			default:
				isAuto = 0;
				break;
		}
		break;
	// END OF EXECUTIONS

	default:
		isAuto = 0;
		break;
	}

	autonomousInfo.lastStep = autonomousInfo.step;

	//lcdPrint(uart1, 1, "Step: %d", autonomousInfo.step);

	if(autonomousInfo.isFinished)
	{
		autonomousInfo.step ++;
		autonomousInfo.isFinished = 0;
	}

}

void autonomous()
{
	lcdSetText(uart1, 1, "started");

	autonomousInit();

	//lcdSetText(uart1, 1, "initialized");

	while(isAuto)
	{
		autonomousPeriodic();

		if(isOnline())
		{
			if(!isAutonomous() || !isEnabled()) isAuto = 0;
		}

		delay(20);

		//puts("Autonomous");
	}
}


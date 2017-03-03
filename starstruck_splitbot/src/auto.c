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
DriveToWPProperties *defaultBig;
DriveToWPProperties *defaultSmall;
// START OF DECLARATIONS

DriveToWP * command1;
Timeout * command2;

AutoWall * command3;
DriveToWP * command4;
DriveToWP * command5;
Timeout * command6;

DriveToWP * command7;
DriveToWP * command8;
Timeout * command9;

DriveToWP * command10;
DriveToWP * command11;
Timeout * command12;

DriveToWP * command13;
DriveToWP * command14;
Timeout * command15;

DriveToWP * command16;
Timeout * command17;

DriveToWP * command18;
Timeout * command19;


DriveToWP * command20;
Timeout * command21;

DriveToWP * command22;
DriveToWP * command23;
Timeout * command24;

AutoWall * command25;
DriveToWP * command26;
DriveToWP * command27;
Timeout * command28;

DriveToWP * command29;
DriveToWP * command30;
Timeout * command31;

DriveToWP * command32;
DriveToWP * command33;
Timeout * command34;

DriveToWP * command35;
Timeout * command36;

DriveToWP * command37;
Timeout * command38;


DriveToWP * command39;

DriveToWP * command40;
DriveToWP * command41;
DriveToWP * command42;
DriveToWP * command43;

// END OF DECLARATIONS

void autonomousInit()
{
	defaultBig = initDriveToWPProperties(bigDrive,
				0.5, 18, 500, 100, 40, // MAG
				0.5, 18, 500, 100, 60, // DIR
				2, 40, 70, 40, 4.25, 1, 500); //ROT
	defaultSmall = initDriveToWPProperties(smallDrive,
				0.5, 18, 500, 100, 30, // MAG
				0.5, 18, 500, 100, 40, // DIR
				2, 40, 70, 25, 3.5, 1, 500); //ROT
	// START OF INSTANTIATIONS
if(autonomousSelection == DO_NOTHING)
{
}
if(autonomousSelection == MODE_1)
{
	command1 = initDriveToWP(defaultBig,52,0,0);
	command2 = initTimeout(5000);

	command3 = initAutoWall(bigWall,WALL_DEPLOY);
	command4 = initDriveToWP(defaultBig,-10,0,0);
	command5 = initDriveToWP(defaultSmall,-6,0,0);
	command6 = initTimeout(2000);

	command7 = initDriveToWP(defaultBig,0,-42,0);
	command8 = initDriveToWP(defaultSmall,10,0,0);
	command9 = initTimeout(3000);

	command10 = initDriveToWP(defaultBig,10, 0, 0);
	command11 = initDriveToWP(defaultSmall, 0, 0, -90);
	command12 = initTimeout(3000);

	command13 = initDriveToWP(defaultBig, 20,0,0);
	command14 = initDriveToWP(defaultSmall, 100, 0, 0);
	command15 = initTimeout(5000);

	command16 = initDriveToWP(defaultSmall, 0,0,90);
	command17 = initTimeout(3000);

	command18 = initDriveToWP(defaultSmall, 100,0,0);
	command19 = initTimeout(3000);

}
if(autonomousSelection == MID_FAST)
{
	command20 = initDriveToWP(defaultBig,24,0,0);
	command21 = initTimeout(5000);

	command22 = initDriveToWP(defaultBig,24,-36,0);
	command23 = initDriveToWP(defaultSmall,-6,0,0);
	command24 = initTimeout(2000);

	command25 = initAutoWall(bigWall,WALL_DEPLOY);
	command26 = initDriveToWP(defaultBig,6,-12,0);
	command27 = initDriveToWP(defaultSmall,10,0,0);
	command28 = initTimeout(3000);

	command29 = initDriveToWP(defaultBig,10, 0, 0);
	command30 = initDriveToWP(defaultSmall, 0, 0, -75);
	command31 = initTimeout(3000);

	command32 = initDriveToWP(defaultBig, 20,0,0);
	command33 = initDriveToWP(defaultSmall, 100, 0, 0);
	command34 = initTimeout(5000);

	command35 = initDriveToWP(defaultSmall, 0,0,90);
	command36 = initTimeout(3000);

	command37 = initDriveToWP(defaultSmall, 100,0,0);
	command38 = initTimeout(3000);

}
if(autonomousSelection == BIG_TEST)
{
	command39 = initDriveToWP(defaultBig,0,-24,0);
}
if(autonomousSelection == SMALL_TEST)
{
	command40 = initDriveToWP(defaultSmall,24,0,0);
	command41 = initDriveToWP(defaultSmall,0,0,90);
	command42 = initDriveToWP(defaultSmall,0,0,-90);
	command43 = initDriveToWP(defaultSmall,-24,0,0);
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
				timeout(command2);
				autonomousInfo.isFinished = (*command1).isFinished || (*command2).isFinished;
				break;
			case(2):
				autoWall(command3);

				autonomousInfo.isFinished = (*command3).isFinished;
				break;
			case(3):
				driveToWP(command4);
				driveToWP(command5);
				timeout(command6);
				autonomousInfo.isFinished = (*command4).isFinished && (*command5).isFinished || (*command6).isFinished;
				break;
			case(4):
				driveToWP(command7);
				driveToWP(command8);
				timeout(command9);
				autonomousInfo.isFinished = (*command7).isFinished && (*command8).isFinished || (*command9).isFinished;
				break;
			case(5):
				driveToWP(command10);
				driveToWP(command11);
				timeout(command12);
				autonomousInfo.isFinished = (*command10).isFinished && (*command11).isFinished || (*command12).isFinished;
				break;
			case(6):
				driveToWP(command13);
				driveToWP(command14);
				timeout(command15);
				autonomousInfo.isFinished = (*command13).isFinished && (*command14).isFinished || (*command15).isFinished;
				break;
			case(7):
				driveToWP(command16);
				timeout(command17);
				autonomousInfo.isFinished = (*command16).isFinished || (*command17).isFinished;
				break;
			case(8):
				driveToWP(command18);
				timeout(command19);
				autonomousInfo.isFinished = (*command18).isFinished || (*command19).isFinished;
				break;


			default:
				isAuto = 0;
				break;
		}
		break;
		case(MID_FAST):
		switch(autonomousInfo.step)
		{
			case(1):
				driveToWP(command20);
				timeout(command21);
				autonomousInfo.isFinished = (*command20).isFinished || (*command21).isFinished;
				break;
			case(2):
				driveToWP(command22);
				driveToWP(command23);
				timeout(command24);
				autonomousInfo.isFinished = (*command22).isFinished && (*command23).isFinished || (*command24).isFinished;
				break;
			case(3):
				autoWall(command25);

				autonomousInfo.isFinished = (*command25).isFinished;
				break;
			case(4):
				driveToWP(command26);
				driveToWP(command27);
				timeout(command28);
				autonomousInfo.isFinished = (*command26).isFinished && (*command27).isFinished || (*command28).isFinished;
				break;
			case(5):
				driveToWP(command29);
				driveToWP(command30);
				timeout(command31);
				autonomousInfo.isFinished = (*command29).isFinished && (*command30).isFinished || (*command31).isFinished;
				break;
			case(6):
				driveToWP(command32);
				driveToWP(command33);
				timeout(command34);
				autonomousInfo.isFinished = (*command32).isFinished && (*command33).isFinished || (*command34).isFinished;
				break;
			case(7):
				driveToWP(command35);
				timeout(command36);
				autonomousInfo.isFinished = (*command35).isFinished || (*command36).isFinished;
				break;
			case(8):
				driveToWP(command37);
				timeout(command38);
				autonomousInfo.isFinished = (*command37).isFinished || (*command38).isFinished;
				break;


			default:
				isAuto = 0;
				break;
		}
		break;
		case(BIG_TEST):
		switch(autonomousInfo.step)
		{
			case(1):
				driveToWP(command39);

				autonomousInfo.isFinished = (*command39).isFinished;
				break;


			default:
				isAuto = 0;
				break;
		}
		break;
		case(SMALL_TEST):
		switch(autonomousInfo.step)
		{
			case(1):
				driveToWP(command40);

				autonomousInfo.isFinished = (*command40).isFinished;
				break;
			case(2):
				driveToWP(command41);

				autonomousInfo.isFinished = (*command41).isFinished;
				break;
			case(3):
				driveToWP(command42);

				autonomousInfo.isFinished = (*command42).isFinished;
				break;
			case(4):
				driveToWP(command43);

				autonomousInfo.isFinished = (*command43).isFinished;
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


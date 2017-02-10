/*
 * OI.c
 *
 *  Created on: Oct 29, 2015
 *      Author: Erik
 */

#include "main.h"

int OIGetDriveLeft()
{
	return joystickGetAnalog(1, 3);
}

int OIGetDriveRight()
{
	return joystickGetAnalog(1, 2);
}

int OIGetDriveY()
{
	return joystickGetAnalog(1, 3);
}

int OIGetDriveX()
{
	return joystickGetAnalog(1, 4);
}

int OIGetDriveMagnitude()
{
	return joystickGetAnalog(2, 3);
}

int OIGetDriveDirection()
{
	return joystickGetAnalog(2, 4);
}

int OIGetDriveRotation()
{
	return joystickGetAnalog(2, 1);
}


int OIGetWallDeploy()
{
	return joystickGetDigital(2, 5, JOY_UP) &&
			joystickGetDigital(2, 6, JOY_UP);
}

int OIGetWallUndeploy()
{
	return joystickGetDigital(2, 5, JOY_DOWN) &&
			joystickGetDigital(2, 6, JOY_DOWN);
}

int OIGetDriveForward()
{
	return joystickGetDigital(1, 7, JOY_UP);
}

int OIGetDriveBackward()
{
	return joystickGetDigital(1, 7, JOY_DOWN);
}

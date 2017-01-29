/*
 * OI.c
 *
 *  Created on: Oct 29, 2015
 *      Author: Erik
 */

#include "main.h"

int OIGetDriveLeft()
{
	return joystickGetAnalog(2, 3);
}

int OIGetDriveRight()
{
	return joystickGetAnalog(2, 2);
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
	return joystickGetAnalog(1, 3);
}

int OIGetDriveDirection()
{
	return joystickGetAnalog(1, 4);
}

int OIGetDriveRotation()
{
	return joystickGetAnalog(1, 1);
}

/*
 * AutoLiftLock.c
 *
 *  Created on: Nov 10, 2016
 *      Author: Erik
 */

#include "main.h"

AutoLiftLock * initAutoLiftLock(LiftLock * lock, int direction)
{
	AutoLiftLock * newStep = malloc(sizeof(AutoLiftLock));

	newStep->lock = lock;
	if(direction == IN || direction == OUT)
	{
		newStep->direction = direction;
	}
	else
	{
		newStep->direction = OUT;
	}
	newStep->isFinished = 0;

	return newStep;
}

void autoLiftLock(AutoLiftLock * step)
{
	if(step->direction == IN)
	{
		liftLockIn(step->lock);
	}
	else
	{
		liftLockOut(step->lock);
	}

	step->isFinished = 1;
}

/*
 * AutoTippers.c
 *
 *  Created on: Nov 10, 2016
 *      Author: Erik
 */

#include "main.h"

AutoTippers * initAutoTippers(AntiTippers * tippers, int direction)
{
	AutoTippers * newStep = malloc(sizeof(AutoTippers));
	newStep->tipper = tippers;
	if(direction == IN || direction == OUT)
	{
		newStep->direction = direction;
	}
	else
	{
		newStep->direction = IN;
	}

	newStep->isFinished = 0;

	return newStep;
}

void autoTippers(AutoTippers * step)
{
	if(step->direction == IN)
	{
		antiTippersIn(step->tipper);
	}
	else
	{
		antiTippersOut(step->tipper);
	}

	step->isFinished = 1;
}

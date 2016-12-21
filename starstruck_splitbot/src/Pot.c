/*
 * Pot.c
 *
 *  Created on: Oct 11, 2016
 *      Author: Erik
 */

#include "main.h"

Pot * initPot(int port, int top, int bottom)
{
	Pot *newPot = malloc(sizeof(Pot));
	newPot->port = port;
	newPot->top = top;
	newPot->bottom = bottom;
	return newPot;
}

/*
 * Returns a scaled value between 0 and 1 for the potentiometer's positions
 * in a defined range.
 */
double potGetScaledValue(Pot * pot)
{
	return ((double) (analogRead(pot->port) - pot->bottom))/
			((double) (pot->top - pot->bottom));
}

int potGetRawValue(Pot * pot)
{
	return analogRead(pot->port);
}

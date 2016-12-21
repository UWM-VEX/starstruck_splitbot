/*
 * AntiTippers.c
 *
 *  Created on: Nov 10, 2016
 *      Author: Erik
 */

#include "main.h"

#define ANTI_TIPPERS_IN LOW
#define ANTI_TIPPERS_OUT HIGH

AntiTippers * initAntiTippers(int port)
{
	AntiTippers * newAntiTippers = malloc(sizeof(AntiTippers));
	newAntiTippers->port = port;

	pinMode(port, OUTPUT);

	digitalWrite(port, ANTI_TIPPERS_OUT);

	return newAntiTippers;
}

void antiTippersIn(AntiTippers * antiTippers)
{
	digitalWrite(antiTippers->port, ANTI_TIPPERS_IN);
}

void antiTippersOut(AntiTippers * antiTippers)
{
	digitalWrite(antiTippers->port, ANTI_TIPPERS_OUT);
}

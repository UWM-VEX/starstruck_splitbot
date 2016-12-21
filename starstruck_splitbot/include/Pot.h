/*
 * Pot.h
 *
 *  Created on: Oct 11, 2016
 *      Author: Erik
 */

#ifndef INCLUDE_POT_H_
#define INCLUDE_POT_H_

#include "main.h"

struct Pot{
	int port;
	int top;
	int bottom;
}typedef Pot;

Pot * initPot(int port, int top, int bottom);
/*
 * Returns a scaled value between 0 and 1 for the potentiometer's positions
 * in a defined range.
 */
double potGetScaledValue(Pot * pot);
int potGetRawValue(Pot * pot);

#endif /* INCLUDE_POT_H_ */

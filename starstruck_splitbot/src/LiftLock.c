/*
 * AntiTippers.c
 *
 *  Created on: Nov 10, 2016
 *      Author: Erik
 */

#include "main.h"

#define LIFT_LOCK_IN HIGH
#define LIFT_LOCK_OUT LOW

LiftLock * initLiftLock(int port, int port2)
{
	LiftLock * newLiftLock = malloc(sizeof(AntiTippers));
	newLiftLock->port = port;
	newLiftLock->port2 = port2;

	pinMode(port, OUTPUT);
	pinMode(port2, OUTPUT);

	digitalWrite(port, LIFT_LOCK_OUT);
	digitalWrite(port, LIFT_LOCK_OUT);

	return newLiftLock;
}

void liftLockIn(LiftLock * liftLock)
{
	digitalWrite(liftLock->port, LIFT_LOCK_IN);
	digitalWrite(liftLock->port2, LIFT_LOCK_IN);
}

void liftLockOut(LiftLock * liftLock)
{
	digitalWrite(liftLock->port, LIFT_LOCK_OUT);
	digitalWrite(liftLock->port2, LIFT_LOCK_OUT);
}

/*
 * Claw.c
 *
 *  Created on: Jan 5, 2017
 *      Author: Erik
 */

#include "main.h"

Claw * initClaw(PantherMotor motor, Pot * pot, double open, double close)
{
	Claw * newClaw = malloc(sizeof(Claw));

	newClaw->motor = motor;
	newClaw->pot = pot;
	newClaw->open = open;
	newClaw->close = close;
	newClaw->mode = CLAW_MANUAL;
	newClaw->autoState = CLAW_OPEN;

	return newClaw;
}

void runClawAtSpeed(Claw * claw, int speed)
{
	setPantherMotor(claw->motor, speed);
}

double clawToPosition(Claw * claw, double sp)
{
	double pv = potGetScaledValue(claw->pot);
	double error = sp - pv;

	if(absDouble(error) < 0.1)
	{
		runClawAtSpeed(claw, 0);
		return 0;
	}
	else if(error > 0)
	{
		runClawAtSpeed(claw, 127);
		return error;
	}
	else
	{
		runClawAtSpeed(claw, -127);
		return error;
	}
}

int clawGetMode(Claw * claw)
{
	return claw->mode;
}

double clawOpen(Claw * claw)
{
	return clawToPosition(claw, claw->open);
}

double clawClose(Claw * claw)
{
	return clawToPosition(claw, claw->close);
}

void clawTeleop(Claw * claw)
{
	lcdPrint(uart1, 1, "Claw: %f", potGetScaledValue(claw->pot));
	if(abs(OIGetClawManual()) > 20)
	{
		claw->mode = CLAW_MANUAL;
		//lcdSetText(uart1, 2, "Manual");
	}
	else
	{
		//lcdSetText(uart1, 2, "Auto");
		if(OIGetClawOpen())
		{
			claw->mode = CLAW_AUTO;
			claw->autoState = CLAW_OPEN;
		}
		else if(OIGetClawClose())
		{
			claw->mode = CLAW_AUTO;
			claw->autoState = CLAW_CLOSE;
		}
	}

	if(claw->mode == CLAW_MANUAL)
	{
		runClawAtSpeed(claw, OIGetClawManual());
	}
	else
	{
		if(claw->autoState == CLAW_OPEN)
		{
			clawOpen(claw);
		}
		else
		{
			clawClose(claw);
		}
	}
}

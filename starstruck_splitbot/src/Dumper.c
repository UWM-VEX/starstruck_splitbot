/*
 * Shovel.c
 *
 *  Created on: Aug 16, 2016
 *      Author: Erik
 */

#include "main.h"

Dumper * initDumper(PantherMotor topLeft, PantherMotor frontLeft, PantherMotor backLeft,
		PantherMotor bottomLeft, PantherMotor topRight, PantherMotor frontRight,
		PantherMotor backRight, PantherMotor bottomRight, Pot * pot, double kP, double kI, double kD,
		double lowHeight, double travelHeight, double highHeight, double hangHeight, double autoHeight)
{
	Dumper * newDumper = malloc(sizeof(Dumper));
	newDumper->topLeft = topLeft;
	newDumper->frontLeft = frontLeft;
	newDumper->backLeft = backLeft;
	newDumper->bottomLeft = bottomLeft;
	newDumper->topRight = topRight;
	newDumper->frontRight = frontRight;
	newDumper->backRight = backRight;
	newDumper->bottomRight = bottomRight;
	newDumper->pot = pot;
	newDumper->pidController = initPIDController(kP, kI, kD, 0, 0, 3);
	newDumper->mode = DUMPER_MANUAL;
	newDumper->height = DUMPER_LOW;
	newDumper->dumpState = DUMPER_RAISING;
	newDumper->lowHeight = lowHeight;
	newDumper->travelHeight = travelHeight;
	newDumper->highHeight = highHeight;
	newDumper->hangHeight = hangHeight;
	newDumper->autoHeight = autoHeight;

	return newDumper;
}

void runDumperAtSpeed(Dumper * shovel, int speed)
{
	setPantherMotor(shovel->topLeft, speed);
	setPantherMotor(shovel->frontLeft, speed);
	setPantherMotor(shovel->backLeft, speed);
	setPantherMotor(shovel->bottomLeft, speed);
	setPantherMotor(shovel->topRight, speed);
	setPantherMotor(shovel->frontRight, speed);
	setPantherMotor(shovel->backRight, speed);
	setPantherMotor(shovel->bottomRight, speed);
}

int dumperToHeight(Dumper *dumper, double height)
{
	double pv = potGetScaledValue(dumper->pot);
	PIDsetSetPoint(dumper->pidController, height);
	int speed = PIDRunController(dumper->pidController, pv);
	speed = limit(speed, 127, -127);
	speed = enforceDeadband(speed, 0, 10);
	runDumperAtSpeed(dumper, speed);
	return speed;
}

void updateDumperPID(Dumper * dumper)
{
	double pv = potGetScaledValue(dumper->pot);
	PIDRunController(dumper->pidController, pv);

	lcdPrint(uart1, 1, "PV: %f", pv);
}

double getDumperHeight(Dumper * dumper)
{
	switch(dumper->height)
	{
	case(DUMPER_LOW):
		return dumper->lowHeight;
	case(DUMPER_TRAVEL):
		return dumper->travelHeight;
	case(DUMPER_HIGH):
		return dumper->highHeight;
	case(DUMPER_HANG):
		return dumper->hangHeight;
	default:
		return dumper->travelHeight;
	}
}

void dumperDump(Dumper * dumper)
{
	double pv = potGetScaledValue(dumper->pot);
	if(dumper->dumpState == DUMPER_RAISING)
	{
		if(inDeadBandDouble(pv, dumper->highHeight, .02))
		{
			dumper->dumpState = DUMPER_FALLING;
		}
		else
		{
			dumperToHeight(dumper, dumper->highHeight);
		}
	}

	if(dumper->dumpState == DUMPER_FALLING)
	{
		if(inDeadBandDouble(pv, dumper->lowHeight, .02))
		{
			dumper->height = DUMPER_LOW;
			dumper->dumpState = DUMPER_RAISING;
		}
		else
		{
			dumperToHeight(dumper, dumper->lowHeight);
		}
	}
}

void dumperTeleop(Dumper * dumper)
{
	if(abs(OIGetDumper()) > 20)
	{
		dumper->mode = DUMPER_MANUAL;
		lcdSetText(uart1, 2, "Manual");
	}
	else
	{
		lcdSetText(uart1, 2, "Auto");
		if(OIGetDumperLow())
		{
			dumper->mode = DUMPER_AUTO;
			dumper->height = DUMPER_LOW;
		}
		else if(OIGetDumperHigh())
		{
			dumper->mode = DUMPER_AUTO;
			dumper->height = DUMPER_HIGH;
		}
	}

	if(dumper->mode == DUMPER_MANUAL)
	{
		runDumperAtSpeed(dumper, OIGetDumper());
	}
	else
	{
		if(dumper->height != DUMPER_DUMP)
		{
			double height = getDumperHeight(dumper);
			dumperToHeight(dumper, height);
		}
		else
		{
			dumperDump(dumper);
		}
	}

	updateDumperPID(dumper);
}

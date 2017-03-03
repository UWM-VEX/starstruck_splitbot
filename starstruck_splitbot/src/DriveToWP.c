/*
 * DriveToWP.c
 *
 *  Created on: Jul 27, 2015
 *      Author: Erik
 */

#include "main.h"

DriveToWPProperties * initDriveToWPProperties(Drive drive, double magnitudeDB,
		double magnitudeBreakingDistance, long magnitudeRampUpTime, int magnitudeMaxSpeed,
		int magnitudeMinSpeed, double directionDB, double directionBreakingDistance,
		long directionRampUpTime, int directionMaxSpeed, int directionMinSpeed,
		int rotationDB, int rotationBreakingDistance, int rotationMaxSpeed,
		int rotationMinSpeed, double wheelDiameter, int gyroInverted,
		unsigned long holdTime)
{
	DriveToWPProperties * newDriveToWPProperties = malloc(sizeof(DriveToWPProperties));

	newDriveToWPProperties->drive = drive;
	newDriveToWPProperties->magnitudeDB = magnitudeDB;
	newDriveToWPProperties->magnitudeBreakingDistance = magnitudeBreakingDistance;
	newDriveToWPProperties->magnitudeRampUpTime = magnitudeRampUpTime;
	newDriveToWPProperties->magnitudeMaxSpeed = magnitudeMaxSpeed;
	newDriveToWPProperties->magnitudeMinSpeed = magnitudeMinSpeed;
	newDriveToWPProperties->directionDB = directionDB;
	newDriveToWPProperties->directionBreakingDistance = directionBreakingDistance;
	newDriveToWPProperties->directionRampUpTime = directionRampUpTime;
	newDriveToWPProperties->directionMaxSpeed = directionMaxSpeed;
	newDriveToWPProperties->directionMinSpeed = directionMinSpeed;
	newDriveToWPProperties->rotationDB = rotationDB;
	newDriveToWPProperties->rotationBreakingDistance = rotationBreakingDistance;
	newDriveToWPProperties->rotationMaxSpeed = rotationMaxSpeed;
	newDriveToWPProperties->rotationMinSpeed = rotationMinSpeed;
	newDriveToWPProperties->wheelDiameter = wheelDiameter;
	newDriveToWPProperties->gyroInverted = gyroInverted;
	newDriveToWPProperties->holdTime = holdTime;

	return newDriveToWPProperties;
}

DriveToWP * initDriveToWP(DriveToWPProperties * properties, double distance,
		double direction, int rotation)
{
	DriveToWP * newDriveToWP = malloc(sizeof(DriveToWP));
	newDriveToWP->distance = distance;
	newDriveToWP->direction = direction;
	newDriveToWP->rotation = rotation;
	newDriveToWP->properties = properties;
	newDriveToWP->reachedDistance = 0;
	newDriveToWP->reachedDirection = 0;
	newDriveToWP->reachedRotation = 0;
	newDriveToWP->timeAchievedGoodLocation = 0;
	newDriveToWP->isFirstTime = 1;
	return newDriveToWP;
}

void driveToWP(DriveToWP * step)
{
	if(step->isFirstTime)
	{
		step->firstLeftEncoder = encoderGet(step->properties->drive.leftEncoder);
		step->firstRightEncoder = encoderGet(step->properties->drive.rightEncoder);
		step->firstGyro = gyroGet(step->properties->drive.gyro);
		step->isFirstTime = 0;
	}

	//lcdPrint(uart1, 1, "l: %d", encoderGet(step->properties->drive.leftEncoder));
	//lcdPrint(uart1, 2, "r: %d", encoderGet(step->properties->drive.rightEncoder));

	double averageMagEncoder = ((double)((encoderGet(step->properties->drive.leftEncoder)
			- step->firstLeftEncoder)
			+ (encoderGet(step->properties->drive.rightEncoder)
					- step->firstRightEncoder)) / 2);
	double averageDirEncoder = encoderGet(step->properties->drive.middleEncoder);
	double distancePV = encoderToInches(averageMagEncoder,
			step->properties->wheelDiameter);
	double directionPV = encoderToInches(averageDirEncoder,
				step->properties->wheelDiameter);
	int rotationPV = gyroGet(step->properties->drive.gyro) - step->firstGyro;

	if(step->properties->gyroInverted)
	{
		rotationPV *= -1;
	}

	//lcdPrint(uart1,1,"Gyro: %d", rotationPV);

	double distanceError = step->distance - distancePV;
	double directionError = step->direction - directionPV;
	int rotationError = step->rotation - rotationPV;

	int inDistanceDB = (absDouble(distanceError) < step->properties->magnitudeDB);

	if(inDistanceDB)
	{
		step->reachedDistance = 1;
	}

	int inDirectionDB = (absDouble(directionError) < step->properties->directionDB) || step->properties->drive.numEncoders == 2;

	if(inDirectionDB)
	{
		step->reachedDirection = 1;
	}

	int inRotationDB = abs(rotationError) < step->properties->rotationDB;

	if(inRotationDB)
	{
		step->reachedRotation = 1;
	}

	int magnitude = 0;
	int direction = 0;
	int rotation = 0;

	// If it has not reached both its distance and rotation targets
	if( ! (step->reachedDistance && step->reachedDirection && step->reachedRotation))
	{
		//lcdSetText(uart1, 1, "Case 1");

		if(inDistanceDB)
		{
			//lcdSetText(uart1, 1, "Mag: DB");
			magnitude = 0;
		}
		else if(absDouble(distanceError) < step->properties->magnitudeBreakingDistance)
		{
			//lcdSetText(uart1, 1, "Mag: Break");
			// slow down
			// magnitude = (Vmax - Vmin)(SP - PV)/Breaking Distance + Vmin
			magnitude = (int) ((step->properties->magnitudeMaxSpeed -
					step->properties->magnitudeMinSpeed) * (distanceError)) /
							step->properties->magnitudeBreakingDistance +
							step->properties->magnitudeMinSpeed;
		}
		else if(autonomousInfo.elapsedTime < step->properties->magnitudeRampUpTime)
		{
			//lcdSetText(uart1, 1, "Mag: Accel");
			// speed up
			// magnitude = (Vmax - Vmin)*t/ramp up time + Vmin
			magnitude = (int) ((step->properties->magnitudeMaxSpeed -
					step->properties->magnitudeMinSpeed) * autonomousInfo.elapsedTime
							/ step->properties->magnitudeRampUpTime +
							step->properties->magnitudeMinSpeed);
		}
		else
		{
			//lcdSetText(uart1, 1, "Mag: Coast");
			// coast
			magnitude = step->properties->magnitudeMaxSpeed;
		}

		if(inDirectionDB || absDouble(step->direction) < step->properties->directionDB || step->properties->drive.numEncoders == 2)
		{
			//lcdSetText(uart1, 2, "Dir: DB");
			direction = 0;
		}
		else if(absDouble(directionError) < step->properties->directionBreakingDistance)
		{
			//lcdSetText(uart1, 2, "Dir: Break");
			// slow down
			// direction = (Vmax - Vmin)(SP - PV)/Breaking direction + Vmin
			direction = (int) ((step->properties->directionMaxSpeed -
					step->properties->directionMinSpeed) * (directionError)) /
							step->properties->directionBreakingDistance +
							step->properties->directionMinSpeed;
		}
		else if(autonomousInfo.elapsedTime < step->properties->directionRampUpTime)
		{
			//lcdSetText(uart1, 2, "Dir: Accel");
			// speed up
			// direction = (Vmax - Vmin)*t/ramp up time + Vmin
			direction = (int) ((step->properties->directionMaxSpeed -
					step->properties->directionMinSpeed) * autonomousInfo.elapsedTime
							/ step->properties->directionRampUpTime +
							step->properties->directionMinSpeed);
		}
		else
		{
			//lcdSetText(uart1, 2, "Dir: Coast");
			// coast
			direction = step->properties->directionMaxSpeed;
		}

		if(inRotationDB)
		{
			//lcdSetText(uart1, 2, "Rot: DB");
			// no rotation
			rotation = 0;
		}
		else if(abs(rotationError) < step->properties->rotationBreakingDistance)
		{
			//lcdSetText(uart1, 2, "Rot: Slow");
			// turn slowly
			rotation = step->properties->rotationMinSpeed;
		}
		else
		{
			//lcdSetText(uart1, 2, "Rot: Fast");
			// turn quickly
			rotation = step->properties->rotationMaxSpeed;
		}

		step->isFinished = 0;
	}
	else
	{
		//lcdSetText(uart1, 1, "Case 2");

		// If at some point we've reached a good distance and a good rotation
		int goodDistance = 0;

		// Check that we're at a good distance, if we're not, slowly move to a good distance
		if(absDouble(distanceError) < step->properties->magnitudeDB)
		{
			lcdSetText(uart1, 1, "Mag: Good");
			goodDistance = 1;
		}
		else
		{
			lcdSetText(uart1, 1, "Mag: Adj");
			magnitude = step->properties->magnitudeMinSpeed;
		}

		// If at some point we've reached a good distance and a good rotation
		int goodDirection = 0;

		// Check that we're at a good distance, if we're not, slowly move to a good distance
		if((absDouble(directionError) < step->properties->directionDB) ||
				(absDouble(step->direction) < step->properties->directionDB) ||
				step->properties->drive.numEncoders == 2)
		{
			//lcdSetText(uart1, 2, "Dir: Good");
			goodDirection = 1;
		}
		else
		{
			//lcdSetText(uart1, 2, "Dir: Adj");
			direction = step->properties->directionMinSpeed;
		}

		int goodRotation = 0;

		// Check that we're at a good rotation, if we're not, slowly move to a good rotation
		if(abs(rotationError) < step->properties->rotationDB)
		{
			//lcdSetText(uart1, 2, "Rot: Good");
			goodRotation = 1;
		}
		else
		{
			//lcdSetText(uart1, 2, "Rot: Adj");
			rotation = step->properties->rotationMinSpeed;
		}

		if(goodDistance && goodDirection && goodRotation)
		{
			if(step->timeAchievedGoodLocation == 0)
			{
				step->timeAchievedGoodLocation = millis();
			}

			if(millis() - step->timeAchievedGoodLocation > step->properties->holdTime)
			{
				step->isFinished = 1;
			}
		}
		else
		{
			step->timeAchievedGoodLocation = 0;
		}
	}

	if(magnitude != 0)
	{
		magnitude = limit(magnitude, step->properties->magnitudeMaxSpeed,
				step->properties->magnitudeMinSpeed);
	}

	if(direction != 0)
	{
		direction = limit(direction, step->properties->directionMaxSpeed,
				step->properties->directionMinSpeed);
	}

	if(rotation != 0)
	{
		rotation = limit(rotation, step->properties->rotationMaxSpeed,
				step->properties->rotationMinSpeed);
	}

	if(absDouble(step->distance) < 0.5 && abs(step->rotation) < step->properties->rotationDB)
	{
		magnitude = 0;
	}

	if(absDouble(step->direction) < 0.5)
	{
		direction = 0;
	}

	if(distanceError < 0)
	{
		magnitude *= -1;
	}

	if(directionError < 0)
	{
		direction *= -1;
	}

	if(rotationError < 0)
	{
		rotation *= -1;
	}

	//lcdPrint(uart1, 1, "%f", directionPV);
	//lcdPrint(uart1, 1, "%f", directionError);
	lcdPrint(uart1, 2, "Mag: %d", magnitude);

	hexDrive(step->properties->drive, magnitude, direction, rotation);
}

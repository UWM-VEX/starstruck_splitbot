#include "main.h"

/**
 * Initializes a new drive object composed of six PantherMotors, two encoders and a gyro.
 */
Drive initDrive(PantherMotor leftMotor, PantherMotor rightMotor,
		Encoder leftEncoder, Encoder rightEncoder, Gyro gyro, int gyroInverted)
{
	Drive newDrive = {leftMotor, rightMotor,
			leftEncoder, rightEncoder,
			gyro, gyroInverted};

	return newDrive;
}

void tankDrive(Drive drive, int left, int right)
{
	left = limit(left, 127, -127);
	right = limit(right, 127, -127);

	setPantherMotor(drive.leftMotor, left);
	setPantherMotor(drive.rightMotor, right);
}

void arcadeDrive(Drive drive, int magnitude, int rotation)
{
	int left = magnitude + rotation;
	int right = magnitude - rotation;

	left = limit(left, 127, -127);
	right = limit(right, 127, -127);

	tankDrive(drive, left, right);
}

int driveGyroRead(Drive drive)
{
	if(drive.gyroInverted)
	{
		return - gyroGet(drive.gyro);
	}
	else
	{
		return gyroGet(drive.gyro);
	}
}

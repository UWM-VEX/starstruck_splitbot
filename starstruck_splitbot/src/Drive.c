#include "main.h"

/**
 * Initializes a new drive object composed of six PantherMotors, two encoders and a gyro.
 */
Drive initDrive(SmartMotor* frontLeftMotor, SmartMotor* frontRightMotor,
		SmartMotor* middleLeftMotor, SmartMotor* middleRightMotor,
		SmartMotor* rearLeftMotor, SmartMotor* rearRightMotor,
		Encoder leftEncoder, Encoder rightEncoder, Gyro gyro)
{
	Drive newDrive = {frontLeftMotor, frontRightMotor,
			middleLeftMotor, middleRightMotor,
			rearLeftMotor, rearRightMotor,
			leftEncoder, rightEncoder, gyro};

	return newDrive;
}

void tankDrive(Drive drive, int left, int right)
{
	left = limit(left, 127, -127);
	right = limit(right, 127, -127);

	setSmartMotor(drive.frontLeftMotor, left);
	setSmartMotor(drive.rearLeftMotor, left);
	setSmartMotor(drive.middleLeftMotor, left);
	setSmartMotor(drive.middleRightMotor, right);
	setSmartMotor(drive.frontRightMotor, right);
	setSmartMotor(drive.rearRightMotor, right);
}

void arcadeDrive(Drive drive, int magnitude, int rotation)
{
	int left = magnitude + rotation;
	int right = magnitude - rotation;

	left = limit(left, 127, -127);
	right = limit(right, 127, -127);

	tankDrive(drive, left, right);
}

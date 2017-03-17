#include "main.h"

/**
 * Initializes a new drive object composed of six PantherMotors, two encoders and a gyro.
 */
Drive initDrive(SmartMotor* frontLeftMotor, SmartMotor* frontRightMotor,
		SmartMotor* middleLeftMotor, SmartMotor* middleRightMotor,
		SmartMotor* rearLeftMotor, SmartMotor* rearRightMotor,
		Encoder leftEncoder, Encoder middleEncoder, Encoder rightEncoder, Gyro gyro, int numEncoders)
{
	Drive newDrive = {frontLeftMotor, frontRightMotor,
			middleLeftMotor, middleRightMotor,
			rearLeftMotor, rearRightMotor,
			leftEncoder, rightEncoder, middleEncoder,
			gyro, numEncoders};

	return newDrive;
}

void hexDrive(Drive drive, int magnitude, int direction, int rotation)
{
	int frontLeft = magnitude + direction + rotation;
	int frontRight = magnitude - direction - rotation;
	int rearLeft = magnitude - direction + rotation;
	int rearRight = magnitude + direction - rotation;

	frontLeft = limit(frontLeft, 127, -127);
	frontRight = limit(frontRight, 127, -127);
	rearLeft = limit(rearLeft, 127, -127);
	rearRight = limit(rearRight, 127, -127);

	setSmartMotor(drive.frontLeftMotor, frontLeft);
	setSmartMotor(drive.frontRightMotor, -frontRight);
	setSmartMotor(drive.rearLeftMotor, rearLeft);
	setSmartMotor(drive.rearRightMotor, -rearRight);

	double speedRatio = (100/160) * (24/18);
	double sin45 = 0.70710678118;

	double magicNumber = speedRatio / sin45;

	int hSpeed = (int) (direction / magicNumber);

	hSpeed = limit(hSpeed, 127, -127);

	if(hSpeed > -20 && hSpeed < 20)
	{
		hSpeed = 0;
	}

	setSmartMotor(drive.middleLeftMotor, hSpeed);
	setSmartMotor(drive.middleRightMotor, hSpeed);
}

void tankDrive(Drive drive, int left, int right)
{
	left = limit(left, 127, -127);
	right = limit(right, 127, -127);

	setSmartMotor(drive.frontLeftMotor, left);
	setSmartMotor(drive.rearLeftMotor, left);
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

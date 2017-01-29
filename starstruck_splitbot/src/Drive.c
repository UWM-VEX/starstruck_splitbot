#include "main.h"

/**
 * Initializes a new drive object composed of six PantherMotors, two encoders and a gyro.
 */
Drive initDrive(PantherMotor frontLeftMotor, PantherMotor frontRightMotor,
		PantherMotor middleLeftMotor, PantherMotor middleRightMotor,
		PantherMotor rearLeftMotor, PantherMotor rearRightMotor,
		Encoder leftEncoder, Encoder rightEncoder, Gyro gyro, int numMotors)
{
	Drive newDrive = {frontLeftMotor, frontRightMotor,
			middleLeftMotor, middleRightMotor,
			rearLeftMotor, rearRightMotor,
			leftEncoder, rightEncoder,
			gyro, numMotors};

	return newDrive;
}

void holonomicDrive(Drive drive, int magnitude, int direction, int rotation)
{
	int frontLeft = magnitude + direction + rotation;
	int frontRight = magnitude - direction + rotation;
	int rearLeft = magnitude - direction - rotation;
	int rearRight = magnitude + direction - rotation;

	frontLeft = limit(frontLeft, 127, -127);
	frontRight = limit(frontRight, 127, -127);
	rearLeft = limit(rearLeft, 127, -127);
	rearRight = limit(rearRight, 127, -127);

	setPantherMotor(drive.frontLeftMotor, frontLeft);
	setPantherMotor(drive.rearLeftMotor, frontRight);
	setPantherMotor(drive.frontRightMotor, rearLeft);
	setPantherMotor(drive.rearRightMotor, rearRight);
}

void tankDrive(Drive drive, int left, int right)
{
	left = limit(left, 127, -127);
	right = limit(right, 127, -127);

	setPantherMotor(drive.frontLeftMotor, left);
	setPantherMotor(drive.rearLeftMotor, left);

	if(drive.numMotors == 6)
	{
		setPantherMotor(drive.middleLeftMotor, left);
		setPantherMotor(drive.middleRightMotor, right);
	}

	setPantherMotor(drive.frontRightMotor, right);
	setPantherMotor(drive.rearRightMotor, right);
}

void arcadeDrive(Drive drive, int magnitude, int rotation)
{
	int left = magnitude + rotation;
	int right = magnitude - rotation;

	left = limit(left, 127, -127);
	right = limit(right, 127, -127);

	tankDrive(drive, left, right);
}

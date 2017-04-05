/*
 * Drive.h
 *
 *  Created on: Feb 25, 2015
 *      Author: Erik
 */

#ifndef DRIVE_H_
#define DRIVE_H_

#include "main.h"

/**
 * Reference type for a two motor drive.
 */
struct Drive{

	SmartMotor* frontLeftMotor;
	SmartMotor* frontRightMotor;
	SmartMotor* middleLeftMotor;
	SmartMotor* middleRightMotor;
	SmartMotor* rearLeftMotor;
	SmartMotor* rearRightMotor;
	Encoder leftEncoder;
	Encoder rightEncoder;
	Gyro gyro;

}typedef Drive;

Drive initDrive(SmartMotor* frontLeftMotor, SmartMotor* frontRightMotor,
		SmartMotor* middleLeftMotor, SmartMotor* middleRightMotor,
		SmartMotor* rearLeftMotor, SmartMotor* rearRightMotor,
		Encoder leftEncoder, Encoder rightEncoder, Gyro gyro);
void tankDrive(Drive drive, int left, int right);
void arcadeDrive(Drive drive, int magnitude, int rotation);

#endif /* DRIVE_H_ */

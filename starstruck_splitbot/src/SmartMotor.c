/*
 * SmartMotor.c
 *
 *  Created on: Mar 2, 2017
 *      Author: Erik
 */

#include "main.h"

SmartMotor* initSmartMotor(int port, int inverted, long rampUpTime)
{
	SmartMotor* newMotor = malloc(sizeof(SmartMotor));

	newMotor->motor = initPantherMotor(port, inverted);
	newMotor->rampUpTime = rampUpTime;
	newMotor->lastSpeed = 0;
	newMotor->lastTime = millis();

	return newMotor;
}

int setSmartMotor(SmartMotor* motor, int speed)
{
	double maxStep = (127.0 / motor->rampUpTime) * (millis() - motor->lastTime);
	motor->lastTime = millis();
	motor->lastSpeed = limitDouble((double) speed, motor->lastSpeed + maxStep, motor->lastSpeed - maxStep);
	int finalSpeed = limit((int) motor->lastSpeed, 127, -127);
	setPantherMotor(motor->motor, finalSpeed);
	return finalSpeed;
}

int getSmartMotor(SmartMotor* motor)
{
	return motor->lastSpeed;
}

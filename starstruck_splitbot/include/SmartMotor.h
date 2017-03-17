/*
 * SmartMotor.h
 *
 *  Created on: Mar 2, 2017
 *      Author: Erik
 */

#ifndef INCLUDE_SMARTMOTOR_H_
#define INCLUDE_SMARTMOTOR_H_

#include "main.h"

struct SmartMotor{

	PantherMotor motor;
	double rampUpTime;
	long lastTime;
	double lastSpeed;

}typedef SmartMotor;

SmartMotor * initSmartMotor(int port, int inverted, long rampUpTime);
int setSmartMotor(SmartMotor* motor, int speed);
int getSmartMotor(SmartMotor* motor);

#endif /* INCLUDE_SMARTMOTOR_H_ */

/*
 * Utilities.h
 *
 *  Created on: Feb 25, 2015
 *      Author: Erik
 */

#ifndef UTILITIES_H_
#define UTILITIES_H_

#define SIN_45 0.70710678118
#define PI 3.14159265359

int limit(int, int, int);
double limitDouble(double num, double max, double min);
int abs(int);
int inDeadBand(int realNum, int desiredNum, int deadBand);
double encoderToInches(double encoderLines, double wheelDiameter);
double absDouble(double num);
int inDeadBand(int realNum, int desiredNum, int deadBand);
int inDeadBandDouble(double realNum, double desiredNum, double deadBand);
int enforceDeadband(int input, int desiredNumber, int deadband);

#endif /* UTILITIES_H_ */

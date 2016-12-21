/*
 * PIDController.h
 *
 *  Created on: Jun 15, 2015
 *      Author: Erik
 */

#ifndef PIDCONTROLLER_H_
#define PIDCONTROLLER_H_

struct PIDController{

	double kP;
	double kI;
	double kD;
	double kF;
	double setPoint;
	double lastError;
	long lastTime;
	double sumOfError;
	double errorEpsilon;
	int lastD;
	long lastDTime;

}typedef PIDController;

PIDController* initPIDController(double kP, double kI, double kD, double kF, double setPoint, double errorEpsilon);
void PIDsetkP(PIDController *controller, double kP);
void PIDsetkI(PIDController *controller, double kP);
void PIDsetkD(PIDController *controller, double kP);
void PIDsetkF(PIDController *controller, double kP);
void PIDsetSetPoint(PIDController *controller, double setPoint);
void PIDsetErrorEpsilon(PIDController *controller, double errorEpsilon);
int PIDgetPContribution(PIDController *controller, double processVariable);
int PIDgetIContribution(PIDController *controller, double processVariable);
int PIDgetDContribution(PIDController *controller, double processVariable);
int PIDgetFContribution(PIDController *controller);
int PIDRunController(PIDController *controller, double processVariable);

#endif /* PIDCONTROLLER_H_ */

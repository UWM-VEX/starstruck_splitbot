/*
 * AutoLiftLock.h
 *
 *  Created on: Nov 10, 2016
 *      Author: Erik
 */

#ifndef INCLUDE_AUTOLIFTLOCK_H_
#define INCLUDE_AUTOLIFTLOCK_H_

struct AutoLiftLock{

	int direction;
	LiftLock * lock;
	int isFinished;

}typedef AutoLiftLock;

AutoLiftLock * initAutoLiftLock(LiftLock * lock, int direction);
void autoLiftLock(AutoLiftLock * step);

#endif /* INCLUDE_AUTOLIFTLOCK_H_ */

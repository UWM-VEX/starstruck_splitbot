/*
 * AutoTippers.h
 *
 *  Created on: Nov 10, 2016
 *      Author: Erik
 */

#ifndef INCLUDE_AUTOTIPPERS_H_
#define INCLUDE_AUTOTIPPERS_H_

struct AutoTippers{

	int direction;
	AntiTippers * tipper;
	int isFinished;

}typedef AutoTippers;

AutoTippers * initAutoTippers(AntiTippers * tippers, int direction);
void autoTippers(AutoTippers * step);

#endif /* INCLUDE_AUTOTIPPERS_H_ */

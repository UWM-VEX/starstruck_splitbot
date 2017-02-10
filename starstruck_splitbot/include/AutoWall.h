/*
 * AutoWall.h
 *
 *  Created on: Feb 9, 2017
 *      Author: Erik
 */

#ifndef INCLUDE_AUTOWALL_H_
#define INCLUDE_AUTOWALL_H_

#include "main.h"

struct AutoWall{

	Wall * wall;
	int type;
	int isFinished;

} typedef AutoWall;

AutoWall * initAutoWall(Wall * wall, int type);
void autoWall(AutoWall * step);

#endif /* INCLUDE_AUTOWALL_H_ */

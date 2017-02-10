/*
 * Wall.h
 *
 *  Created on: Feb 9, 2017
 *      Author: Erik
 */

#ifndef INCLUDE_WALL_H_
#define INCLUDE_WALL_H_

#include "main.h"

#define WALL_DEPLOY HIGH
#define WALL_UNDEPLOY LOW

struct Wall{

	int port1;
	int port2;

} typedef Wall;

Wall * initWall(int port1, int port2);
void deployWall(Wall * wall);
void undeployWall(Wall * wall);

#endif /* INCLUDE_WALL_H_ */

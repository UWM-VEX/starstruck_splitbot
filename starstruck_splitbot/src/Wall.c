/*
 * Wall.c
 *
 *  Created on: Feb 9, 2017
 *      Author: Erik
 */

#include "main.h"

Wall * initWall(int port1, int port2)
{
	Wall * newWall = malloc(sizeof(Wall));

	newWall->port1 = port1;
	newWall->port2 = port2;

	pinMode(port1, OUTPUT);
	pinMode(port2, OUTPUT);

	digitalWrite(port1, WALL_UNDEPLOY);
	digitalWrite(port2, WALL_UNDEPLOY);

	return newWall;
}

void deployWall(Wall * wall)
{
	digitalWrite(wall->port1, WALL_DEPLOY);
	digitalWrite(wall->port2, WALL_DEPLOY);
}

void undeployWall(Wall * wall)
{
	digitalWrite(wall->port1, WALL_UNDEPLOY);
	digitalWrite(wall->port2, WALL_UNDEPLOY);
}

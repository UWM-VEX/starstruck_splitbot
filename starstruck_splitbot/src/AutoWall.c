/*
 * AutoWall.c
 *
 *  Created on: Feb 9, 2017
 *      Author: Erik
 */

#include "main.h"

AutoWall * initAutoWall(Wall * wall, int type)
{
	AutoWall * newStep = malloc(sizeof(AutoWall));

	newStep->wall = wall;
	newStep->type = type;
	newStep->isFinished = 0;

	return newStep;
}

void autoWall(AutoWall * step)
{
	if(step->type == WALL_UNDEPLOY)
	{
		undeployWall(step->wall);
	}
	else
	{
		deployWall(step->wall);
	}

	step->isFinished = autonomousInfo.elapsedTime > 250;
}

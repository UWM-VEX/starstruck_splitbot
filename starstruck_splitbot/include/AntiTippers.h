/*
 * AntiTippers.h
 *
 *  Created on: Nov 10, 2016
 *      Author: Erik
 */

#ifndef INCLUDE_ANTITIPPERS_H_
#define INCLUDE_ANTITIPPERS_H_

struct AntiTippers{

	int port;

}typedef AntiTippers;

AntiTippers * initAntiTippers(int port);

void antiTippersIn(AntiTippers * antiTippers);

void antiTippersOut(AntiTippers * antiTippers);

#endif /* INCLUDE_ANTITIPPERS_H_ */

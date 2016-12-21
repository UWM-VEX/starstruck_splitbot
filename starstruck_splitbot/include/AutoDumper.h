/*
 * AutoDumper.h
 *
 *  Created on: Nov 3, 2016
 *      Author: Erik
 */

#ifndef INCLUDE_AUTODUMPER_H_
#define INCLUDE_AUTODUMPER_H_

struct AutoDumper {

	int isFinished;
	int height;
	Dumper * dumper;

}typedef AutoDumper;

AutoDumper * initAutoDumper(Dumper * dumper, int height);
void autoDumper(AutoDumper * step);

#endif /* INCLUDE_AUTODUMPER_H_ */

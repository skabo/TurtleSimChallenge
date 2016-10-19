/*
 * turtleStarDrawer.h
 *
 *  Created on: Oct 16, 2016
 *      Author: skabo
 */

#ifndef TURTLESTARDRAWER_H_
#define TURTLESTARDRAWER_H_

#include "turtleMotionControl.h"

class turtleStarDrawer {
public:
	turtleStarDrawer(ros::NodeHandle *n);
	virtual ~turtleStarDrawer();

	void drawStar(double lenght, double alpha);

private:
	turtleMotionControl *turtleMotion;
};

#endif /* TURTLESTARDRAWER_H_ */

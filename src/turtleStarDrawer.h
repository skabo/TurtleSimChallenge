/*
 * turtleStarDrawer.h
 *
 *  Created on: Oct 16, 2016
 *      Author: skabo
 */

#ifndef TURTLESTARDRAWER_H_
#define TURTLESTARDRAWER_H_

#include "turtleMotionControl.h"

class turtleStarDrawer
{
public:
	turtleStarDrawer(ros::NodeHandle *n, double starSideLenght, double starPointsAngle);
	virtual ~turtleStarDrawer();

	void pauseDrawing();
	void startDrawing();
private:

	turtleMotionControl *turtleMotion;
	double _starSideLenght;
	double _starPointsAngle;
	bool _alreadyDrawing;

	void drawStar();
};

#endif /* TURTLESTARDRAWER_H_ */

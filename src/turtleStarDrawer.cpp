/*
 * turtleStarDrawer.cpp
 *
 *  Created on: Oct 16, 2016
 *      Author: skabo
 */

#include "turtleStarDrawer.h"

const double PI = 3.14159265359;
const double THETA = (2.0 * PI / 5.0);
const double THETA_2	= (THETA / 2.0);
const double VEL = 1;

turtleStarDrawer::turtleStarDrawer(ros::NodeHandle *n)
{
	turtleMotion = new turtleMotionControl(n);
	turtleMotion->resetTurtle();
}

turtleStarDrawer::~turtleStarDrawer() {
	// TODO Auto-generated destructor stub
}

void turtleStarDrawer::drawStar(double lenght, double alpha)
{
	double R = lenght *(cos(alpha) + sin(alpha) / tan(THETA_2));
	double gamma = THETA + 2 *alpha;

	turtleMotion->setPen(false);
	turtleMotion->rotateTurtle(VEL,PI/2.0,false);
	turtleMotion->moveTurtle(VEL,R);
	turtleMotion->setPen(true);

	turtleMotion->rotateTurtle(VEL,PI-alpha,true);
	turtleMotion->moveTurtle(VEL,lenght);

	turtleMotion->rotateTurtle(VEL,PI-gamma,false);
	turtleMotion->moveTurtle(VEL,lenght);

	turtleMotion->rotateTurtle(VEL,PI-2*alpha,true);
	turtleMotion->moveTurtle(VEL,lenght);

	turtleMotion->rotateTurtle(VEL,PI-gamma,false);
	turtleMotion->moveTurtle(VEL,lenght);

	turtleMotion->rotateTurtle(VEL,PI-2*alpha,true);
	turtleMotion->moveTurtle(VEL,lenght);

	turtleMotion->rotateTurtle(VEL,PI-gamma,false);
	turtleMotion->moveTurtle(VEL,lenght);

	turtleMotion->rotateTurtle(VEL,PI-2*alpha,true);
	turtleMotion->moveTurtle(VEL,lenght);

	turtleMotion->rotateTurtle(VEL,PI-gamma,false);
	turtleMotion->moveTurtle(VEL,lenght);

	turtleMotion->rotateTurtle(VEL,PI+2*alpha,false);
	turtleMotion->moveTurtle(VEL,lenght);

	turtleMotion->rotateTurtle(VEL,PI-gamma,false);
	turtleMotion->moveTurtle(VEL,lenght);
}

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

turtleStarDrawer::turtleStarDrawer(ros::NodeHandle *n, double starSideLenght, double starPointsAngle)
{
	_starPointsAngle = starPointsAngle;
	_starSideLenght = starSideLenght;
	_alreadyDrawing = false;

	turtleMotion = new turtleMotionControl(n);
	turtleMotion->resetTurtle();
}

turtleStarDrawer::~turtleStarDrawer() {
	// TODO Auto-generated destructor stub
}

void turtleStarDrawer::pauseDrawing()
{
	turtleMotion->pauseMovement();
}

void turtleStarDrawer::startDrawing()
{
	turtleMotion->startMovement();
	if(!_alreadyDrawing)
	{
		_alreadyDrawing = true;
		drawStar();
	}
}

void turtleStarDrawer::drawStar()
{
	double R = _starSideLenght *(cos(_starPointsAngle) + sin(_starPointsAngle) / tan(THETA_2));
	double gamma = THETA + _starPointsAngle;

	turtleMotion->setPen(false);
	turtleMotion->rotateTurtle(VEL,PI/2.0,false);
	turtleMotion->moveTurtle(VEL,R);
	turtleMotion->setPen(true);

	turtleMotion->rotateTurtle(VEL,PI-_starPointsAngle/2.0,true);
	turtleMotion->moveTurtle(VEL,_starSideLenght);

	turtleMotion->rotateTurtle(VEL,PI-gamma,false);
	turtleMotion->moveTurtle(VEL,_starSideLenght);

	turtleMotion->rotateTurtle(VEL,PI-_starPointsAngle,true);
	turtleMotion->moveTurtle(VEL,_starSideLenght);

	turtleMotion->rotateTurtle(VEL,PI-gamma,false);
	turtleMotion->moveTurtle(VEL,_starSideLenght);

	turtleMotion->rotateTurtle(VEL,PI-_starPointsAngle,true);
	turtleMotion->moveTurtle(VEL,_starSideLenght);

	turtleMotion->rotateTurtle(VEL,PI-gamma,false);
	turtleMotion->moveTurtle(VEL,_starSideLenght);

	turtleMotion->rotateTurtle(VEL,PI-_starPointsAngle,true);
	turtleMotion->moveTurtle(VEL,_starSideLenght);

	turtleMotion->rotateTurtle(VEL,PI-gamma,false);
	turtleMotion->moveTurtle(VEL,_starSideLenght);

	turtleMotion->rotateTurtle(VEL,PI-_starPointsAngle,true);
	turtleMotion->moveTurtle(VEL,_starSideLenght);

	turtleMotion->rotateTurtle(VEL,PI-gamma,false);
	turtleMotion->moveTurtle(VEL,_starSideLenght);
}

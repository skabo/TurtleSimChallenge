/*
 * turtleMotionControl.cpp
 *
 *  Created on: Oct 16, 2016
 *      Author: skabo
 */

#include "turtleMotionControl.h"
#include <std_srvs/Empty.h>
#include <turtlesim/SetPen.h>

using namespace std;

const double ROS_RATE = 250;
const double MINIMUM_POSITION_ERROR = 0.01;
const double MINIMUM_ANGLE_ERROR = 0.01;

turtleMotionControl::turtleMotionControl(ros::NodeHandle *n)
{

	velPublisher = n->advertise<geometry_msgs::Twist>("/turtle1/cmd_vel",100);
	posSubscriber = n->subscribe("/turtle1/pose",10, &turtleMotionControl::turtlePoseCallback,this);
	resetSrv = n->serviceClient<std_srvs::Empty>("reset");
	setPenSrv = n->serviceClient<turtlesim::SetPen>("/turtle1/set_pen");
}

turtleMotionControl::~turtleMotionControl() {
	// TODO Auto-generated destructor stub
}

void turtleMotionControl::pauseMovement()
{
	isPaused = true;
}

void turtleMotionControl::startMovement()
{
	isPaused = false;
}

void turtleMotionControl::resetTurtle()
{
	std_srvs::Empty empty;
	resetSrv.call(empty);
}

void turtleMotionControl::setPen(bool state)
{
	turtlesim::SetPen srv;
	srv.request.off = !state;
	srv.request.r = 255;
	srv.request.g = 255;
	srv.request.b = 255;
	srv.request.width = 2;
	setPenSrv.call(srv);
}

void turtleMotionControl::turtlePoseCallback(const turtlesim::Pose::ConstPtr & pose_message)
{
	turtlesimPose.x = pose_message->x;
	turtlesimPose.y = pose_message->y;
	turtlesimPose.theta = pose_message->theta;
}

void turtleMotionControl::moveTurtle(double speed, double distance)
{
	geometry_msgs::Twist velMessage;
	double xGoal;
	double yGoal;

	velMessage.linear.x = abs(speed);
	velMessage.linear.y = 0;
	velMessage.linear.z = 0;
	velMessage.angular.x = 0;
	velMessage.angular.y = 0;
	velMessage.angular.z = 0;

	xGoal = turtlesimPose.x + distance * cos(turtlesimPose.theta);
	yGoal = turtlesimPose.y + distance * sin(turtlesimPose.theta);

	ros::Rate loopRate(ROS_RATE);

	do
	{
		if(isPaused)
		{
			velMessage.linear.x = 0;
		}
		else
		{
			velMessage.linear.x = abs(speed);
		}

		velPublisher.publish(velMessage);
		ros::spinOnce();
		loopRate.sleep();

	}while (!hasTurtleReachedPosition(xGoal,yGoal));

	std::cout<<abs(xGoal - turtlesimPose.x)<<" , "<<abs(yGoal - turtlesimPose.y)<<endl;
	std::cout<<"END FORWARD LOOP"<<endl;

	velMessage.linear.x = 0;
	velPublisher.publish(velMessage);
	ros::spinOnce();
}

void turtleMotionControl::rotateTurtle(double angularSpeed, double relativeAngle, bool clockwise)
{
	geometry_msgs::Twist velMessage;
	double absoluteAngleTarget;
	double signedSpeed;

	velMessage.linear.x = 0;
	velMessage.linear.y = 0;
	velMessage.linear.z = 0;
	velMessage.angular.x = 0;
	velMessage.angular.y = 0;

	if(clockwise)
	{
		signedSpeed = -abs(angularSpeed);
		absoluteAngleTarget = turtlesimPose.theta - relativeAngle;
	}
	else
	{
		signedSpeed = abs(angularSpeed);
		absoluteAngleTarget = turtlesimPose.theta + relativeAngle;
	}

	ros::Rate loopRate(ROS_RATE);

	do
	{
		if(isPaused)
		{
			velMessage.angular.z = 0;
		}
		else
		{
			velMessage.angular.z = signedSpeed;
		}

		velPublisher.publish(velMessage);
		ros::spinOnce();
        loopRate.sleep();

	}while(!hasTurtleReachedAngle(absoluteAngleTarget));

	std::cout<<absoluteAngleTarget<<" , "<<turtlesimPose.theta<<" , "<<abs(absoluteAngleTarget - turtlesimPose.theta)<<endl;
	std::cout<<"END ROTATION LOOP"<<endl;

	velMessage.angular.z = 0;
    velPublisher.publish(velMessage);
    ros::spinOnce();
}

bool turtleMotionControl::hasTurtleReachedPosition(double xGoal, double yGoal)
{
	return ((abs(xGoal-turtlesimPose.x) < MINIMUM_POSITION_ERROR) && (abs(yGoal-turtlesimPose.y) < MINIMUM_POSITION_ERROR));
}

bool turtleMotionControl::hasTurtleReachedAngle(double desiredAngle)
{
	return (abs(desiredAngle - turtlesimPose.theta) < MINIMUM_ANGLE_ERROR);
}

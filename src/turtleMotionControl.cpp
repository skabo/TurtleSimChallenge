/*
 * turtleMotionControl.cpp
 *
 *  Created on: Oct 16, 2016
 *      Author: skabo
 */

#include "turtleMotionControl.h"
#include "math.h"
#include <std_srvs/Empty.h>
#include <turtlesim/SetPen.h>

using namespace std;

const double ROS_RATE = 250;


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

	velMessage.linear.x = abs(speed);
	velMessage.linear.y = 0;
	velMessage.linear.z = 0;
	velMessage.angular.x = 0;
	velMessage.angular.y = 0;
	velMessage.angular.z = 0;

	double initialTime = ros::Time::now().toSec();
	double actualDistance = 0;
	double elapsedTime = 0;
	ros::Rate loopRate(ROS_RATE);

	do
	{
		velPublisher.publish(velMessage);
		elapsedTime = ros::Time::now().toSec();
		actualDistance = speed * (elapsedTime - initialTime);
		ros::spinOnce();
		loopRate.sleep();

	}while (abs(actualDistance - distance)>0.01);

	std::cout<<actualDistance<<" , "<<distance<<" , "<<abs(actualDistance - distance)<<endl;
	std::cout<<"END FORWARD LOOP"<<endl;

	velMessage.linear.x = 0;
	velPublisher.publish(velMessage);
	ros::spinOnce();
}

void turtleMotionControl::rotateTurtle(double angularSpeed, double relativeAngle, bool clockwise)
{
	geometry_msgs::Twist velMessage;
	double absoluteAngleTarget;

	velMessage.linear.x = 0;
	velMessage.linear.y = 0;
	velMessage.linear.z = 0;
	velMessage.angular.x = 0;
	velMessage.angular.y = 0;

	if(clockwise)
	{
		velMessage.angular.z = -abs(angularSpeed);
		absoluteAngleTarget = turtlesimPose.theta - relativeAngle;
	}
	else
	{
		velMessage.angular.z = abs(angularSpeed);
		absoluteAngleTarget = turtlesimPose.theta + relativeAngle;
	}

	std::cout<<turtlesimPose.theta<<" , "<<relativeAngle<<endl;

	ros::Rate loopRate(ROS_RATE);

	do
	{
		velPublisher.publish(velMessage);
		ros::spinOnce();
        loopRate.sleep();

	}while(abs(absoluteAngleTarget - turtlesimPose.theta)>0.01);

	std::cout<<absoluteAngleTarget<<" , "<<turtlesimPose.theta<<" , "<<abs(absoluteAngleTarget - turtlesimPose.theta)<<endl;
	std::cout<<"END ROTATION LOOP"<<endl;

	velMessage.angular.z = 0;
    velPublisher.publish(velMessage);
    ros::spinOnce();
}


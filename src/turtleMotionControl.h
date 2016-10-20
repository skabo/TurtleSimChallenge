/*
 * turtleMotionControl.h
 *
 *  Created on: Oct 16, 2016
 *      Author: skabo
 */

#ifndef TURTLEMOTIONCONTROL_H_
#define TURTLEMOTIONCONTROL_H_

#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"

class turtleMotionControl
{
public:
	turtleMotionControl(ros::NodeHandle *n);
	virtual ~turtleMotionControl();

	void moveTurtle(double speed, double distance);
	void rotateTurtle(double angularSpeed, double relativeAngle, bool clockwise);
	void resetTurtle();
	void setPen(bool state);
	void pauseMovement();
	void startMovement();
private:
	void  turtlePoseCallback(const turtlesim::Pose::ConstPtr & pose_message);
	bool hasTurtleReachedPosition(double xGoal, double yGoal);
	bool hasTurtleReachedAngle(double desiredAngle);
	ros::Publisher velPublisher;
	ros::Subscriber posSubscriber;
	turtlesim::Pose turtlesimPose;
	ros::ServiceClient resetSrv;
	ros::ServiceClient setPenSrv;
	bool isPaused;
};

#endif /* TURTLEMOTIONCONTROL_H_ */

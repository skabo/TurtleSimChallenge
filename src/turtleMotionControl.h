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

class turtleMotionControl {
public:
	turtleMotionControl();
	virtual ~turtleMotionControl();

	void moveTurtle(double speed, double distance);
	void rotateTurtle(double angularSpeed, double relativeAngle, bool clockwise);
	void resetTurtle();
	void setPen(bool state);
private:
	void  turtlePoseCallback(const turtlesim::Pose::ConstPtr & pose_message);
	ros::Publisher velPublisher;
	ros::Subscriber posSubscriber;
	turtlesim::Pose turtlesimPose;
	ros::ServiceClient resetSrv;
	ros::ServiceClient setPenSrv;
};

#endif /* TURTLEMOTIONCONTROL_H_ */

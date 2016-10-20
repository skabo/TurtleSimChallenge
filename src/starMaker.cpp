#include "ros/ros.h"
#include "turtleStarDrawer.h"
#include <std_msgs/String.h>

using namespace std;

const double PI = 3.14159265359;
const double STAR_SIDE_LENGHT = 2;
const double STAR_POINTS_ANGLE = 15 * PI / 180.0;

void commanderCallback(const std_msgs::String::ConstPtr& msg);
turtleStarDrawer *drawer;

int main(int argc, char **argv)
{
    ros::init(argc, argv, "starMaker");
    ros::NodeHandle n;

    ros::Subscriber posSubscriber = n.subscribe("commander",10, commanderCallback);

    ROS_INFO("Waiting for android client commands...");

    drawer = new turtleStarDrawer(&n, STAR_SIDE_LENGHT, STAR_POINTS_ANGLE);

    ros::spin();

    return 0;
}

void commanderCallback(const std_msgs::String::ConstPtr& msg)
{
	ROS_INFO("Command received from client: %s", msg->data.c_str());

	if( msg->data == "Start")
	{
		drawer->startDrawing();
	}
	else if(msg->data == "Pause")
	{
		drawer->pauseDrawing();
	}

}

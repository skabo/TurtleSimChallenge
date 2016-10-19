#include "ros/ros.h"
#include "turtleStarDrawer.h"
#include <std_msgs/String.h>

using namespace std;

const double PI = 3.14159265359;
const double STAR_SIDE_LENGHT = 2;

void commanderCallback(const std_msgs::String::ConstPtr& msg);

int main(int argc, char **argv)
{
	double alpha;

    ros::init(argc, argv, "starMaker");
    ros::NodeHandle n;

    ros::Subscriber posSubscriber = n.subscribe("commander",10, commanderCallback);

    turtleStarDrawer *drawer = new turtleStarDrawer(&n);

    std::cout<<"Enter star angle (in degrees): ";
    std::cin>>alpha;

    drawer->drawStar(STAR_SIDE_LENGHT, alpha*PI/180.0);

    ros::spin();

    return 0;
}

void commanderCallback(const std_msgs::String::ConstPtr& msg)
{
	if( msg->data == "Start")
	{
		ROS_INFO("I heard: [%s]", msg->data.c_str());
	}

}

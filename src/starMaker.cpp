#include "ros/ros.h"
#include "turtleStarDrawer.h"


using namespace std;

const double PI = 3.14159265359;
const double STAR_SIDE_LENGHT = 2;

int main(int argc, char **argv)
{
	double alpha;

    ros::init(argc, argv, "starMaker");

    turtleStarDrawer drawer;

    std::cout<<"Enter star angle (in degrees): ";
    std::cin>>alpha;

    drawer.drawStar(STAR_SIDE_LENGHT, alpha*PI/180.0);

    return 0;
}

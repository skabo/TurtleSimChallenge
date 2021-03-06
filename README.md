# TurtleSimChallenge

Building the node:

- Download the code and save it in the catkin workspace src folder (~/catkin_ws/src)
- Make the package with catkin_make (make sure you are in ~/catkin_ws)
  $ catkin_make
- Source the setup.bash ($ source ./devel/setup.bash)

Running the node:

Open a new terminal and execute
$ roscore

In another terminal execute
$ rosrun turtlesim turtlesim_node

Finally, open another terminal and execute
$ rosrun turtlesim_star turtlesim_star_node

At this moment, the node is waiting for a command from the android client node.

Install the android application and launch it. In the first screen enter the rosmaster uri wich is running in the PC, get the uri from the terminal where you lanch the roscore. It´s probably that you will have to replace the name of the server with the IP:

ex:
ROS_MASTER_URI=http://ubuntuOwnRos:11311

And with the ip: http://192.168.1.105:11311

Make sure that the android device and the PC running the master node are both in the same range of IP.

Click the "Connect" button and you will see a second screen with 2 buttons: "Start Drawing" and "Pause Drawing".
Click "Start Drawing" to start turtlesim drawing a star. You can pause and star the drawing whenever you want.

Running from command line:

You can check the topics list with
$ rostopic list -v

And You will see:

Published topics:
 * /turtle1/color_sensor [turtlesim/Color] 1 publisher
 * /rosout [rosgraph_msgs/Log] 3 publishers
 * /rosout_agg [rosgraph_msgs/Log] 1 publisher
 * /commander [std_msgs/String] 1 publisher
 * /turtle1/cmd_vel [geometry_msgs/Twist] 1 publisher
 * /turtle1/pose [turtlesim/Pose] 1 publisher

Subscribed topics:
 * /turtle1/cmd_vel [geometry_msgs/Twist] 1 subscriber
 * /rosout [rosgraph_msgs/Log] 1 subscriber
 * /commander [std_msgs/String] 1 subscriber
 * /turtle1/pose [turtlesim/Pose] 1 subscriber

The /commander topic is of the type std_msgs/String, so you can publish on this topic from command line like this:

To start execution:
$ rostopic pub -1 /commander std_msgs/String Start

To pause:
$ rostopic pub -1 /commander std_msgs/String Pause



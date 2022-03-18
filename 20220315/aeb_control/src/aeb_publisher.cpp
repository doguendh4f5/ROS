 #include "ros/ros.h"
 #include "std_msgs/Int8.h"
 #include "std_msgs/String.h"
  #include "std_msgs/Bool.h"
 #include "sensor_msgs/Range.h"  // ultrasonic sensor message
 #include "geometry_msgs/Twist.h" // cmd_vel

 int main(int argc, char **argv)
 {
	 int count = 0;
	 
	 ros::init(argc, argv, "aeb_publisher");
	
	 ros::NodeHandle n2;
	 
	 ros::Rate loop_rate(10);  // 10
	 
	 ros::Publisher pub = n2.advertise<sensor_msgs::Range>("range2", 1000);
	
	 
	 while(ros::ok())
	 {
		 sensor_msgs::Range msg;
		 pub.publish(msg);
		 
		 loop_rate.sleep();
		 ros::spinOnce();
		 ++count;
		 
	 }
	 return 0;
 }



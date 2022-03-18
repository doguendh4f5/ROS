 #include "ros/ros.h"
 #include "std_msgs/Int8.h"
 #include "std_msgs/String.h"
 #include "std_msgs/Bool.h"  // boolean data
 #include "sensor_msgs/Range.h"  // ultrasonic sensor message
 #include "geometry_msgs/Twist.h" // cmd_vel
 
  std_msgs::Bool flag_AEB;
  geometry_msgs::Twist cmd_vel_msg;
 
 void UltraSonarCallback(const sensor_msgs::Range::ConstPtr&msg)
 {
	 ROS_INFO("Sonar Seq: [%d]", msg->header.seq);
	 ROS_INFO("Sonar Range: [%f]", msg->range);
	 
	 if(msg->range <=1.0)
	 {
		 flag_AEB.data = true;
		 ROS_INFO("AEB Activation : %d", flag_AEB.data);
	 }
	 else
	 {
		 flag_AEB.data = false;
		 ROS_INFO("AEB Activation : %d", flag_AEB.data);
	 }
 }

void CarControlCallback(const geometry_msgs::Twist&msg)
{
	 ROS_INFO("Cmd_vel : linear_x [%f]", msg.linear.x);
	
	 cmd_vel_msg = msg;
	 
	 ROS_INFO("Cmd_vel : linear_x [%f]", cmd_vel_msg.linear.x);
}

void UltraSonarCallback2(const sensor_msgs::Range::ConstPtr&msg)
{
	ROS_INFO("Sonar2 Seq: [%d]", msg->header.seq);
	ROS_INFO("Sonar2 Rnage: [%f]", msg->range);
}

 int main(int argc, char **argv)
 {
	 int count = 0;
	 
	 ros::init(argc, argv, "aeb_controller");
	 
	 ros::NodeHandle n;
	 
	 ros::Subscriber sub = n.subscribe("/range", 1000, UltraSonarCallback);
	 ros::Subscriber sonar_sub = n.subscribe("/RangeSonar1", 1000, UltraSonarCallback2);
	 ros::Subscriber cmd_vel_sub = n.subscribe("/cmd_vel", 10, &CarControlCallback);
	 
	 ros::Publisher pub_cmd_vel = n.advertise<geometry_msgs::Twist>("/ackermann_steering_controller/cmd_vel", 10);
	 ros::Publisher pub_aeb_activation_flag = n.advertise<std_msgs::Bool>("/aeb_activation_flag", 1);
	 
	 ros::Rate loop_rate(10);  // 10
	 
	 while(ros::ok())
	 {
		 if((count%10) == 0)
		 {
			 pub_aeb_activation_flag.publish(flag_AEB);
		 }
		  
		 if(flag_AEB.data == true)
		 {
			cmd_vel_msg.linear.x = 0;
			pub_cmd_vel.publish(cmd_vel_msg);
			ROS_INFO("Cmd_vel : linear_x [%f]", cmd_vel_msg.linear.x);
		 }
		 
		 else
		 {
			 pub_cmd_vel.publish(cmd_vel_msg);
		 }
		 
		 loop_rate.sleep();
		 ros::spinOnce();
		 ++count;
	 }
	 
	 return 0;
 }


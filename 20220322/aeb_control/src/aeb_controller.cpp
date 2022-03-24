 #include "ros/ros.h"
 #include "std_msgs/Int8.h"
 #include "std_msgs/Float32.h"
 #include "std_msgs/String.h"
 #include "std_msgs/Bool.h"  // boolean data
 #include "sensor_msgs/Range.h"  // ultrasonic sensor message
 #include "geometry_msgs/Twist.h" // cmd_vel
 #include "nav_msgs/Odometry.h"
 
  std_msgs::Bool flag_AEB;
  std_msgs::Float32 delta_range;
  std_msgs::Float32 old_sonar_range;
  geometry_msgs::Twist cmd_vel_msg;
  nav_msgs::Odometry now, delta, prev, vel;
  
 
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
	 
	 delta_range.data = (msg->range) - (old_sonar_range.data);
	 ROS_INFO("delta_range : [%f]", delta_range.data);
	 old_sonar_range.data = msg->range; 
	 
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

void odomCallback(const nav_msgs::Odometry& msg)
{
	// ROS_INFO("[NOW] : %.2lf %.2lf", msg.pose.pose.position.x, msg.pose.pose.position.y);
	now.pose.pose.position.x = msg.pose.pose.position.x;
	now.pose.pose.position.y = msg.pose.pose.position.y;
	
	delta.pose.pose.position.x = now.pose.pose.position.x - prev.pose.pose.position.x;
	delta.pose.pose.position.y = now.pose.pose.position.y - prev.pose.pose.position.y;
	
	// ROS_INFO("[DELTA] : %.2lf %.2lf", delta.pose.pose.position.x, delta.pose.pose.position.y);
	
	prev.pose.pose.position.x = now.pose.pose.position.x;
	prev.pose.pose.position.y = now.pose.pose.position.y;
	
	vel.pose.pose.position.x = delta.pose.pose.position.x / 0.02;
	vel.pose.pose.position.y = delta.pose.pose.position.y / 0.02;
	
	ROS_INFO("[Vx, Vy] : %.2lf %.2lf", vel.pose.pose.position.x, vel.pose.pose.position.y);
}

 int main(int argc, char **argv)
 {
	 int count = 0;
	 
	 ros::init(argc, argv, "aeb_controller");
	 
	 ros::NodeHandle n;
	 
	 std::string odom_sub_topic = "/ackermann_steering_controller/odom";
	 
	 ros::Subscriber sub = n.subscribe("/range", 1000, UltraSonarCallback);
	 ros::Subscriber sonar_sub = n.subscribe("/RangeSonar1", 1000, UltraSonarCallback2);
	 ros::Subscriber cmd_vel_sub = n.subscribe("/cmd_vel", 10, &CarControlCallback);
	 ros::Subscriber sub_odom = n.subscribe(odom_sub_topic, 10, &odomCallback);
	 
	 ros::Publisher pub_cmd_vel = n.advertise<geometry_msgs::Twist>("/ackermann_steering_controller/cmd_vel", 10);
	 ros::Publisher pub_aeb_activation_flag = n.advertise<std_msgs::Bool>("/aeb_activation_flag", 1);
	 ros::Publisher pub_delta_range = n.advertise<std_msgs::Float32>("/delta_range", 1000);
	 ros::Publisher pub_odom = n.advertise<geometry_msgs::Twist>("/speed", 10);
	 
	 ros::Rate loop_rate(10);  // 10
	 
	 while(ros::ok())
	 {
		 pub_delta_range.publish(delta_range);
		 pub_odom.publish(vel);
		 
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


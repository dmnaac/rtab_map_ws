#include <ros/ros.h>
#include <tf2_ros/transform_broadcaster.h>
#include <geometry_msgs/TransformStamped.h>
#include <nav_msgs/Odometry.h>

double translation_x;
double translation_y;
double translation_z;
double rotation_x;
double rotation_y;
double rotation_z;
double rotation_w;

void CallBack(const nav_msgs::Odometry::ConstPtr& msg)
{
    double translation_x = msg->pose.pose.position.x;
    double translation_y = msg->pose.pose.position.y;
    double translation_z = msg->pose.pose.position.z;
    double rotation_x = msg->pose.pose.orientation.x;
    double rotation_y = msg->pose.pose.orientation.y;
    double rotation_z = msg->pose.pose.orientation.z;
    double rotation_w = msg->pose.pose.orientation.w;
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "odom_tf_broadcaster");
    ros::NodeHandle nodehandle;
    tf2_ros::TransformBroadcaster broadcaster;
    ros::Subscriber sub = nodehandle.subscribe("/odom", 1, &CallBack);
    
    geometry_msgs::TransformStamped odom_trans;
    odom_trans.header.stamp = ros::Time::now();
    odom_trans.header.frame_id = "laser";
    odom_trans.child_frame_id = "odom_new";

    odom_trans.transform.translation.x = translation_x;
    odom_trans.transform.translation.y = translation_y;
    odom_trans.transform.translation.z = translation_z;
    odom_trans.transform.rotation.x = rotation_x;
    odom_trans.transform.rotation.y = rotation_y;
    odom_trans.transform.rotation.z = rotation_z;
    odom_trans.transform.rotation.w = rotation_w;

    broadcaster.sendTransform(odom_trans);

    ros::spin();
    return 0;
}
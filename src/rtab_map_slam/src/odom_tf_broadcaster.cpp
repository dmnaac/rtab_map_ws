#include <ros/ros.h>
#include <tf2_ros/transform_broadcaster.h>
#include <geometry_msgs/TransformStamped.h>
#include <nav_msgs/Odometry.h>

void CallBack(const nav_msgs::Odometry::ConstPtr& msg)
{
    tf2_ros::TransformBroadcaster broadcaster;
    geometry_msgs::TransformStamped odom_trans;

    double translation_x = msg->pose.pose.position.x;
    double translation_y = msg->pose.pose.position.y;
    double translation_z = msg->pose.pose.position.z;
    double rotation_x = msg->pose.pose.orientation.x;
    double rotation_y = msg->pose.pose.orientation.y;
    double rotation_z = msg->pose.pose.orientation.z;
    double rotation_w = msg->pose.pose.orientation.w;

    odom_trans.header.stamp = ros::Time::now();
    odom_trans.header.frame_id = "odom_combined";
    odom_trans.child_frame_id = "base_footprint";

    odom_trans.transform.translation.x = translation_x;
    odom_trans.transform.translation.y = translation_y;
    odom_trans.transform.translation.z = translation_z;
    odom_trans.transform.rotation.x = rotation_x;
    odom_trans.transform.rotation.y = rotation_y;
    odom_trans.transform.rotation.z = rotation_z;
    odom_trans.transform.rotation.w = rotation_w;

    broadcaster.sendTransform(odom_trans);
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "odom_tf_broadcaster");
    ros::NodeHandle nodehandle;
    ros::Subscriber sub = nodehandle.subscribe("/odom", 10, &CallBack);
    ros::spin();
    return 0;
}
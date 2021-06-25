#include <ros/ros.h>
#include <sensor_msgs/CameraInfo.h>
#include <iostream>


void msgCallback(const sensor_msgs::CameraInfo::ConstPtr &msg) { 
    std::cout << msg->distortion_model << std::endl;
    std::cout << msg->height << std::endl;
    std::cout << msg->width << std::endl;
}


int main (int argc, char** argv) {
    ros::init(argc, argv, "intel_lidar_test");
    ros::NodeHandle nh;

    ros::Subscriber sub = nh.subscribe("/camera/depth/camera_info", 10, msgCallback);
    ros::spin();

    return 0;
}
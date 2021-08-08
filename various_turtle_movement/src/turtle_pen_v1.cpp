#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <turtlesim/TeleportAbsolute.h>
#include <turtlesim/SetPen.h>
#include <std_srvs/Empty.h>
#include <random>
#include <iostream>
using namespace std;

ros::Publisher pub; //전역으로 선언
ros::ServiceClient srvPenClient;

void msgCallback(const geometry_msgs::Twist::ConstPtr &msg) {
    
    // cout << "msg->angular.x " << msg->angular.x << endl;
    // cout << "msg->angular.y " << msg->angular.y << endl;
    // cout << "msg->angular.z " << msg->angular.z << endl;
    // cout << "----------------------------------------\n";
    // cout << "msg->linear.x " << msg->linear.x << endl;
    // cout << "msg->linear.y " << msg->linear.y << endl;
    // cout << "msg->linear.z " << msg->linear.z << endl;
    
    ros::Rate Loop_rate(10);
    int counter = 0;

    turtlesim::SetPen pen;
    //Args: r g b width off

    pen.request.r = 255;
    pen.request.g = 255;
    pen.request.b = 255;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, 255);
    int penWidth = 0;
    while(ros::ok()) {
        geometry_msgs::Twist whirl;
        
        whirl.linear.x = 1.0; //속도 셋팅
        
        //cout << dis(gen) << endl;

        // 마구 잡이 회전
        if (counter % 3 == 0 ) {
            whirl.angular.z = 1.57;
            penWidth++;
            pen.request.r = dis(gen);
            pen.request.g = dis(gen);
            pen.request.b = dis(gen);
            pen.request.width = penWidth;

            if (!srvPenClient.call(pen)) {
            ROS_ERROR("Failed to request to change color");
            }

            if (penWidth == 10) {
                penWidth = 0; //초기화 
            }

        }

        // cout << movingTime << "    ";
        // cout << "counter : " << counter << endl;

        pub.publish(whirl);
        counter++;
        Loop_rate.sleep();
    }
}

int main (int argc, char** argv) {
    ros::init(argc, argv, "turtle_keyboard_pen_v1");
    ros::NodeHandle nh;

    srvPenClient = nh.serviceClient<turtlesim::SetPen>("/turtle1/set_pen");

    ros::Subscriber sub = nh.subscribe("/cmd_vel", 10, msgCallback);
    pub = nh.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10); //publisher
    ros::spin();

    return 0;
}
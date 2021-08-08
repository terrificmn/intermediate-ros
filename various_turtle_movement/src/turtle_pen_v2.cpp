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
ros::ServiceClient srvClient;
int counter=0;

void msgCallback(const geometry_msgs::Twist::ConstPtr &msg) {
    
    // 그냥 출력용
    cout << "msg->angular.x " << msg->angular.x << endl;
    cout << "msg->angular.y " << msg->angular.y << endl;
    cout << "msg->angular.z " << msg->angular.z << endl;
    cout << "----------------------------------------\n";
    cout << "msg->linear.x " << msg->linear.x << endl;
    cout << "msg->linear.y " << msg->linear.y << endl;
    cout << "msg->linear.z " << msg->linear.z << endl;
    
    ros::Rate Loop_rate(10);
    int counter = 0;

    turtlesim::TeleportAbsolute srv;
    turtlesim::SetPen pen;
    //Args: r g b width off

    pen.request.r = 255;
    pen.request.g = 255;
    pen.request.b = 255;

    //랜덤으로 rd변수 만들기
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, 255);
    
    int penWidth = 0;
    // while(ros::ok()) {
        geometry_msgs::Twist whirl;
        
        whirl.linear.x = 1.0; //속도 셋팅
        
        //cout << dis(gen) << endl;
        cout << msg->linear.z;
        cout << "+++++++++++++++++++++++++";

        if (msg->linear.x > 0 && msg->angular.z > 0) {
            pen.request.width = 1;
        } else if (msg->linear.x > 0 && msg->angular.z < 0) {
            pen.request.width = 10;
        } else if (msg->linear.x > 0) {
            pen.request.width = 5;

        } else {
            pen.request.width = 3;
        }

        // 루프 10번이면 
        if (counter % 10 == 0 ) {
            // 위에서 만든 랜덤으로 색 넣어주기
            pen.request.r = dis(gen);
            pen.request.g = dis(gen);
            pen.request.b = dis(gen);

            if (!srvPenClient.call(pen)) {
            ROS_ERROR("Failed to request to change color");
            }
            if (penWidth == 10) {
                penWidth = 0; //초기화 
            }
        }

        pub.publish(whirl);
        pub.publish(*msg);
        counter++;
}

int main (int argc, char** argv) {
    ros::init(argc, argv, "turtle_keyboard_pen_v2");
    ros::NodeHandle nh;
    
    srvPenClient = nh.serviceClient<turtlesim::SetPen>("/turtle1/set_pen");

    ros::Subscriber sub = nh.subscribe("/cmd_vel", 10, msgCallback);
    pub = nh.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10); //publisher
    ros::spin();

    return 0;
}
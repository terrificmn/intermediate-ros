/// 다른 패키지의 msg 를 가져오는 예제 
/// publisher와 subscriber 를 동시에 활용

#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <turtlesim/TeleportAbsolute.h>
#include <iostream>
using namespace std;

ros::Publisher pub; //전역으로 선언

void msgCallback(const geometry_msgs::Twist::ConstPtr &msg) {
    
    cout << "msg->angular.x " << msg->angular.x << endl;
    cout << "msg->angular.y " << msg->angular.y << endl;
    cout << "msg->angular.z " << msg->angular.z << endl;
    cout << "----------------------------------------\n";
    cout << "msg->linear.x " << msg->linear.x << endl;
    cout << "msg->linear.y " << msg->linear.y << endl;
    cout << "msg->linear.z " << msg->linear.z << endl;
    
    const double PI = 3.141592;
    double speed = (13 * PI) / 360;
    
    cout << "speed: " << speed << endl;
    
    while(ros::ok()) {
        geometry_msgs::Twist cir;
        cir.angular.z = - abs(speed);
        cir.linear.x = 0.6;
        pub.publish(cir);
        //ros::spinOnce();
    }
}

int main (int argc, char** argv) {
    ros::init(argc, argv, "turtle_keyboard_cir");
    ros::NodeHandle nh;

    ros::ServiceClient client = nh.serviceClient<turtlesim::TeleportAbsolute>("/turtle1/teleport_absolute");

    // TeleportAbsolute 서비스 서버 이용해서 중심 요청
    turtlesim::TeleportAbsolute srvTeleport;
    srvTeleport.request.x = 5.544445;
    srvTeleport.request.y =  11.000000;
    srvTeleport.request.theta = 0.000000;

    if(client.call(srvTeleport)) {
        ROS_INFO("SENT");
    } else {
        ROS_ERROR("Failed");
    }
    
    ros::Subscriber sub = nh.subscribe("/cmd_vel", 10, msgCallback);
    pub = nh.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10); //publisher
    
    ros::spin();

    return 0;
}
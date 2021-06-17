/// 다른 패키지의 msg 를 가져오는 예제 
/// publisher와 subscriber 를 동시에 활용

#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <turtlesim/TeleportAbsolute.h>
#include <std_srvs/Empty.h>
#include <iostream>
using namespace std;

ros::Publisher pub; //전역으로 선언
int inputLength = 0;  // 사용자 거리 입력

void msgCallback(const geometry_msgs::Twist::ConstPtr &msg) {
    
    // cout << "msg->angular.x " << msg->angular.x << endl;
    // cout << "msg->angular.y " << msg->angular.y << endl;
    // cout << "msg->angular.z " << msg->angular.z << endl;
    // cout << "----------------------------------------\n";
    // cout << "msg->linear.x " << msg->linear.x << endl;
    // cout << "msg->linear.y " << msg->linear.y << endl;
    // cout << "msg->linear.z " << msg->linear.z << endl;
    
    ros::Rate Loop_rate(1);
    int counter = 0;
    int switchCnt = 1;
    const double PI= 3.14159265359;

    while(ros::ok()) {
        geometry_msgs::Twist tri;
        
        tri.linear.x = 1.0; //속도 셋팅
        
        // 시간 구하기 = 거리 / 속도
        double movingTime = (double)inputLength / tri.linear.x;

        // 테스트용
        // cout << movingTime << "    ";
        // cout << "counter : " << counter << endl;
        
        // 최초 시작시에는 0으로 초기화  : 카운터는 시간 만큼 올라가고 초기화 
        if (counter == 0) {
            tri.linear.x = 0.0;
        // 가야할 시간보다 카운터가 작으면  전진
        } else if ((double)counter < movingTime) {
            tri.linear.x = 1.0;
        // 카운터가 시간보다 커지면 다시 초기화 및 거북이 각도 바꾸기
        } else {
            tri.linear.x = 0.0;
            tri.angular.z += (PI / 2.0);
            counter = 0; //카운터 초기화
        } 
        
        //거리 = 속력 x 시간
        
        //속도 = 거리 / 시간 예: km/h  m/s

        pub.publish(tri);
        counter++;
        Loop_rate.sleep();
    }
}

int main (int argc, char** argv) {
    ros::init(argc, argv, "turtle_keyboard_rect");
    ros::NodeHandle nh;

    ros::ServiceClient srvClient = nh.serviceClient<turtlesim::TeleportAbsolute>("/turtle1/teleport_absolute");
    
    cout << "정사각형 변의 길이를 입력하세요: ";
    cin >> inputLength;
    
    // TeleportAbsolute 서비스 서버 이용해서 중심 요청
    turtlesim::TeleportAbsolute srv;
    srv.request.x = 5.544445;
    srv.request.y = 5.544445;
    srv.request.theta = 0.000000;

    // 사용자 입력이 크면 위치 변경 요청
    if (inputLength > 5) {
        srv.request.x = 5.544445 - (inputLength/2);
        srv.request.y = 5.544445 - (inputLength/2);
    }

    srvClient.call(srv);

    ros::ServiceClient clearSrv = nh.serviceClient<std_srvs::Empty>("/clear");
    std_srvs::Empty clearCall;
    clearSrv.call(clearCall);
    
    ros::Subscriber sub = nh.subscribe("/cmd_vel", 10, msgCallback);
    pub = nh.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10); //publisher
    ros::spin();

    return 0;
}
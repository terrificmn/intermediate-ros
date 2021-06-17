/// 다른 패키지의 msg 를 가져오는 예제 
/// publisher와 subscriber 를 동시에 활용

#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <turtlesim/TeleportAbsolute.h>
#include <std_srvs/Empty.h>
#include <iostream>
using namespace std;

ros::Publisher pub; //전역으로 선언
int multipliedInputNum = 0;  // 사용자 거리 입력

void msgCallback(const geometry_msgs::Twist::ConstPtr &msg) {
    
    ros::Rate Loop_rate(10);
    int counter = 0;
    const double PI= 3.14159265359;
    const double R = PI / 2;

    while(ros::ok()) {
        geometry_msgs::Twist tri;

        double spinSpeed = 5;  // 한 바퀴 돌아가는 시간을 정해줌 -- Loop_rate(10)이면 잘 되는데 (1) 오차가 큼
        
        tri.angular.z =  (2.0 * PI) / spinSpeed;
        tri.linear.x = (multipliedInputNum * (2.0 * PI * R)) / spinSpeed;
        
        // 각도는 2 PI == 2 PI가 360도가 된다
        // 거리는 2 PI R  == R 은 원주율의 반절 180도가 R 
        
        //거리 = 속력 x 시간
        //속도 = 거리 / 시간 예: km/h  m/s

        pub.publish(tri);
        counter++;
        Loop_rate.sleep();
    }
}

int main (int argc, char** argv) {
    ros::init(argc, argv, "turtle_keyboard_cir_v2");
    ros::NodeHandle nh;

    ros::ServiceClient srvClient = nh.serviceClient<turtlesim::TeleportAbsolute>("/turtle1/teleport_absolute");
    
    // TeleportAbsolute 서비스 서버 이용해서 중심 요청
    turtlesim::TeleportAbsolute srv;
    // 요청할 처음 좌표 기본 설정해주기
    srv.request.theta = 0.000000;
    srv.request.x = 5.544445;
    srv.request.y = 5.544445;

    cout << "원 크기를 입력해 주세요. 1 ~ 3.5까지 가능합니다 :";
    cin >> multipliedInputNum;

    // 사용자 입력이 크면 위치 변경 요청
    if (multipliedInputNum >= 2.0 && multipliedInputNum < 2.5 ){
        srv.request.y = 3.5;
    
    } else if (multipliedInputNum >= 2.5 && multipliedInputNum <= 3.5) {
        srv.request.y = 0.1;

    } else if (multipliedInputNum > 3.5) {
        multipliedInputNum = 3.5; // 입력이 3.5 보다 크면 최대 치 강제 3.5 설정
        srv.request.y = 0.1;
    } 

    if (!srvClient.call(srv)) {
        // ROS_ERROR 는 일단 빨간색으로 에러 표시해주는 놈인가보다;;; 에러가 났을 때도 체크해주는 것인줄 알았는데;; 아닌듯
        ROS_ERROR("failed to request");
    } 
    
    // /clear 서비스 클라이언트 호출해서 처음에 선 지우기
    // 먼저 turtlesim 켜져있는 상태에서 rosservice list 해보면 그 중에 /clear 란 서비스가 있고
    // rosservice info /clear 를 해보면 타입은 Type: std_srvs/Empty 라고 나온다 
    // 이를 이용해서 핸들러를 이용해서 serviceClient를 지정해주고 std_srvs::Empty /clear가 서비스명이다
    ros::ServiceClient clearSrv = nh.serviceClient<std_srvs::Empty>("/clear");
    std_srvs::Empty clearCall;
    clearSrv.call(clearCall);

    ros::Subscriber sub = nh.subscribe("/cmd_vel", 10, msgCallback);
    pub = nh.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10); //publisher
    ros::spin();

    return 0;
}
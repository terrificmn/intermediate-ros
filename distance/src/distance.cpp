/// 전역변수 버전 

// 텔레옵 실행
// rosrun teleop_twist_keyboard teleop_twist_keyboard.py  
// 그리고 현재 노드도 실행 
// rosrun yh_distance yh_distance

#include "ros/ros.h"
#include <geometry_msgs/Twist.h>
#include <iostream>

ros::Time startTime;
ros::Time endTime;
int firstPushed = 0;
double storeLinearX = 0;

//#include yh_distance/
void callbackTwist (const geometry_msgs::Twist::ConstPtr&msg) {

    // linear.x의 속력 값을 기준으로 값이 0이 아닐 때의 시간과 값이 0이 되었을 때의 시간을
    // ros::Time::now()를 활용하여 체크하고 그 시간 동안의 이동거리를 계산한다
    //long linearX = msg->linear.x;
    
    // 키가 안 눌리고 x가 0이 아니면 시작시간 기록
    if (firstPushed == 0 && msg->linear.x != 0) {
        // 시간 넣어주기 및 초기화 
        startTime = ros::Time::now();
        firstPushed = 1;  // 처음 눌렸으므로 1 값을 준다
        storeLinearX = msg->linear.x;  // 마지막에 비교하기 위해서 저장
        std::cout << "처음 눌렸습니다: 시간을 기록 합니다" << std::endl;

    } else if (msg->linear.x != 0) {
        // 속도 변화가 있을 수도 있으므로 일단 저장 (속도는 w, s 키임)
        storeLinearX = msg->linear.x; 
        std::cout << "이동 중 입니다..." << std::endl;

    } else if (firstPushed == 1 && msg->linear.x == 0) {
        // 마지막 시간 저장
        endTime = ros::Time::now();
        firstPushed = 0; // 멈춤이 눌리면 0으로 초기화

        ros::Duration duration = endTime - startTime;  //durantion ros::Time객체에서 빼게 되면 생김
        std::cout << "멈췄습니다. " << duration.toSec() << " 초 소요 됐습니다." << std::endl;
        std::cout << "이동한 거리는 " << storeLinearX * duration.toSec() << " 입니다." << std::endl;

        ///// 거리구하기 = 속력 * 시간 
        storeLinearX = 0; //초기화
    }
}


int main(int argc, char **argv) {
    ros::init(argc, argv, "sub_distance_norm");
    ros::NodeHandle nh;
    ros::Subscriber sub = nh.subscribe("cmd_vel", 100, callbackTwist);
    ros::spin();
    
    return 0;
}
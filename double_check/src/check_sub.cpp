#include <ros/ros.h>
#include <double_check/topic_switched.h>
#include <iostream>

// topic을 2개로 하는 방식으로 했다면 전역변수로 int data1, data2 를 해놓고 
// 각각의 pub 노드에서 topic을 다르게 해서 (2개를 만든다)
// 그리고 그 2개의 토픽은 현재 subscriber 노드에서 2개로 subscribe로 받아서 
// 2개의 콜백으로 실행을 한다
// 그래서 각각의 콜백함수에서 ( msg->dataPub1 == 1 && msg->dataPub2 ==1)로 비교하면 된다

// 현재는 2개의 노드에서 한개의 topic으로 처리했는데 
// 추후 다시 해보자

void msgCallback (const double_check::topic_switched::ConstPtr&msg) {

    // 3개의 값을 모두 같이 비교해야지 정확한 결과가 나옴 
    if (msg->dataPub1 == msg->dataPub2 == 1) {
        std::cout << "avoidance!!" << std::endl;
    } 
    //ROS_INFO("[odd number] received msg = %d", msg->dataPub1);
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "double_chk_sup"); //node 명 정하기
    ros::NodeHandle nh;

    ros::Subscriber sub_1 = nh.subscribe("double_chk_pub", 10, msgCallback);
    // subscriber2r개 만들기 (topic 2개로 나눠서 받아야 함, 콜백함수로 2개)
    //ros::Subscriber sub_2 = nh.subscribe("double_chk_pub", 10, msgCallback2);
    
    ros::spin();

    return 0;
}
#include <ros/ros.h>
#include <double_check/topic_switched.h>


int main(int argc, char **argv) {
    ros::init(argc, argv, "chk_pub_0point5"); //node 이름 설정
    ros::NodeHandle nh;

    ros::Publisher pub = nh.advertise < double_check::topic_switched >("double_chk_pub", 10);
    ros::Rate loop_rate(2);  //0.5초마다 1번 loop

    double_check::topic_switched msg;

    int pubCheck = 0;
    int count = 0;

    while(ros::ok()) {
        msg.stamp = ros::Time::now();

        //ROS_INFO("send msg = %d", msg.stamp.sec);
        //ROS_INFO("send msg = %d", msg.stamp.nsec);

        //카운트 2의 배수이면 0.5초에 한번씩 돌고 있음
        if (count % 2 == 0) {  //카운트가 바뀔 때마다 보내기
            msg.dataPub1 = 0;
            ROS_INFO("send message = %d", msg.dataPub1);
            
        } else {
            msg.dataPub1 = 1;
            ROS_INFO("send message = %d", msg.dataPub1);
        }
        count++;            
        pub.publish(msg);
        loop_rate.sleep();    
    }

    return 0;
}
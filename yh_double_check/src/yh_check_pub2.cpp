#include <ros/ros.h>
#include <yh_double_check/topic_switched.h>


int main(int argc, char **argv) {
    ros::init(argc, argv, "yh_chk_pub_0point4"); //node 이름 설정
    ros::NodeHandle nh;

    ros::Publisher pub = nh.advertise < yh_double_check::topic_switched >("yh_double_pub", 10);
    ros::Rate loop_rate(10);  //0.1초마다 1번 loop
    // loop_rate(2.5)로 설정해주면 더 편할 수 있음
    // 아래에서 while문 처리할 때 더 쉽게 알고리즘 짤 수 있음
    // 2.5 면 0.4초 마다 1번 loop 그래서 while에서 2개중에 하나로 나눠서 1 ,0 으로 publish할 수있음

    yh_double_check::topic_switched msg;

    int count = 0;
    int countMulti4 = 0;

    while(ros::ok()) {
        msg.stamp = ros::Time::now();
        
        //ROS_INFO("send msg = %d", msg.stamp.sec);
        //ROS_INFO("send msg = %d", msg.stamp.nsec);
        
        //카운트 4가 되었을 때 0.4초 일때만 카운트를 +1씩 해주기
        if (count % 4 == 0) {
            countMulti4++;  // count는 4+ 될 때마다 들어오므로 다 2의 배수가 되버림, 새로 카운터 만들기
            if (countMulti4 % 2 == 0) {  //카운트가 바뀔 때마다 보내기
                msg.dataPub2 = 0;
                ROS_INFO("send msg = %d", msg.dataPub2);
                pub.publish(msg);

            } else {
                msg.dataPub2 = 1;
                ROS_INFO("send msg = %d", msg.dataPub2);
                pub.publish(msg);
            }
        } 
        count++;
        loop_rate.sleep();
    }

    return 0;
}
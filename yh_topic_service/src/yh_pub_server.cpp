#include "ros/ros.h" //ROS 기본 헤더파일 추가하기 - 기본 함수들을 사용하기 위해서
#include "yh_topic_service/pubNumber.h" // 패키지 이름/메세지파일이름.h 
#include "yh_topic_service/addNumber.h"
#include <iostream>

bool calculationCallback(yh_topic_service::addNumber::Request &req, yh_topic_service::addNumber::Response &res) {
    res.result = req.num1 + req.num2;
    
    // 화면에 출력
    std::cout << "request accepted : num1= " << (long int)req.num1 << " num2= " << (long int)req.num2 << std::endl; //%ld 는 long int
    std::cout << "sending back the result: " << (long int)res.result << std::endl;

    return true;  //리턴을 bool 로 선언했음
}


int main(int argc, char **argv) {
    ros::init(argc, argv, "publishServerNum");  // 위의 ros.h 파일을 가져왔기 때문에 ros를 사용할 수 있다
    // init()으로 노드명을 초기화 해준다
    ros::NodeHandle nh; // ROS 시스템과 통신을 위한 노드 핸들을 nh 로 만들어 준다
    ros::Publisher pub = nh.advertise < yh_topic_service::pubNumber >("publishNum", 100);

    ros::ServiceServer server = nh.advertiseService("calculateNum", calculationCallback);

    ros::Rate loop_rate(10); // 루프 주기를 10Hz로 설정 (1초에 반복되는 횟수) : 루프 한번이 0.1초에 한번 돌아간다
    yh_topic_service::pubNumber msg;  //yh_topic_service의 pubNumber 의 내가 만든 메시지 파일 형식으로 msg를 선언해준다

    int count = 0;
    int count_3 = 0; //3씩 올려줄 카운트변수

    while(ros::ok()) { // ros가 실행이 되면 ok()가 활성화가 된다.
        msg.stamp = ros::Time::now();  //현재 시간을 msg 객체의 stamp에 저장
                
        // 10번이면 1초, 3 넣어주기
        if(count % 10 == 0){
            count_3 += 3;
            msg.num1 = count_3;
            
            //ROS_INFO("send msg = %d", msg.stamp.sec);  // ros의 prinft 함수 
            ROS_INFO("send msg **each 1 sec** = %d", msg.num1); // num1 퍼블리싱
            
            // 10 배수면 1초 이기도 하지만, 0.1 초에 해당, 그래서 num2에도 0.1  단위로 넣어주기
            msg.num2 = count;
            ROS_INFO("send msg each 0.1 sec= %d", msg.num2); //num1 퍼블리싱

        } else {  // 10단위 (1초 아닐 시) 에는 num2만 보내기
            msg.num2 = count;
            ROS_INFO("send msg = %d", msg.stamp.sec);  // ros의 prinft 함수 
            ROS_INFO("send msg each 0.1 sec = %d", msg.num2); //num1 퍼블리싱
        }

        pub.publish(msg);  //publish() 함수로 메세지를 발행한다
        loop_rate.sleep();
        ros::spinOnce();

        ++count; // 현재 0.1초에 한번씩 +
    } 

    return 0;
}
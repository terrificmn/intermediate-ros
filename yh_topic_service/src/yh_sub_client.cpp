#include "ros/ros.h"
#include "yh_topic_service/pubNumber.h" // 패키지 이름/메세지파일이름.h 
#include "yh_topic_service/addNumber.h" // 서비스 메시지

#include <iostream>

using namespace std;

ros::ServiceClient *ptrClient; //전역포인터 선언

void msgCallback (const yh_topic_service::pubNumber::ConstPtr&msg) { // 파라미터를 상수 형태로 끊어서 사용하겠다
    // srv 만들어서 각각 subscribe받은 내용을 srv 로 넘겨주기
    yh_topic_service::addNumber srv;
    
    //request에 저장
    srv.request.num1 = msg->num1;  
    srv.request.num2 = msg->num2;  
    
    //cout << srv.request.num1 << "++++srv.request.num1 값+++++" << endl; //테스트용
    //cout << srv.request.num2 << "++++srv.request.num2 값+++++" << endl; //테스트용
    
    // client 만든 것을 dereference 해주기 
    ros::ServiceClient client = (ros::ServiceClient)*ptrClient; 

    cout << "this is message from pulisher" << endl;
    cout << "received msg num1 = " << msg -> num1 << " for 1 second" << endl; //출력
    cout << "received msg num2 = "<< msg -> num2 << " for 0.1 second" << endl;

    //num1이 1초마다 갱신되므로 10초 카운트
    if (msg->num2 % 100 == 0) {

        if(client.call(srv)) {
            cout << endl;
            cout << "this is message from SERVER" << endl;
            cout << "::::::::RECEIVED data : " << srv.response.result <<  " from server :::::::" << endl;
            cout << endl;
        } else {
            ROS_ERROR("Failed to call service");
        }
    }
    
}

int main(int argc, char **argv) {

    ros::init(argc, argv, "subsribeClientNum"); //ros 초기화 하면서 노드명을 만들어 준다
    ros::NodeHandle nh; //NodeHandle 을 nh로 만들어 준다 . 현재 노드에 해당한다

    // 서비스 client 만들기 
    ros::ServiceClient client = nh.serviceClient<yh_topic_service::addNumber>("calculateNum");
    
    // 포인터로 선언 해서 subscriber 콜백함수에서 사용할 수 있게 함
    ptrClient = & client;  // 위에서 선언
    // 포인터 말고도 전역변수로 하는 방법도 있음~  // row::ServiceClient client 를 제일 위에 선언해서 전역변수로 만들어서 
    // 사용하는 방법도 있다 

    // Subscriber 만들기
    ros::Subscriber sub = nh.subscribe("publishNum", 100, msgCallback);  //topic publishNum을 받는다
    
    ros::spin(); // msgCallback 함수를 계속 확인

    return 0;
}
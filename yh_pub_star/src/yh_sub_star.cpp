#include "ros/ros.h"
#include "iostream"
#include "yh_pub_star/yh_topic_star.h"

using namespace std;

void msgCallback (const yh_pub_star::yh_topic_star::ConstPtr&msg) { // 파라미터를 상수 형태로 끊어서 사용하겠다

    // ROS_INFO("received msg = %d", msg -> stamp.sec); //출력
    // ROS_INFO("received msg = %d", msg -> stamp.nsec);
    // ROS_INFO("received msg = %d", msg -> data);

    int countFromPub = msg->data;
    int half = countFromPub / 2;

    cout << "Stars are falling... or my tears are falling?" << endl;

    for (int i=0; i < countFromPub; i++) {

        // pubisher한테 받은 데이터의 반값을 넘어가면 내려가는 for loop을 실행
        if (i < half) {
            
            // 순조롭게 i 까지 반복시키는데 어차피 위의 조건문때문에 i 최대값까지 못찍는다
            for (int j=0; j < i ; j++) {
                cout << '*';    
            }
            cout << endl;
        
        } else {
            // 드디이 별 내려갈 차례  k는 half값으로 지정해서 k--  해줌
            for (int k= half; k > 0 ; k--) {
                cout << "*";    
            }

            cout << endl;    
            half--;  // half는 i 반복문에 들어온 순간부터 계속 고정이므로 임의적으로 --해줘서 half값이 떨어지게 만들어줌
        }

    }
    
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "sub_star"); //ros 초기화 하면서 노드명을 만들어 준다
    ros::NodeHandle nh; //NodeHandle 을 nh로 만들어 준다 . 현재 노드에 해당한다

    //Subscriber 이용해서 sub 객체로 만들어 준다
    //nh.subscribe() 을 사용해서 서브스크라이드를 해주는데 topic은 yh_topic 으로 해준다
    // msgCallback을 호출한다
    ros::Subscriber sub = nh.subscribe("yh_topic_star", 100, msgCallback);

    ros::spin();
    // spin() 함수는 publisher에서 메세지가 있을 때까지 기다린다

    return 0;
}
# 거북이 패키지들
turtlesim을 이용해서 원형, 사각형, 삼각형, 랜덤 움직임등을 표현하는 패키지 입니다.   
각 패키지의 실행법은 아래를 참고해 주세요.

<br/>

# distance 패키지
cmd_vel을 이용해서 키보드가 눌렸을 때, 즉 움직임이 시작되었을 때로부터 다시 멈추는 순간까지   
얼마나 움직였는지 계산하는 노드 입니다.

distance 노드 실행하기
```
rosrun distance distance
```

다른 터미널에서 실행
```
rosrun teleop_twist_keyboard teleop_twist_keyboard.py 
```
키보드 방향키를 눌러서 teleop_twist_keyboard가 실행이 되면 i키를 눌러서 cmd_vel을 publish를 해준다  
k키를 눌러서 멈추게되면 이동한 거리를 구해줍니다.


<br/>

# double_check 패키지
2개의 노드에서 check_pusb1, check_pub2 에서 각각 0.5초, 0.1초 roop_late로 퍼블리싱을 하게 되는데   
이를 check_sub 노드에서 subscribed를 해서 각각 겹치는 타이밍에 avoidance를 출력하는 프로그램 입니다.

런치파일로 쉽게 실행
```
roslaunch double_check double_check.launch
```
쉽게 결과를 볼 수 있음

<br/>

#  star_pubsub 패키지
0.5 초씩 발행되는 토픽 topic_star을 구독을 해서 별을 그리는 프로그램 입니다.  
아래와 같은 별 모양을 출력하게 됩니다.
```
*
**
***
**
*
```

각각 다른 터미널에서 노드를 실행시켜 줍니다.
```
rosrun star_pubsub pub_star
```
아래 실행
```
rosrun star_pubsub sub_star
```

<br/>

# yh_topic_service 패키지
10초마다 service 요청을 하고 클라이언트에게 각 숫자를 더해서 응답하게 되는 노드 입니다.

yh_pub_server 노드는 각 1초 마다 2개의 숫자를 퍼블리싱 하고, 10초에는 숫자 한개만 퍼블리싱하게 됩니다.
그리고 service 요청을 받았을 때 각 숫자를 더해서 응답을 해줍니다.
yh_sub_client 노드는 퍼블리싱 되는 것을 구독하고 10초 마다 서비스 콜을 해줘서 요청을 하게 됩니다.

실행
```
rosrun yh_topic_service yh_pub_server 
```
그리고 다른 터미널에서 실행
```
rosrun yh_topic_service yh_sub_client
```

<br/>

# various_turtle_movement 패키지
turtle_circle, turtle_rectangle, turtle_triangle, turtle_pen_v1 다양한 노드에서 
각각 원형, 사각형, 삼각형 그리고 랜덤 이동을 하는 프로그램 입니다

(turtlesim 노드와 teleop_twist_keyboard 노드를 사용합니다.)

런치파일로 쉽게 실행하기  
원형을 그리는 것은 버전이 2개 있습니다.
```
roslaunch various_turtle_movement turtle_circle_v1.launch
roslaunch various_turtle_movement turtle_circle_v2.launch
```

사각형 실행
```
roslaunch various_turtle_movement turtle_rectangle.launch
```

삼각형 실행
```
roslaunch various_turtle_movement turtle_triangle.launch
```

랜덤 무브먼트는 각 버전이 2개 있습니다.
```
roslaunch various_turtle_movement turtle_pen_v1.launch
roslaunch various_turtle_movement turtle_pen_v2.launch
```
turtle_pen_v2 버전은 런치파일이 실행이 되면 키보드로 조작을 해야합니다.  
i키로 움직이고 u 또는 o 키로 움직여서 회전을 할 때 거북이 경로 표시가   
다르게 표시 됩니다. 나머지는 랜덤으로 색이 표현됩니다.

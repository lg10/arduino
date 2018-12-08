#include <Servo.h>// 声明调用Servo.h库
Servo myservo;// 创建一个舵机对象
int pos=0;
void setup(){
  myservo.attach(6);
}
void loop(){
      myservo.write(180);
       delay(1000);
      myservo.write(-180);
      delay(1000);
}

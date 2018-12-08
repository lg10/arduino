#include <IRremote.h>     // IRremote库声明  
  
int RECV_PIN = 5;        //定义红外接收器的引脚为11  
  
IRrecv irrecv(RECV_PIN);   
  
decode_results results;   //解码结果放在 decode results结构的 result中
    
void setup()  
  {  
      Serial.begin(9600);  
      irrecv.enableIRIn(); // 启动接收器  
  }  
  
void loop() {  
    if (irrecv.decode(&results))//解码成功，收到一组红外讯号   
    {  
      Serial.println(results.value, HEX);//以16进制换行输出接收代码  
      irrecv.resume(); // 接收下一个值  
    }  
    delay(100);  
  }  


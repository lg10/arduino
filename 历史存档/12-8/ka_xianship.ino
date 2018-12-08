
#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <String.h>
#include <Servo.h>
 
#define SS_PIN 10
#define RST_PIN 9
 
MFRC522 rfid(SS_PIN, RST_PIN); //实例化类
//设置LCD1602设备地址
LiquidCrystal_I2C lcd(0x27,16,2);   
// 初始化数组用于存储读取到的NUID 
Servo myservo;// 创建一个舵机对象
byte nuidPICC[4];
int a[4];
//char str[20];
int d[4]={205,117,116,60};
int zph[4]={220,103,225,59};
int lnx[4]={80,24,195,34};
char *xs1;
char *xs2;

//long c=0;
 
void setup() { 
  Serial.begin(9600);
  SPI.begin(); // 初始化SPI总线
  rfid.PCD_Init(); // 初始化 MFRC522 
  lcd.init();                  // 初始化LCD
  lcd.backlight();             //设置LCD背景等亮
  myservo.attach(6);        //设置舵机接口6
}

void qp(){
      lcd.setCursor(0,0);                //设置显示指针
      lcd.print("                  ");     //输出字符到LCD1602上
      lcd.setCursor(0,1);
      lcd.print("                  ");
  }

void xs(){
      lcd.setCursor(0,0);                //设置显示指针
      lcd.print(xs1);     //输出字符到LCD1602上
      lcd.setCursor(0,1);
      lcd.print(xs2);
  }

void dj(){
      myservo.write(180);
       delay(1000);
      myservo.write(-180);
      delay(1000);
}

void loop() {
 
   // 找卡
  if ( ! rfid.PICC_IsNewCardPresent())
    return;
 
  // 验证NUID是否可读
  if ( ! rfid.PICC_ReadCardSerial())
    return;
    MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
 
  // 检查是否MIFARE卡类型
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&  
    piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
    piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
    Serial.println("不支持读取此卡类型");
    return;
  }
  
  // 将NUID保存到nuidPICC数组
  for (byte i = 0; i < 4; i++) {
    nuidPICC[i] = rfid.uid.uidByte[i];
    a[i]=nuidPICC[i];
    //itoa(a[i], str, 10);
    //strcpy(d,str);
    //Serial.print(nuidPICC[i]);
    Serial.println(nuidPICC[i]);
  
  }
  if(a[0]==lnx[0]&&a[1]==lnx[1]&&a[2]==lnx[2]&&a[3]==lnx[3]){
      xs1="Welcome 623";
      xs2="   name:  lnx";
      xs();
      delay(1000);
      dj();
      qp();
      }
   else if(a[0]==zph[0]&&a[1]==zph[1]&&a[2]==zph[2]&&a[3]==zph[3]){
      xs1="Welcome 623";
      xs2="   name:  zph";
      xs();
      delay(1000);
      dj();
      qp();
      }
 else{
      xs1="Error";
      xs2="you can't open";
      xs();
      delay(1000);
      qp();
      }
  Serial.println();
  Serial.print("十六进制UID：");
  printHex(rfid.uid.uidByte, rfid.uid.size);
  Serial.print("十进制UID：");
  printDec(rfid.uid.uidByte, rfid.uid.size);
  Serial.println();
  
  // 使放置在读卡区的IC卡进入休眠状态，不再重复读卡
  rfid.PICC_HaltA();
 
  // 停止读卡模块编码
  rfid.PCD_StopCrypto1();
}
 //正则算法
void printHex(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : "");
    Serial.print(buffer[i], HEX);
  }
}
 
void printDec(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : "");
    Serial.print(buffer[i], DEC);
  }


}

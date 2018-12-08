
#include <SPI.h>
#include <MFRC522.h>
#include <String.h>
 
#define SS_PIN 10
#define RST_PIN 9
 
MFRC522 rfid(SS_PIN, RST_PIN); //实例化类
 
// 初始化数组用于存储读取到的NUID 
byte nuidPICC[4];
int a[4];
//char str[20];
int d[4]={205,117,116,60};
int zph[4]={220,103,225,59};
//long c=0;
 
void setup() { 
  Serial.begin(9600);
  SPI.begin(); // 初始化SPI总线
  rfid.PCD_Init(); // 初始化 MFRC522 
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
    //Serial.println(str[20]);
  
  }
  if(a[0]==d[0]&&a[1]==d[1]&&a[2]==d[2]&&a[3]==d[3]){
      Serial.println("你好！李楠翔");
      }
   else if(a[0]==zph[0]&&a[1]==zph[1]&&a[2]==zph[2]&&a[3]==zph[3]){
      Serial.println("你好！zph");
      }
 else{
       Serial.println("对不起没有你的信息！");
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

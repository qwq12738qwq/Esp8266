#include "DHT11_Simple.h"
#include <Arduino.h>
#include <TFT_eSPI.h>
#include <SPI.h>
#include <cJSON.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <iostream>
#include <DHT.h>
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
TFT_eSPI tft = TFT_eSPI();
WiFiClient Send_Tcp;
// put function declarations here:
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); // 设置频率
  pinMode(2,OUTPUT);
  // 初始化 tft屏幕
  tft.init();
  tft.fillScreen(TFT_BLACK);
  // 初始化链接wifi
  WiFiMode(WIFI_STA);
  // 设置wifi链接名称,密码
  const char* ssid = "vivo S9";
  const char* passwd = "1145141919810";
  
  while (WiFi.status() != WL_CONNECTED)
  {
    WiFi.begin(ssid,passwd);
    delay(10000);
  }
  // 指示灯汇报WIFI链接成功
  int i = 0;
  while (i != 3)
  {
  digitalWrite(2,HIGH);
  delay(500);
  digitalWrite(2,LOW);
  i++;
  delay(10);
  }
  digitalWrite(2,LOW);
}
  


void loop() {
  // 初始关闭灯光
  digitalWrite(2,LOW);
  // 初始化Json数据
  cJSON *Datas = cJSON_CreateObject();
  int T = dht.readTemperature();
  // delay(3000);
  // float H = DHT_Read_H(); // 使用DHT11_Simple.h中的函数
  delay(3000);
  int H = dht.readHumidity();
  cJSON_AddNumberToObject(Datas,"Temperature", T);
  cJSON_AddNumberToObject(Datas, "Humidity", H);
  // cJSON_AddNumberToObject(Datas, "Humidity_New", H_New);
  delay(1000);
  const char* Host_ip = "192.168.227.190";
  const int Post = 8080; 
  // 创建TCP连接
  if (Send_Tcp.connect(Host_ip,Post))
  {
    // TCP连接成功,板载灯常量
    digitalWrite(2,HIGH);
  }
  // 发送Json字符串
  Send_Tcp.println(cJSON_Print(Datas));
  // 关闭连接
  Send_Tcp.stop();
  // 关闭信号灯,表明数据已发送
  digitalWrite(2,LOW);
  delay(100);
  std::cout << "T:" << T << std::endl;
  std::cout << "H:" << H << std::endl;
  cJSON_Delete(Datas);
  delay(60000);
}
// put function definitions here:
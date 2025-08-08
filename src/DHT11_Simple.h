#ifndef DHT11_Simple
#define DHT11_Simple
#include <Arduino.h>
#include <math.h>

class Share
{
    public:
        int InputPin = 4; // 若无定义,则取GPIO4为默认值
        int Bit_Datas[5];
        int i = 0; // 计数变量
        const int n = 8;
        int Humidity_Cache = 0;
        float Humidity = 0.0;
        float Humidity_F = 0.0;
        uint8_t DHT_Server;
};

Share share;

int Read_Bit()
{
    int F = 0;
    while (digitalRead(share.InputPin) == HIGH)
    {
        os_delay_us(1);
        F++;
    }
    os_delay_us(50);
    if (F > 27)
    {
        return 1;
    }
    return 0;
}

uint8_t DHT_Initialization()
{
    pinMode(share.InputPin,OUTPUT); // 调整输出,与DHT11呼应
    // 呼应DHT11
    digitalWrite(share.InputPin, LOW);
    delay(18); // 拉低18ms告知DHT11
    digitalWrite(share.InputPin,HIGH);
    os_delay_us(30);
    pinMode(share.InputPin, INPUT);
    uint8_t Read_Mode = digitalRead(share.InputPin);
    os_delay_us(5); // 5纳秒等待
    // 检测是否高电平
    if (Read_Mode == HIGH)
    {
        return 1;
    }
    while(Read_Mode == LOW) // 等待低电平
    while(Read_Mode == HIGH) // 等待高电平

    printf("1919810\n");
    os_delay_us(50);
    return 0;
}

// int DHT_Read_T()
// {

// }

float DHT_Read_H()
{
    share.Humidity = 0.0; // 重定义变量
    share.Humidity_F = 0.0; // 重定义变量
    share.DHT_Server = DHT_Initialization();
    if (share.DHT_Server == 1)
    {
        return 1;
    }
    printf("114514\n");
    pinMode(share.InputPin,INPUT);
    share.i = 0;
    // 读取整数部分
    while (share.i < 8)
    {
        int Bit = Read_Bit();
        share.i++;
        // 二进制转化十进制
        share.Humidity_Cache = Bit * pow(2,share.n - (share.i + 1));
        share.Humidity = share.Humidity + share.Humidity_Cache;
                
    }
    share.i = 0;
    // 读取小数部分
    while (share.i < 8)
    {
        int Bit = Read_Bit();
        share.i++;
        share.Humidity_Cache = Bit * pow(2,share.n - (share.i + 1));
        share.Humidity_F = share.Humidity_F + share.Humidity_Cache;
    }
    share.Humidity = share.Humidity + (share.Humidity_F / 100); // 整数小数相加
        
    delay(2000);
    return share.Humidity;
}



// int Base2_To_Base10()
// {
    
// }

#endif
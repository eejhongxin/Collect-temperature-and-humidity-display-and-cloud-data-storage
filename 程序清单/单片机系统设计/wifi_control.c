#include "wifi_control.h"
#include "uart.h"
#include "delay.h"

//ESP8266 WIFI发送AT指令
//pbuf：AT指令，字符串格式，如："AT"
void ESP8266_SendCmd(uchar *pbuf)
{
    while(*pbuf!='\0') //遇到空格跳出循环
    {
        UART_SendData(*pbuf);
        delay_us(50);
        pbuf++;
    }
    delay_us(10);
    UART_SendData('\r');//回车
    delay_us(10);
    UART_SendData('\n');//换行
    delay_us(10);
}

//ESP8266 WIFI发送数据到APP
//pbuf：数据
void ESP8266_SendData(uchar *pbuf)
{
    while(*pbuf!='\0') //遇到空格跳出循环
    {
        UART_SendData(*pbuf);
        delay_us(10);
        pbuf++;
    }

}

//ESP8266-WIFI模块工作模式初始化
void ESP8266_ModeInit(void)
{
//    ESP8266_SendCmd("AT+CWMODE=1");//设置路由器模式 1 staTIon模式 2 AP点 路由器模式 3 station+AP混合模式
//	  delay_ms(1000);
//    ESP8266_SendCmd("AT+CWJAP=\"ji\",\"qqaazz112233\"");
//		  delay_ms(1000);
//    ESP8266_SendCmd("AT+CIPSTART=\"TCP\",\"183.230.40.33\",80");
//		  delay_ms(1000);
//    ESP8266_SendCmd("AT+CIPMODE=1");
//		  delay_ms(1000);
//    ESP8266_SendCmd("AT+CIPSEND");
//		  delay_ms(1000);
}

//WIFI控制初始化
void wifi_control_init(void)
{
    UART_Init();
    ESP8266_ModeInit();
//	ES=1;//允许串口中断
}







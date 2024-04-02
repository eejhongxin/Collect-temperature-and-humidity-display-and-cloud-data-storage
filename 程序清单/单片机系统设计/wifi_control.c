#include "wifi_control.h"
#include "uart.h"
#include "delay.h"

//ESP8266 WIFI����ATָ��
//pbuf��ATָ��ַ�����ʽ���磺"AT"
void ESP8266_SendCmd(uchar *pbuf)
{
    while(*pbuf!='\0') //�����ո�����ѭ��
    {
        UART_SendData(*pbuf);
        delay_us(50);
        pbuf++;
    }
    delay_us(10);
    UART_SendData('\r');//�س�
    delay_us(10);
    UART_SendData('\n');//����
    delay_us(10);
}

//ESP8266 WIFI�������ݵ�APP
//pbuf������
void ESP8266_SendData(uchar *pbuf)
{
    while(*pbuf!='\0') //�����ո�����ѭ��
    {
        UART_SendData(*pbuf);
        delay_us(10);
        pbuf++;
    }

}

//ESP8266-WIFIģ�鹤��ģʽ��ʼ��
void ESP8266_ModeInit(void)
{
//    ESP8266_SendCmd("AT+CWMODE=1");//����·����ģʽ 1 staTIonģʽ 2 AP�� ·����ģʽ 3 station+AP���ģʽ
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

//WIFI���Ƴ�ʼ��
void wifi_control_init(void)
{
    UART_Init();
    ESP8266_ModeInit();
//	ES=1;//�������ж�
}







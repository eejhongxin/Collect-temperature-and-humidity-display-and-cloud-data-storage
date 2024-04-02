#include "reg52.h"

#include <intrins.h>
#include "delay.h"
#include "12864.h"
#include "dht11.h"
#include "key.h"
#include "showtemperature.h"
#include "ired.h"
#include "wifi_control.h"
#include "IIc.h"
#define LED_KEY_VALUE		0X45
#define BEEP_KEY_VALUE		0X46
uchar key;
uint flag;//��־λ
sbit wind=P2^2;
uchar ired_buf[3];
uchar key_cnt_led=0;
uchar key_cnt_beep=0;
uchar ired_tempx=0;
uchar ired_tempy=0;
void send_data() {
    ESP8266_SendData("POST /devices/1051580320/datapoints?type=3 HTTP/1.1");
    ESP8266_SendData("\r\n");
    ESP8266_SendData("API-KEY:1ZXQyfKnqL1bqEV0D0JJqbL7pmc=");
    ESP8266_SendData("\r\n");
    ESP8266_SendData("Host:api.heclouds.com");
    ESP8266_SendData("\r\n");
    ESP8266_SendData("Content-Length:24");
    ESP8266_SendData("\r\n");
    ESP8266_SendData("");
    ESP8266_SendData("\r\n");
    ESP8266_SendData("{\"temp\":");
    ESP8266_SendData(wendu);
    ESP8266_SendData(",\"humi\":");
    ESP8266_SendData(shidu);
    ESP8266_SendData("}");
    ESP8266_SendData("\r\n");
    ESP8266_SendData("");
    delay_ms(20);
}
//void time0_init(void)
//{
//    TMOD |= 0X01;//ѡ��Ϊ��ʱ��0ģʽ��������ʽ1
//    TH0 = 0XFC;	//����ʱ������ֵ����ʱ1ms
//    TL0 = 0X18;
//    ET0 = 1;//�򿪶�ʱ��0�ж�����
//    EA = 1;//�����ж�
//    TR0 = 1;//�򿪶�ʱ��
//}
//void time1_init(void)
//{
//    TMOD = 0X10;//ѡ��Ϊ��ʱ��1ģʽ��������ʽ1
//    TH1 = 0XFC;	//����ʱ������ֵ����ʱ1ms
//    TL1 = 0X18;
//    ET1 = 1;//�򿪶�ʱ��0�ж�����
//    EA = 1;//�����ж�
//    TR1 = 1;//�򿪶�ʱ��
//}
void time1_init(void)
{
    TMOD = 0X01;//ѡ��Ϊ��ʱ��1ģʽ��������ʽ1
    TH0 = 0XFC;	//����ʱ������ֵ����ʱ1ms
    TL0 = 0X18;
    ET0 = 1;//�򿪶�ʱ��0�ж�����
    EA = 1;//�����ж�
    TR0 = 1;//�򿪶�ʱ��
}


void main()
{
    time1_init();
    lcd_init();
//    ired_init();//�����ʼ��
    lcd_showstring(0, 0, "2020213373");
    lcd_showstring(0, 1, "������");
     c02_init();
		read_time();
    while(1) {
        key=Keypress();
        settem();
        if (flag==13) {
            lcd_init();
					  save_time();
					    while(flag==13) {
            showtem();
            key=Keypress();
            delay_ms(100);
            DHT11_temget();
//            detect();
		ttop=(temtop[0]-'0')*10+(temtop[1]-'0');
    tlow=(temlow[0]-'0')*10+(temlow[1]-'0');
    htop=(humtop[0]-'0')*10+(humtop[1]-'0');
    hlow=(humlow[0]-'0')*10+(humlow[1]-'0');
    tnow=(wendu[0]-'0')*10+(wendu[1]-'0');
    hnow=(shidu[0]-'0')*10+(shidu[1]-'0');
    if(tnow>=ttop||tnow<=tlow) {
        wind=0;
    }
    else if(tnow<ttop&&tnow>=tlow&&hnow<htop&&hnow>=hlow) {
        wind=1;
    }
    if(hnow>=htop||hnow<=hlow) {
        wind=0;
    }
    else if(tnow<ttop&&tnow>=tlow&&hnow<htop&&hnow>=hlow) {
        wind=1;
    }
				    ESP8266_SendData("{\"temp\":");
    ESP8266_SendData(wendu);
    ESP8266_SendData(",\"humi\":");
    ESP8266_SendData(shidu);
    ESP8266_SendData("}");
    ESP8266_SendData("\r\n");
            if(flag!=13)break;
        }
        }

        if(flag==14) {
            wifi_control_init();
            while (flag==14) {
                key=Keypress();
                send_data();
                DHT11_temget();
                showtem();
		if(tnow>=ttop||tnow<=tlow) {
        wind=0;
    }
    else if(tnow<ttop&&tnow>=tlow&&hnow<htop&&hnow>=hlow) {
        wind=1;
    }
    if(hnow>=htop||hnow<=hlow) {
        wind=0;
    }
    else if(tnow<ttop&&tnow>=tlow&&hnow<htop&&hnow>=hlow) {
        wind=1;
    }
                delay_ms(20);

                if(flag!=14)break;
            }
        }
//        if(flag==15) {
//            ired_init();//�����ʼ��
//            while(flag==15) {
//							key=Keypress();
//					showtem();
//					 detect();
//                ired_tempx=gired_data[2];//�����ֵ
//                if(ired_tempx==LED_KEY_VALUE)//����ǵ�һ������
//                {
//                    gired_data[2]=0;//����,�ȴ��´ΰ�������
//                    key_cnt_led++;
//                    if(key_cnt_led==3)key_cnt_led=1;
//                }
//                while(key_cnt_led==1) {
//                    wind=0;
//                    ired_tempx=gired_data[2];//�����ֵ

//                    if(ired_tempx==LED_KEY_VALUE)//����ǵ�һ������
//                    {
//                        gired_data[2]=0;//����,�ȴ��´ΰ�������
//                        key_cnt_led++;
//                        if(key_cnt_led==3)break;
//                    }
//                }
//            }
//						 if(flag!=15)break;
//        }

    }


}



void time0() interrupt 1  //T0�жϺ�Ϊ
{
    static unsigned int count = 0;
    TH0 = 0XFC;	//����ʱ������ֵ����ʱ1ms
    TL0 = 0X18;
    count++;
    if (count == 3000) {
        lcd_showstring(0, 0, "�¶����ޣ�");
        lcd_showstring(0, 1, "�¶����ޣ�");
        lcd_showstring(0, 2, "ʪ�����ޣ�");
        lcd_showstring(0, 3, "ʪ�����ޣ�");
        ET0 = 0;
    }



}

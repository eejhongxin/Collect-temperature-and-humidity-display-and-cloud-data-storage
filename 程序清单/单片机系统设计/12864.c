#include "reg52.h"
#include <intrins.h>
#include "delay.h"
#include "showtemperature.h"
/*TS12864A-3 �˿ڶ���*/
#define LCD_data  P0             //���ݿ�
#define BASIC_SET  0x30
#define EXTEND_SET 0x34
#define DRAW_ON    0x36
#define DRAW_OFF   0x34
sbit LCD_RS  =  P2^6;            //�Ĵ���ѡ������
sbit LCD_RW  =  P2^5;            //Һ����/д����
sbit LCD_EN  =  P2^7;            //Һ��ʹ�ܿ���
sbit LCD_PSB =  P3^2;            //��/����ʽ����
//sbit wela    =  P2^6;
//sbit dula    =  P2^7;
uchar k,a,b;
#define delayNOP(); {_nop_();_nop_();_nop_();_nop_();};
void delay0(uchar x);  //x*0.14MS
void beep();
void lcd_pos(uchar X,uchar Y);  //ȷ����ʾλ��


/*���LCDæ״̬                                                    */
/*lcd_busyΪ1ʱ��æ���ȴ���lcd-busyΪ0ʱ,�У���дָ�������ݡ�      */
bit lcd_busy()
{
    bit result;
    LCD_RS = 0;
    LCD_RW = 1;
    LCD_EN = 1;
    delayNOP();
    result = (bit)(P0&0x80);
    LCD_EN = 0;
    return(result);
}


/*дָ�����ݵ�LCD                                                  */
/*RS=L��RW=L��E=�����壬D0-D7=ָ���롣                             */
void lcd_wcmd(uchar cmd)
{
    while(lcd_busy());
    LCD_RS = 0;
    LCD_RW = 0;
    LCD_EN = 0;
    _nop_();
    _nop_();
    P0 = cmd;
    delayNOP();
    LCD_EN = 1;
    delayNOP();
    LCD_EN = 0;
}

/*д��ʾ���ݵ�LCD                                                  */
/*RS=H��RW=L��E=�����壬D0-D7=���ݡ�                               */
void lcd_wdat(uchar dat)
{
    while(lcd_busy());
    LCD_RS = 1;
    LCD_RW = 0;
    LCD_EN = 0;
    P0 = dat;
    delayNOP();
    LCD_EN = 1;
    delayNOP();
    LCD_EN = 0;
}


/*  LCD��ʼ���趨                                                  */
void lcd_init()
{

    LCD_PSB = 1;         //���ڷ�ʽ
//    wela=0;
//    dula=0;
    lcd_wcmd(0x34);      //����ָ�����
    delay(5);
    lcd_wcmd(0x30);      //����ָ�����
    delay(5);
    lcd_wcmd(0x0C);      //��ʾ�����ع��
    delay(5);
    lcd_wcmd(0x01);      //���LCD����ʾ����
    delay(5);
}


/* �趨��ʾλ��                                          */
//void lcd_pos(uchar X,uchar Y)
//{
//    X&=0x0f;
//    if (Y==0)
//    {
//        X|=0x80;
//    }
//    else if (Y==1)
//    {
//        X|=0x90;
//    }
//    else if (Y==2)
//    {
//        X|=0x88;
//    }
//    else if (Y==3)
//    {
//        X|=0x98;
//    }
//    lcd_wcmd(X);     //��ʾ��ַ
//}

void lcd_showstring(uchar x,uchar y,uchar *str)
{
    if(y<=0)y=0;
    if(y>3)y=3;
    x&=0x0f;	//����x,y���ܴ�����ʾ��Χ

    switch(y)
    {
    case 0:
        x|=0x80;
        break;//��1�е�ַ+x��ƫ��
    case 1:
        x|=0x90;
        break;//��2�е�ַ+x��ƫ��
    case 2:
        x|=0x88;
        break;//��3�е�ַ+x��ƫ��
    case 3:
        x|=0x98;
        break;//��4�е�ַ+x��ƫ��
    }
    lcd_wcmd(x);
    while(*str!='\0')
    {
        lcd_wdat(*str);
        str++;
    }

}

//uchar read_dat(void)
//{
//    uchar temp;
//    P0 = 0XFF;
////�ͷ�������
//    LCD_RS = 1;
////����
//    LCD_RW = 1;
//// ��ģʽ
//    LCD_EN = 1;
////EΪ�ߵ�ƽ���ж����ݻ�ָ��
//    delay(1);
//    temp = P0;
//    LCD_EN = 0;
//    return temp;
//}

////��ͼ��ʾ������������������ָ���ڻ�ͼʱ�����ã�


//void gui_clear()
//{
//    uchar i, j, k;
//    lcd_wcmd(EXTEND_SET);//��չָ���8λ���ݴ���
//    lcd_wcmd(DRAW_OFF);//��ͼ��ʾ�ر�
//    for(i = 0; i < 2; i ++)//����������д
//    {
//        for(j = 0; j < 32; j ++)
//        {
//            lcd_wcmd(0x80 + j);//дy����
//            delay(1);
//            if(i == 0) //дx����
//            {
//                lcd_wcmd(0x80);
//                delay(1);
//            }
//            else      //д�°���
//            {
//                lcd_wcmd(0x88);
//                delay(1);
//            }
//            for(k = 0; k < 16; k ++)//дһ��������
//            {
//                lcd_wdat(0x00);//д���ֽ�
//                lcd_wdat(0x00);//д���ֽ�
//                delay(1);
//            }

//        }
//    }
//    lcd_wcmd(DRAW_ON);//�򿪻�ͼ��ʾ
//    lcd_wcmd(BASIC_SET);//�򿪻���ָ�
//}
////���������겢���ģ�����λ�ô�㺯��
//void lcd_set_dot(uchar x,uchar y)
//{
//    uchar x_byte,x_bit;   //ȷ�����������һ�ֽ���һλ
//    uchar y_ping, y_bit;     //ȷ�����������һ����һ��
//    uchar tmph, tmpl;    //����������ʱ���������ڴ�Ŷ�����������
//    lcd_wcmd(EXTEND_SET);    //��չָ�
//    lcd_wcmd(DRAW_OFF);        //��ͼ��ʾ�ر�
//    x_byte = x / 16;        //�������һ�ֽڣ�ע��һ����ַ��16λ��
//    x_bit = x % 16;        //& 0x0f;//�������һλ
//    y_ping = y / 32;        //ȷ�����ϰ��������°�����0�����ϰ�����1�����°���
//    y_bit = y % 32;        //& 0x1f;//ȷ���ڵڼ���
//    lcd_wcmd(0X80 + y_bit);//��д��ֱ��ַ�����λ���룩
//    lcd_wcmd(0x80 + x_byte + 8 * y_ping);//ˮƽ���꣬�°���������ʼ��ַΪ0x88����+8*y_ping����������ȷ���ϰ��������°���
//    read_dat();//Ԥ��ȡ����
//    tmph = read_dat();//��ȡ��ǰ��ʾ��8λ����
//    tmpl = read_dat();//��ȡ��ǰ��ʾ��8λ����
//    delay(1);
//    lcd_wcmd(0x80 + y_bit);//��������ı�AC��������������һ��
//    lcd_wcmd(0x80 + x_byte + 8 * y_ping);
//    delay(1);
//    if(x_bit < 8)
//    {
//        lcd_wdat(tmph | (0x01 << (7 - x_bit)));//д���ֽڣ���Ϊ�����Ǵ������ҵģ�GDRAM��λ���򣬵�λ����
//        lcd_wdat(tmpl);//ԭ��λ�����ͻ�
//    }
//    else
//    {
//        lcd_wdat(tmph);//ԭ��λ�����ͻ�
//        lcd_wdat(tmpl | (0x01 << (15 - x_bit)));
//    }
//    lcd_wcmd(DRAW_ON); //�򿪻�ͼ��ʾ
//    lcd_wcmd(BASIC_SET);//�ص�����ָ�
//}
////��ˮƽ�ߺ���
////x0��x1Ϊ��ʼ����յ��ˮƽ���꣬yΪ��ֱ����
////**********************************************************
//void gui_hline(uchar x0, uchar x1, uchar y)
//{
//    uchar bak;//���ڶ��������������м������ʹx1Ϊ��ֵ
//    if(x0 > x1)
//    {
//        bak = x1;
//        x1 = x0;
//        x0 = bak;
//    }
//    do
//    {
//        lcd_set_dot(x0, y); //�����������ʾ
//        x0 ++;
//    }
//    while(x1 >= x0);
//}
////***********����ֱ�ߺ���***********************************//
////xΪ��ʼ����յ��ˮƽ���꣬y0��y1Ϊ��ֱ����***************//
////**********************************************************//
//void gui_rline(uchar x, uchar y0, uchar y1)
//{
//    uchar bak;//���ڶ��������������м������ʹy1Ϊ��ֵ
//    if(y0 > y1)
//    {
//        bak = y1;
//        y1 = y0;
//        y0 = bak;
//    }
//    do
//    {
//        lcd_set_dot(x, y0); //���ϵ��������ʾ
//        y0++;

//    }
//    while(y1 >= y0);
//}
////*********��������仭ֱ��*********************************//
////x0��y0Ϊ��ʼ�����꣬x1��y1Ϊ�յ�����**********************//
////**********************************************************//
//void gui_line(uchar x0, uchar y0, uchar x1, uchar y1)
//{
//    char dx;        //ֱ��x���ֵ
//    char dy;        //ֱ��y���ֵ
//    char dx_sym;        //x����������Ϊ-1ʱ��ֵ����Ϊ1ʱ��ֵ����
//    char dy_sym;        //y����������Ϊ-1ʱ��ֵ����Ϊ1ʱ��ֵ����
//    char dx_x2;        //dx*2ֵ���������ڼӿ������ٶ�
//    char dy_x2;        //dy*2ֵ���������ڼӿ������ٶ�
//    char di;   //���߱���
//    if(x0 == x1)//�ж��Ƿ�Ϊ��ֱ��
//    {
//        gui_rline(x0, y0, y1);  //����ֱ��
//        return;
//    }
//    if(y0 == y1)//�ж��Ƿ�Ϊˮƽ��
//    {
//        gui_hline(x0, x1, y0);  //��ˮƽ��
//        return;
//    }
//    dx = x1 - x0;//��ȡ����֮��Ĳ�ֵ
//    dy = y1 - y0;//****�ж��������򣬻��Ƿ�Ϊˮƽ�ߡ���ֱ�ߡ���*//
//    if(dx > 0)//�ж�x�᷽��
//        dx_sym = 1;
//    else
//    {
//        if(dx < 0)
//            dx_sym = -1;
//        else
//        {
//            gui_rline(x0, y0, y1);
//            return;
//        }
//    }
//    if(dy > 0)//�ж�y�᷽��
//        dy_sym = 1;
//    else
//    {
//        if(dy < 0)
//            dy_sym = -1;
//        else
//        {
//            gui_hline(x0, x1, y0);
//            return;
//        }
//    }
//    /*��dx��dyȡ����ֵ***********/
//    dx = dx_sym * dx;
//    dy = dy_sym * dy;
//    /****����2����dx��dyֵ*******/
//    dx_x2 = dx * 1;//�Ҹ�Ϊ��һ���������Ÿ���ʵ�������Ӧ
//    dy_x2 = dy * 1;    /***ʹ��bresenham�����л�ֱ��***/
//    if(dx >= dy)//����dx>=dy��ʹ��x��Ϊ��׼
//    {
//        di = dy_x2 - dx;
//        while(x0 != x1)
//        {
//            lcd_set_dot(x0,y0);
//            x0 +=dx_sym;
//            if(di < 0)
//                di += dy_x2;//�������һ���ľ���ֵ
//            else
//            {
//                di += dy_x2 - dx_x2;
//                y0 += dy_sym;
//            }
//        }
//        lcd_set_dot(x0, y0);//��ʾ���һ��
//    }
//    else  //����dx<dyʹ��y��Ϊ��׼
//    {
//        di = dx_x2 - dy;
//        while(y0 != y1)
//        {
//            lcd_set_dot(x0, y0);
//            y0 += dy_sym;
//            if(di < 0)
//                di += dx_x2;
//            else
//            {
//                di += dx_x2 - dy_x2;
//                x0 += dx_sym;
//            }
//        }
//        lcd_set_dot(x0, y0);//��ʾ���һ��
//    }
//}


//void display()
//{
//    uint shi,ge;
//    shi=wendu[0]-'0';
//    ge=wendu[1]-'0';
//    if(k==100)
//    {
//        ++i;
//        k=0;
//        if(i>127)
//        {
//            i=0;
//            a=0;
//            b=0;
//            gui_clear();//��ͼʱ��������
//            gui_line(0,15,0,63);
//            gui_line(0,63,127,63);
//        }
//        gui_line(a,63-b,i,63-shi*10-ge);
//        b=shi*10+ge;
//        a=i;
//    }
//}
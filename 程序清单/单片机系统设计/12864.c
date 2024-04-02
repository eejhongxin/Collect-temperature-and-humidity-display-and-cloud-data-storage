#include "reg52.h"
#include <intrins.h>
#include "delay.h"
#include "showtemperature.h"
/*TS12864A-3 端口定义*/
#define LCD_data  P0             //数据口
#define BASIC_SET  0x30
#define EXTEND_SET 0x34
#define DRAW_ON    0x36
#define DRAW_OFF   0x34
sbit LCD_RS  =  P2^6;            //寄存器选择输入
sbit LCD_RW  =  P2^5;            //液晶读/写控制
sbit LCD_EN  =  P2^7;            //液晶使能控制
sbit LCD_PSB =  P3^2;            //串/并方式控制
//sbit wela    =  P2^6;
//sbit dula    =  P2^7;
uchar k,a,b;
#define delayNOP(); {_nop_();_nop_();_nop_();_nop_();};
void delay0(uchar x);  //x*0.14MS
void beep();
void lcd_pos(uchar X,uchar Y);  //确定显示位置


/*检查LCD忙状态                                                    */
/*lcd_busy为1时，忙，等待。lcd-busy为0时,闲，可写指令与数据。      */
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


/*写指令数据到LCD                                                  */
/*RS=L，RW=L，E=高脉冲，D0-D7=指令码。                             */
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

/*写显示数据到LCD                                                  */
/*RS=H，RW=L，E=高脉冲，D0-D7=数据。                               */
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


/*  LCD初始化设定                                                  */
void lcd_init()
{

    LCD_PSB = 1;         //并口方式
//    wela=0;
//    dula=0;
    lcd_wcmd(0x34);      //扩充指令操作
    delay(5);
    lcd_wcmd(0x30);      //基本指令操作
    delay(5);
    lcd_wcmd(0x0C);      //显示开，关光标
    delay(5);
    lcd_wcmd(0x01);      //清除LCD的显示内容
    delay(5);
}


/* 设定显示位置                                          */
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
//    lcd_wcmd(X);     //显示地址
//}

void lcd_showstring(uchar x,uchar y,uchar *str)
{
    if(y<=0)y=0;
    if(y>3)y=3;
    x&=0x0f;	//限制x,y不能大于显示范围

    switch(y)
    {
    case 0:
        x|=0x80;
        break;//第1行地址+x的偏移
    case 1:
        x|=0x90;
        break;//第2行地址+x的偏移
    case 2:
        x|=0x88;
        break;//第3行地址+x的偏移
    case 3:
        x|=0x98;
        break;//第4行地址+x的偏移
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
////释放数据线
//    LCD_RS = 1;
////数据
//    LCD_RW = 1;
//// 读模式
//    LCD_EN = 1;
////E为高电平进行读数据或指令
//    delay(1);
//    temp = P0;
//    LCD_EN = 0;
//    return temp;
//}

////绘图显示的清屏函数（因清屏指令在画图时不能用）


//void gui_clear()
//{
//    uchar i, j, k;
//    lcd_wcmd(EXTEND_SET);//扩展指令集，8位数据传输
//    lcd_wcmd(DRAW_OFF);//绘图显示关闭
//    for(i = 0; i < 2; i ++)//分上下两屏写
//    {
//        for(j = 0; j < 32; j ++)
//        {
//            lcd_wcmd(0x80 + j);//写y坐标
//            delay(1);
//            if(i == 0) //写x坐标
//            {
//                lcd_wcmd(0x80);
//                delay(1);
//            }
//            else      //写下半屏
//            {
//                lcd_wcmd(0x88);
//                delay(1);
//            }
//            for(k = 0; k < 16; k ++)//写一整行数据
//            {
//                lcd_wdat(0x00);//写高字节
//                lcd_wdat(0x00);//写低字节
//                delay(1);
//            }

//        }
//    }
//    lcd_wcmd(DRAW_ON);//打开绘图显示
//    lcd_wcmd(BASIC_SET);//打开基本指令集
//}
////（给定坐标并打点的）任意位置打点函数
//void lcd_set_dot(uchar x,uchar y)
//{
//    uchar x_byte,x_bit;   //确定在坐标的那一字节哪一位
//    uchar y_ping, y_bit;     //确定在坐标的哪一屏哪一行
//    uchar tmph, tmpl;    //定义两个临时变量，用于存放读出来的数据
//    lcd_wcmd(EXTEND_SET);    //扩展指令集
//    lcd_wcmd(DRAW_OFF);        //绘图显示关闭
//    x_byte = x / 16;        //算出在哪一字节，注意一个地址是16位的
//    x_bit = x % 16;        //& 0x0f;//算出在哪一位
//    y_ping = y / 32;        //确定在上半屏还是下半屏，0代表上半屏，1代表下半屏
//    y_bit = y % 32;        //& 0x1f;//确定在第几行
//    lcd_wcmd(0X80 + y_bit);//先写垂直地址（最高位必须）
//    lcd_wcmd(0x80 + x_byte + 8 * y_ping);//水平坐标，下半屏坐标起始地址为0x88，（+8*y_ping）就是用来确定上半屏还是下半屏
//    read_dat();//预读取数据
//    tmph = read_dat();//读取当前显示高8位数据
//    tmpl = read_dat();//读取当前显示低8位数据
//    delay(1);
//    lcd_wcmd(0x80 + y_bit);//读操作会改变AC，所以重新设置一下
//    lcd_wcmd(0x80 + x_byte + 8 * y_ping);
//    delay(1);
//    if(x_bit < 8)
//    {
//        lcd_wdat(tmph | (0x01 << (7 - x_bit)));//写高字节，因为坐标是从左向右的，GDRAM高位在昨，低位在右
//        lcd_wdat(tmpl);//原低位数据送回
//    }
//    else
//    {
//        lcd_wdat(tmph);//原高位数据送回
//        lcd_wdat(tmpl | (0x01 << (15 - x_bit)));
//    }
//    lcd_wcmd(DRAW_ON); //打开绘图显示
//    lcd_wcmd(BASIC_SET);//回到基本指令集
//}
////画水平线函数
////x0、x1为起始点和终点的水平坐标，y为垂直坐标
////**********************************************************
//void gui_hline(uchar x0, uchar x1, uchar y)
//{
//    uchar bak;//用于对两个数互换的中间变量，使x1为大值
//    if(x0 > x1)
//    {
//        bak = x1;
//        x1 = x0;
//        x0 = bak;
//    }
//    do
//    {
//        lcd_set_dot(x0, y); //从左到右逐点显示
//        x0 ++;
//    }
//    while(x1 >= x0);
//}
////***********画竖直线函数***********************************//
////x为起始点和终点的水平坐标，y0、y1为垂直坐标***************//
////**********************************************************//
//void gui_rline(uchar x, uchar y0, uchar y1)
//{
//    uchar bak;//用于对两个数互换的中间变量，使y1为大值
//    if(y0 > y1)
//    {
//        bak = y1;
//        y1 = y0;
//        y0 = bak;
//    }
//    do
//    {
//        lcd_set_dot(x, y0); //从上到下逐点显示
//        y0++;

//    }
//    while(y1 >= y0);
//}
////*********任意两点间画直线*********************************//
////x0、y0为起始点坐标，x1、y1为终点坐标**********************//
////**********************************************************//
//void gui_line(uchar x0, uchar y0, uchar x1, uchar y1)
//{
//    char dx;        //直线x轴差值
//    char dy;        //直线y轴差值
//    char dx_sym;        //x轴增长方向，为-1时减值方向，为1时增值方向
//    char dy_sym;        //y轴增长方向，为-1时减值方向，为1时增值方向
//    char dx_x2;        //dx*2值变量，用于加快运算速度
//    char dy_x2;        //dy*2值变量，用于加快运算速度
//    char di;   //决策变量
//    if(x0 == x1)//判断是否为垂直线
//    {
//        gui_rline(x0, y0, y1);  //画垂直线
//        return;
//    }
//    if(y0 == y1)//判断是否为水平线
//    {
//        gui_hline(x0, x1, y0);  //画水平线
//        return;
//    }
//    dx = x1 - x0;//求取两点之间的差值
//    dy = y1 - y0;//****判断增长方向，或是否为水平线、垂直线、点*//
//    if(dx > 0)//判断x轴方向
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
//    if(dy > 0)//判断y轴方向
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
//    /*将dx、dy取绝对值***********/
//    dx = dx_sym * dx;
//    dy = dy_sym * dy;
//    /****计算2倍的dx、dy值*******/
//    dx_x2 = dx * 1;//我改为了一倍，这样才跟真实的两点对应
//    dy_x2 = dy * 1;    /***使用bresenham法进行画直线***/
//    if(dx >= dy)//对于dx>=dy，使用x轴为基准
//    {
//        di = dy_x2 - dx;
//        while(x0 != x1)
//        {
//            lcd_set_dot(x0,y0);
//            x0 +=dx_sym;
//            if(di < 0)
//                di += dy_x2;//计算出下一步的决策值
//            else
//            {
//                di += dy_x2 - dx_x2;
//                y0 += dy_sym;
//            }
//        }
//        lcd_set_dot(x0, y0);//显示最后一点
//    }
//    else  //对于dx<dy使用y轴为基准
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
//        lcd_set_dot(x0, y0);//显示最后一点
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
//            gui_clear();//画图时清屏函数
//            gui_line(0,15,0,63);
//            gui_line(0,63,127,63);
//        }
//        gui_line(a,63-b,i,63-shi*10-ge);
//        b=shi*10+ge;
//        a=i;
//    }
//}
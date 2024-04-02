#include "reg52.h"
#include <intrins.h>
#include "delay.h"
#include "key.h"
#define keyboard P1
#define KEY1_PRESS	1
#define KEY2_PRESS	2
#define KEY3_PRESS	3
#define KEY4_PRESS	4
#define KEY_UNPRESS	0
uchar func;
uchar Keypress()
{

    uchar temp;
    uchar key;
    uchar KeyDown = 0;
    P1 = 0xF0;
    temp = keyboard;
    temp = temp & 0xF0;
    if (temp != 0xF0)
    {
        delay(10);
        if (temp != 0xf0)
        {
            temp = keyboard;
            temp = temp | 0X0F;
            keyboard = temp;
            key = keyboard;
            switch (key)
            {
            case 0x77:
                KeyDown = 1;
                flag=1;
                break;
            case 0x7B:
                KeyDown = 2;
                flag=2;
                break;
            case 0x7D:
                KeyDown = 3;
                flag=3;
                break;
            case 0x7E:
                KeyDown = 4;
                flag=4;
                break;
            case 0xB7:
                KeyDown = 5;
                flag=5;
                break;
            case 0xBB:
                KeyDown = 6;
                flag=6;
                break;
            case 0xBD:
                KeyDown = 7;
                flag=7;
                break;
            case 0xBE:
                KeyDown = 8;
                flag=8;
                break;
            case 0xD7:
                KeyDown = 9;
                flag=9;
                break;
            case 0xDB:
                KeyDown = 10;
                flag=10;
                break;
            case 0xDD:
                KeyDown = 11;
                flag=11;
                break;
            case 0xDE:
                KeyDown = 12;
                flag=12;
                break;
            case 0xE7:
                KeyDown = 13;
                flag=13;
                break;
            case 0xEB:
                KeyDown = 14;
                flag=14;
                break;
            case 0xED:
                KeyDown = 15;
                flag=15;
                break;
            case 0xEE:
                KeyDown = 16;
                flag=16;
                break;
            default:
                break;
            }
            keyboard = 0xF0;
        }
    }
    return KeyDown;
}




uchar key_scan(uchar mode)
{
    static uchar key=1;

    if(mode)key=1;//连续扫描按键
    if(key==1&&(KEY1==0||KEY2==0||KEY3==0||KEY4==0))//任意按键按下
    {
        delay_ms(10);//消抖
        key=0;
        if(KEY1==0)
            return KEY1_PRESS;
        else if(KEY2==0)
            return KEY2_PRESS;
        else if(KEY3==0)
            return KEY3_PRESS;
        else if(KEY4==0)
            return KEY4_PRESS;
    }
    else if(KEY1==1&&KEY2==1&&KEY3==1&&KEY4==1)	//无按键按下
    {
        key=1;
    }
    return KEY_UNPRESS;
}
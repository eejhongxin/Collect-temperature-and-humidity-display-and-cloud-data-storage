#include "reg52.h"
#include <intrins.h>



/*******************************************************************************
* 函 数 名       : delay_ms
* 函数功能		 : ms延时函数，ms=1时，大约延时1ms
* 输    入       : ms：ms延时时间
* 输    出    	 : 无
*******************************************************************************/
void delay_ms(uint ms)
{
    uint i,j;
    for(i=ms; i>0; i--)
        for(j=110; j>0; j--);
}
void delay(int ms)
{
    while(ms--)
    {
        uchar i;
        for(i=0; i<250; i++)
        {
            _nop_();
            _nop_();
            _nop_();
            _nop_();
        }
    }
}
void delay_us(uchar n)
{
    while(--n);
}
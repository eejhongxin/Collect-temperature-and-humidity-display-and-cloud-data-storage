#include "reg52.h"
#include <intrins.h>



/*******************************************************************************
* �� �� ��       : delay_ms
* ��������		 : ms��ʱ������ms=1ʱ����Լ��ʱ1ms
* ��    ��       : ms��ms��ʱʱ��
* ��    ��    	 : ��
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
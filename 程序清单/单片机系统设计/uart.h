#ifndef _uart_H
#define _uart_H

#include "reg52.h"
#include "stdio.h"


#define UART_REC_LEN  			10  	//定义最大接收字节数 50

extern uchar  UART_RX_BUF[UART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符
extern uint UART_RX_STA;         		//接收状态标记


void UART_Init(void);
void UART_SendData(uchar dat);
void UART_SendString(uchar *pbuf);


#endif

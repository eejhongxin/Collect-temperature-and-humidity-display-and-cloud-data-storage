#ifndef _ired_H
#define _ired_H

#include "reg52.h"
#include <intrins.h>
#include "delay.h"

//�ܽŶ���
sbit IRED=P3^2;

//��������
extern uchar gired_data[4];

//��������
void ired_init(void);

#endif
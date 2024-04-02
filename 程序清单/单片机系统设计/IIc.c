#include "reg52.h"
#include "delay.h"
#include <intrins.h>
#include "showtemperature.h"
sbit sda = P2 ^ 0; //I2C����������
sbit scl = P2 ^ 1; //I2C����ʱ����
void c02_init()  //24c02��ʼ���ӳ���
{
	scl = 1;
	_nop_();
	sda = 1;
	_nop_();
}
void start()        //����I2C����
{
	sda = 1;
	_nop_();
	scl = 1;
	_nop_();
	sda = 0;
	_nop_();
	scl = 0;
	_nop_();
}
void stop()         //ֹͣI2C����
{
	sda = 0;
	_nop_();
	scl = 1;
	_nop_();
	sda = 1;
	_nop_();
}
void writebyte(unsigned char j)  //дһ���ֽ�
{
	unsigned char i, temp;
	temp = j;
	for (i = 0; i < 8; i++)
	{
		temp = temp << 1;
		scl = 0;
		_nop_();
		sda = CY;		//temp����ʱ���Ƴ���ֵ������CY��
		_nop_();
		scl = 1;		//��sda���ϵ������ȶ��󣬽�scl����
		_nop_();
	}
	scl = 0;
	_nop_();
	sda = 1;
	_nop_();
}
unsigned char readbyte()   //��һ���ֽ�
{
	unsigned char i, j, k = 0;
	scl = 0; _nop_(); sda = 1;
	for (i = 0; i < 8; i++)
	{
		_nop_(); scl = 1; _nop_();
		if (sda == 1)
			j = 1;
		else
			j = 0;
		k = (k << 1) | j;
		scl = 0;
	}
	_nop_();
	return(k);
}
void clock()         //I2C����ʱ��
{
	unsigned char i = 0;
	scl = 1;
	_nop_();
	while ((sda == 1) && (i < 255))
		i++;
	scl = 0;
	_nop_();
}
////////��24c02�ĵ�ַaddress�ж�ȡһ���ֽ�����/////
unsigned char read24c02(unsigned char address)
{
	unsigned char i;
	start();
	writebyte(0xa0);
	clock();
	writebyte(address);
	clock();
	start();
	writebyte(0xa1);
	clock();
	i = readbyte();
	stop();
	delay_ms(10);
	return(i);
}
//////��24c02��address��ַ��д��һ�ֽ�����info/////
void write24c02(unsigned char address, unsigned char info)
{
	start();
	writebyte(0xa0);
	clock();
	writebyte(address);
	clock();
	writebyte(info);
	clock();
	stop();
	delay_ms(1000); //�����ʱһ��Ҫ�㹻��������������Ϊ24c02�ڴ�sda��ȡ�����ݺ󣬻���Ҫһ��ʱ�����¼���̡�
}
void save_time()
{
	write24c02(0,temtop[0]);
	delay(5);
	write24c02(1,temtop[1]);
	delay(5);
	write24c02(2,temlow[0]);
	delay(5);
	write24c02(3,temlow[1]);
	delay(5);
		write24c02(4,humtop[0]);
	delay(5);
		write24c02(5,humtop[1]);
	delay(5);
		write24c02(6,humlow[0]);
	delay(5);
		write24c02(7,humlow[1]);
	delay(5);


}
void read_time() {
	temtop[0] = read24c02(0);
	temtop[1] = read24c02(1);
	temlow[0] = read24c02(2);
	temlow[1] = read24c02(3);
	humtop[0] = read24c02(4);
	humtop[1] = read24c02(5);
	humlow[0] = read24c02(6);
	humlow[1] = read24c02(7);

}
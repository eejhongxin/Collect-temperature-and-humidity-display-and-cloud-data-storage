#include "reg52.h"
#include "delay.h"
#include <intrins.h>
#include "showtemperature.h"
sbit sda = P2 ^ 0; //I2C总线数据线
sbit scl = P2 ^ 1; //I2C总线时钟线
void c02_init()  //24c02初始化子程序
{
	scl = 1;
	_nop_();
	sda = 1;
	_nop_();
}
void start()        //启动I2C总线
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
void stop()         //停止I2C总线
{
	sda = 0;
	_nop_();
	scl = 1;
	_nop_();
	sda = 1;
	_nop_();
}
void writebyte(unsigned char j)  //写一个字节
{
	unsigned char i, temp;
	temp = j;
	for (i = 0; i < 8; i++)
	{
		temp = temp << 1;
		scl = 0;
		_nop_();
		sda = CY;		//temp左移时，移出的值放入了CY中
		_nop_();
		scl = 1;		//待sda线上的数据稳定后，将scl拉高
		_nop_();
	}
	scl = 0;
	_nop_();
	sda = 1;
	_nop_();
}
unsigned char readbyte()   //读一个字节
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
void clock()         //I2C总线时钟
{
	unsigned char i = 0;
	scl = 1;
	_nop_();
	while ((sda == 1) && (i < 255))
		i++;
	scl = 0;
	_nop_();
}
////////从24c02的地址address中读取一个字节数据/////
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
//////向24c02的address地址中写入一字节数据info/////
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
	delay_ms(1000); //这个延时一定要足够长，否则会出错。因为24c02在从sda上取得数据后，还需要一定时间的烧录过程。
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
#ifndef __DHT11_H__
#define __DHT11_H__
#define uchar unsigned char
sbit Data=P3^6;
void DHT11_start();
uchar DHT11_rec_byte();
void DHT11_receive();
extern uchar rec_dat[9];
void DHT11_temget();
#endif
#ifndef __KEY_H__
#define __KEY_H__
extern uint flag;
extern uchar key;
extern uchar func;
sbit KEY1=P3^1;
sbit KEY2=P3^0;
sbit KEY3=P3^2;
sbit KEY4=P3^3;
uchar Keypress();
uchar key_scan(uchar mode);

#endif
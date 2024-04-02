#ifndef __SHOWTEMPERATURE_H__
#define __SHOWTEMPERATURE_H__

extern uchar wendu[4];
extern uchar shidu[4];
extern uchar temtop[4];
extern uchar temlow[4];
extern uchar humtop[4];
extern uchar humlow[4];
extern uint ttop,tlow,htop,hlow,tnow,hnow;
extern uchar i;
void showtem();
void settem();
void detect();
#endif


#include "reg52.h"
#include <intrins.h>
#include "delay.h"
#include "12864.h"
#include "dht11.h"
#include "key.h"
#include "showtemperature.h"
#include "wifi_control.h"
#include "IIc.h"

uchar i;
uint ttop,tlow,htop,hlow,tnow,hnow;
sbit beep=P2^5;
sbit wind=P2^1;
uchar number[]="123456789";
uchar temtop[4];
uchar temlow[4];
uchar humtop[4];
uchar humlow[4];
uchar wendu[4];
uchar shidu[4];
void showtem() {

//                lcd_init();
    lcd_showstring(0, 0, "温度：   C");
    lcd_showstring(0, 1, "湿度：   %");
    lcd_showstring(3,0,wendu);
    lcd_showstring(3,1,shidu);
    lcd_showstring(0,2,"上限");
    lcd_showstring(4,2,"C");
    lcd_showstring(7,2,"%");
    lcd_showstring(2,2,temtop);
    lcd_showstring(5,2,humtop);
    lcd_showstring(0,3,"下限");
    lcd_showstring(4,3,"C");
    lcd_showstring(7,3,"%");
    lcd_showstring(2,3,temlow);
    lcd_showstring(5,3,humlow);

}



void settem() {
    uchar func;
    key=Keypress();
    i=0;
    func=key_scan(0);
    if(func==1) {
        while(i<2) {
            key=Keypress();
            delay(10);
            if(key!=0) {
                temtop[i]=number[key-1];
                i++;
                if(i==2) {
                    temtop[i]=' ';
                }
            }
        }
        lcd_showstring(5,0,temtop);
    }
    i=0;
    if(func==2) {
        while(i<2) {
            key=Keypress();
            delay(20);
            if(key!=0) {
                temlow[i]=number[key-1];
                i++;
                if(i==2) {
                    temlow[i]=' ';
                }
            }
        }
        lcd_showstring(5,1,temlow);
    }
    i=0;
    if(func==3) {
        while(i<2) {
            key=Keypress();
            delay(20);
            if(key!=0) {
                humtop[i]=number[key-1];
                i++;
                if(i==2) {
                    humtop[i]=' ';
                }
            }
        }
        lcd_showstring(5,2,humtop);
    }
    i=0;
    if(func==4) {
        while(i<2) {
            key=Keypress();
            delay(20);
            if(key!=0) {
                humlow[i]=number[key-1];
                i++;
                if(i==2) {
                    humlow[i]=' ';
                }
            }
        }
        lcd_showstring(5,3,humlow);
    }

}

void detect() {
    ttop=(temtop[0]-'0')*10+(temtop[1]-'0');
    tlow=(temlow[0]-'0')*10+(temlow[1]-'0');
    htop=(humtop[0]-'0')*10+(humtop[1]-'0');
    hlow=(humlow[0]-'0')*10+(humlow[1]-'0');
    tnow=(wendu[0]-'0')*10+(wendu[1]-'0');
    hnow=(shidu[0]-'0')*10+(shidu[1]-'0');
    if(tnow>=ttop||tnow<=tlow) {
        wind=0;
    }
    else if(tnow<ttop&&tnow>=tlow) {
        wind=1;
    }
    if(hnow>=htop||hnow<=hlow) {
        wind=0;
    }
    else if(hnow<htop&&hnow>=hlow) {
        wind=1;
    }


}

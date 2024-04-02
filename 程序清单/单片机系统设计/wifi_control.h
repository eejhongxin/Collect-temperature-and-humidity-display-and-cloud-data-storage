#ifndef _wifi_control_H
#define _wifi_control_H

#include "reg52.h"


void wifi_control_init(void);
void wifi_control(void);
void ESP8266_SendData(uchar *pbuf);
#endif

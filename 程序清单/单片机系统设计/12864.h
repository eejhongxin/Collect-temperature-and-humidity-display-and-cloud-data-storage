#ifndef __12864_H__
#define __12864_H__
extern uchar k;

bit lcd_busy();
void lcd_wcmd(uchar cmd);
void lcd_wdat(uchar dat);
void lcd_init();
//void lcd_pos(uchar X,uchar Y);
void lcd_showstring(uchar x,uchar y,uchar *str);
#endif
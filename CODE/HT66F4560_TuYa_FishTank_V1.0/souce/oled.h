#ifndef _OLED_H_
#define _OLED_H_
#include "HT66F4560.h"

#define OLED_SCLC  _pac4
#define OLED_SDAC  _pbc5

#define OLED_SCL  _pa4
#define OLED_SDA  _pb5

#define OLED_SDA_PU _pbpu5


#define u8 unsigned char
#define u16 unsigned int

void delay_1us(u8);
void oled_iic_start();
void oled_iic_stop();
u8 oled_iic_wait_ack();
void oled_write_byte(u8);
void oled_write_cmd(u8);
void oled_write_dat(u8);
void oled_set_pos(u8, u8);
u16 oled_pow(u8,u8);
void oled_showchar(u8 ,u8 ,u8 , u8);
void oled_shownum(u8,u8,u16,u8,u8);
void oled_showstring(u8 x,u8 y,char *str,u8 size);
void oled_showphoto(u8 x0, u8 y0,u8 x1, u8 y1,const u8 BMP[]);
void oled_init();
void oled_clear();
void oled_clear_hang(u8);

extern const unsigned char  F6x8[][6];
extern const unsigned char  LOGO_HOLTEK[];
extern const unsigned char  LOGO_VIKING[];


#endif












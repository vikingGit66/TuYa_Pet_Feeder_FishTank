#ifndef _DS1302_H_
#define _DS1302_H_
#include "HT66F4560.h"

#define DS1302_SCLC  _pbc2
#define DS1302_SDAC  _pbc1
#define DS1302_CEC   _pbc3

#define DS1302_SCL  _pb2
#define DS1302_SDA  _pb1
#define DS1302_CE   _pb3



#define WriteSecond	 	0x80
#define	WriteMinute 	0x82
#define	WriteHour	  	0x84
#define	WriteDay		0x86
#define	WriteMonth		0x88
#define	writeWeek		0x8a
#define	writeYear		0x8c

#define	ReadSecond 		0x81
#define	ReadMinute 		0x83
#define	ReadHour	 	0x85
#define	ReadDay	 		0x87
#define	ReadMonth		0x89
#define	ReadWeek 		0x8b
#define	ReadYear 		0x8d


#define year 	0
#define week 	1
#define month 	2
#define day 	3
#define hour 	4
#define min 	5
#define second 	6


void Time_read_turn_Init();
void Time_read_turn_Init_Stm();
void ds1302_init();
//unsigned char hex_to_bcd(unsigned char hex_data);
unsigned char bcd_to_hex(unsigned char bcd_data);
void write_one_byte(unsigned char data);
unsigned char read_one_byte();
void ds1302_write_data(unsigned char reg,unsigned char data);
unsigned char ds1302_read_data(unsigned char reg);
void time_init();
void time_read();
void DS1302_Time_Display();
void DS1302_Key_Set_Time();


extern volatile unsigned char time_Last[7];
extern volatile unsigned char time[7];

#endif





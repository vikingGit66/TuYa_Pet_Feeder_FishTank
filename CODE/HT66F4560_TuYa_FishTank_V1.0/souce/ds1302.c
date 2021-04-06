/*----------------------------------------*/
/*----时钟文件 														*/
/*----版本：V1.0														*/
/*----作者：Viking 												*/
/*----时间：T20200417 											*/
/*----注：																*/
/*----------------------------------------*/

//20200818 芯片慢9秒
//20200818 芯片慢55秒
#include "HT66F4560.H"
#include "ds1302.h"
#include "oled.h"
//#include "key.h"

#define OUT 0
#define IN  1
#define HIGH	1
#define LOW		0

volatile unsigned char time_Last[7];
volatile unsigned char time[7]={0x20,
			0x2,
			0x08,
			0x18,
			0x17,
			0x05,
			0x00
};//年,星期,月,日,时,分,秒

//void delay_us(u8 time)
//{
//	if(time == 1)
//		GCC_DELAY(1);	
//	if(time == 2)
//		GCC_DELAY(3);
//	if(time == 5)
//		GCC_DELAY(6);	
//}
void ds1302_init()
{
	DS1302_SCLC = OUT;
	DS1302_SDAC = OUT;
	DS1302_CEC  = OUT;
	DS1302_SCL  = HIGH;
	DS1302_SDA  = HIGH;//SDA、SCL输出高
	DS1302_CE   = LOW; //CE输出低
	
}
void Time_read_turn_Init_Stm()
{
	unsigned char i = 0 ,j = 0;
	for(i=0 ;i<7;i++)
	{
		j = time[i] / 10;
		time[i] %= 10;
		time[i] = time[i] + j *16;//例如20 -> 0x20 =32
	}
}
void Time_read_turn_Init()
{
	unsigned char i = 0 ,j = 0;
	for(i=0 ;i<7;i++)
	{
		j = time[i] / 10;
		time[i] %= 10;
		time[i] = time[i] + j *16;//例如20 -> 0x20 =32
	}
}
//10进制转16进制
//u8 hex_to_bcd(u8 hex_data)
//{
//	unsigned char temp;
//	temp=(hex_data/10*16 + hex_data%10);
//	return temp;
//}
//16进制转10进制
u8 bcd_to_hex(u8 bcd_data)
{
	unsigned char temp;
	temp=(bcd_data/16*10 + bcd_data%16);
	return temp;
}
//写入一个字节
void write_one_byte(u8 data)
{
	unsigned char i;
	DS1302_SDAC = OUT;
	for(i=0;i<8;i++)
	{
		DS1302_SCL = LOW;
		if(data & 0x01)//从低位开始
		{
			DS1302_SDA = HIGH;
		}
		else
		{
			DS1302_SDA = LOW;
		}
		GCC_DELAY(6);
		DS1302_SCL = HIGH;
		data>>=1;
		GCC_DELAY(1);
	}
}
//读一个字节
unsigned char read_one_byte()
{
	unsigned char i,data   = 0x00;
	DS1302_SDAC = IN;
	for(i=0;i<8;i++)
	{
		DS1302_SCL = HIGH;
		if(DS1302_SDA == 1)
		{
			data|=0x80;
		}
		else
		{
			data&=0x7F;
		}
		GCC_DELAY(6);
		DS1302_SCL = LOW;
		data>>=1;
		GCC_DELAY(1);
	}
	return	data;
}
//ds1302写寄存器写数据
void ds1302_write_data(unsigned char reg,unsigned char data)
{
	DS1302_SCL = LOW;
	DS1302_CE  = LOW;//初始rst为低
	GCC_DELAY(15);
	DS1302_CE  = HIGH;//sck为低时rst才可置高
	GCC_DELAY(15);
	write_one_byte(reg);//sck低到高
	write_one_byte(data);//sck低到高
	DS1302_SCL = HIGH;
	DS1302_CE  = LOW;
	GCC_DELAY(15);
}
//读ds1302寄存器数据 
unsigned char ds1302_read_data(unsigned char reg) 
{
	u8 data_temp;
	DS1302_SCL = LOW;
	DS1302_CE  = LOW;//初始rst为低
	GCC_DELAY(15);
	DS1302_CE  = HIGH;//sck为低时rst才可置高
	GCC_DELAY(15);//2----------------------------------------------
	write_one_byte(reg);//sck低到高
	GCC_DELAY(15);
	data_temp = read_one_byte();//sck由高到低
	DS1302_CE = LOW;
	GCC_DELAY(15);
	return data_temp;
}


//time初始化
void time_init()
{
	ds1302_write_data(0x8e,0x00);//关闭写保护
	ds1302_write_data(writeYear,(time[0]));//写入hex格式数据?
	ds1302_write_data(writeWeek,(time[1]));
	ds1302_write_data(WriteMonth,(time[2]));
	ds1302_write_data(WriteDay,(time[3]));
	ds1302_write_data(WriteHour,(time[4]));
	ds1302_write_data(WriteMinute,(time[5]));//
	ds1302_write_data(WriteSecond,(time[6]));//
	ds1302_write_data(0x8e,0x80);//开启写保护
}

//读取寄存器时间
void time_read()
{
	time[year]	=	bcd_to_hex(ds1302_read_data(ReadYear));
	time[week]	=	bcd_to_hex(ds1302_read_data(ReadWeek));
	time[month]	=	bcd_to_hex(ds1302_read_data(ReadMonth));
	time[day]	=	bcd_to_hex(ds1302_read_data(ReadDay	));
	time[hour]	=	bcd_to_hex(ds1302_read_data(ReadHour));
	time[min]  =	bcd_to_hex(ds1302_read_data(ReadMinute));
	time[second]  =	bcd_to_hex(ds1302_read_data(ReadSecond));
}
//void DS1302_Time_Display()
//{
//	if(SET_Time_Flag_Flag == 0)//WIFI设置时间后，或不处于WIFI设置的时间了
//	{
//		oled_shownum(0,0,20,2,12);
//		oled_shownum(12,0,time[year],2,12);
//		oled_showchar(24,0,'-',12);
//		oled_shownum(30,0,time[month],2,12);
//		oled_showchar(42,0,'-',12);
//		oled_shownum(48,0,time[day],2,12);
//		oled_shownum(70,0,time[hour],2,12);
//		oled_showchar(82,0,':',12);
//		oled_shownum(88,0,time[min],2,12);
//		oled_shownum(110,0,time[second],2,12);
//	}
//	if(SET_Time_Flag_Flag == 1)
//	{
//		oled_shownum(0,0,20,2,12);
//		oled_shownum(12,0, (time[year]/16*10 + time[year]%16),2,12);
//		oled_showchar(24,0,'-',12);
//		oled_shownum(30,0,(time[month]/16*10 + time[month]%16),2,12);
//		oled_showchar(42,0,'-',12);
//		oled_shownum(48,0,(time[day]/16*10 + time[day]%16),2,12);
//		oled_shownum(70,0,(time[hour]/16*10 + time[hour]%16),2,12);
//		oled_showchar(82,0,':',12);
//		oled_shownum(88,0,(time[min]/16*10 + time[min]%16),2,12);
//		oled_shownum(110,0,(time[second]/16*10 + time[second]%16),2,12);
//	}
//	Seg_Num_Is(DShour * 100 + DSminute,4);
//}

//void DS1302_Key_Set_Time()
//{
//	static u8 oled_Up_Time = 0;
//	oled_clear_hang(1);
//	if(Key_set_Fun_Data == 1)	
//	{
//		oled_Up_Time++;
//		switch(Key_set_Matter_Data)
//		{
//			case year : if(oled_Up_Time %2 == 0 )	{oled_showstring(1,1,"===",12);}
//						else						oled_clear_hang(1);
//						break;
//			case month : if(oled_Up_Time %2 == 0 ) {oled_showstring(29,1,"==",12);}
//						else						oled_clear_hang(1);
//						break;
//			case day : if(oled_Up_Time %2 == 0 ) 	{oled_showstring(47,1,"==",12);}
//						else						oled_clear_hang(1);
//						break;
//			case hour : if(oled_Up_Time %2 == 0 ) 	{oled_showstring(69,1,"==",12);}
//						else						oled_clear_hang(1);
//						break;
//			case min : if(oled_Up_Time %2 == 0 ) 	{oled_showstring(87,1,"==",12);}
//						else						oled_clear_hang(1);
//						break;
//			case second : if(oled_Up_Time %2 == 0 ) 	{oled_showstring(109,1,"==",12);}
//						else							oled_showstring(109,1,"  ",12);
//						break;
//			case Time_Init :if(oled_Up_Time %2 == 0 ) 	{oled_showstring(0,1,"===============",12);}//11個
//						else							oled_clear_hang(1);
//						break;
//			default : break;
//		}
//		if(oled_Up_Time ==200)
//			oled_Up_Time = 0;
//	}
//}


















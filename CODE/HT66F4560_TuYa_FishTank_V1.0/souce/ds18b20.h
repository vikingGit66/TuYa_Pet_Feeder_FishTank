#ifndef _DS18B20_H_
#define _DS18B20_H_
#include "HT66F4560.h"

#define DS18B20_IOC _pec4
#define DS18B20_IO  _pe4



void DS18B20_Rst(void);
unsigned char DS18B20_Check(void);
unsigned char DS18B20_Read_Bit(void);
unsigned char DS18B20_Read_Byte(void);
void DS18B20_Write_Byte(unsigned char dat);
void DS18B20_Start(void);
short DS18B20_Get_Temp(void);
void DS18B20_Dispaly();
#endif


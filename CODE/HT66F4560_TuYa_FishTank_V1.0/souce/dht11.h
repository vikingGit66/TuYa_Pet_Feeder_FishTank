#ifndef _DHT11_H_
#define _DHT11_H_
#include "HT66F4560.h"

#define DHT11_IOC  	_pac6
#define DHT11_IO  	_pa6

extern volatile unsigned char temp_N,temp_Dio,hum_N;

void delay_ms(unsigned char time);
void delay_us(unsigned int time);
void DHT11_Rst();
unsigned char DHT11_Check();
unsigned char DHT11_Read_Bit();
unsigned char DHT11_Read_Byte();
void DHT11_Read_Data();
unsigned char DHT11_Init();
void DHT11_Diaplay();
#endif


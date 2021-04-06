/*----------------------------------------*/
/*----温湿度传感器文件 										*/
/*----版本：V1.0														*/
/*----作者：Viking 												*/
/*----时间：T20200416 											*/
/*----注：数据PD3 													*/
/*----------------------------------------*/
#include "HT66F4560.H"
#include "dht11.h"
//#include "oled.h"

volatile unsigned char temp_N,temp_Dio,hum_N;

//extern u8 temp,temp_m,hum;

#define OUT 0
#define IN  1
#define HIGH	1
#define LOW		0

void delay_ms(unsigned char time)//1ms
{
	unsigned char i = 0;
	for(i = time ; i > 0; i--)
	{
		GCC_DELAY(2000);//1ms
	}
}
void delay_us(unsigned int time)
{
	unsigned char i = 0;
	for(i = time ; i > 0; i--)
	{
	}
}
//复位DHT11
void DHT11_Rst()	   
{                 
	unsigned char iii = 0;
	DHT11_IOC = OUT; 	//SET OUTPUT
  	DHT11_IO  = 0; 		//拉低DQ
  	while(iii <= 4)//100us		//拉低至少18ms
	{
		delay_ms(5);
		iii++;
	}
	
  	DHT11_IO = HIGH; 	//DQ=1 
	GCC_DELAY(90);     	//主机拉高20~40us
	DHT11_IOC = IN; 		//SET INPUT	 
}
//等待DHT11的回应
//返回1:未检测到DHT11的存在
//返回0:存在
unsigned char DHT11_Check() 	   
{   
	unsigned char retry = 0;
	DHT11_IOC = IN; //SET INPUT	 
	while (DHT11_IO && retry<80)//DHT11会拉低40~80us
	{
		retry++;
	} 
	if(retry>=80)
	{
		return 1;
	}
	else
	{
		retry = 0;
	}
	while (!DHT11_IO && retry<80)//DHT11拉低后会再次拉高40~80us
	{
		retry++;
	}
	if(retry>=80)
	{
		return 1;
	}
	else
	{
		return 0;
	}
	
}
//从DHT11读取一个位
//返回值：1/0
unsigned char DHT11_Read_Bit() 			 
{
 	unsigned char retry=0;
 	DHT11_IOC = IN; //SET INPUT	
 	
	while( DHT11_IO && retry<100)//等待变为低电平
	{
		retry++;
	}
	retry=0;
	while(!DHT11_IO && retry<100)//等待变高电平
	{
		retry++;
	}
	GCC_DELAY(50);//等待40us
	if(DHT11_IO)return 1;
	else return 0;		   
}
//从DHT11读取一个字节
//返回值：读到的数据
unsigned char DHT11_Read_Byte()    
{        
    unsigned char i,dat;
    dat=0;
	for (i=0;i<8;i++) 
	{
   		dat <<= 1; 
	    dat |= DHT11_Read_Bit();
    }						    
    return dat;
}
//从DHT11读取一次数据
//temp:温度值(范围:0~50°)
//humi:湿度值(范围:20%~90%)
//返回值：0,正常;1,读取失败
//0濕度整數，1濕度小數，2溫度整數，3溫度小數，4校驗和
void DHT11_Read_Data()    
{        
 	unsigned char buf[5];
	unsigned char i;
	DHT11_Rst();
	
	if(DHT11_Check()==0)
	{
		for(i=0;i<5;i++)//读取40位数据
		{
			buf[i]=DHT11_Read_Byte();
		}
		if((buf[0]+buf[1]+buf[2]+buf[3])==buf[4])
		{
			/**h=buf[0];
			*t=buf[2];
			*t_m=buf[3];*/
			
			hum_N		= buf[0];
			temp_N	 	= buf[2];//溫度減兩度offset
			temp_Dio 	= buf[3];
		}
	}
	
		    
}
//初始化DHT11的IO口 DQ 同时检测DHT11的存在
//返回1:不存在
//返回0:存在    	 
unsigned char DHT11_Init()
{
	DHT11_IOC = OUT;
	DHT11_Rst();
	return DHT11_Check();
}

//void DHT11_Diaplay()
//{
//	
//	oled_shownum(0,2,temp,2,12);
//	oled_showchar(12,2,'.',12);
//	oled_shownum(16,2,temp_m,1,12);
//	oled_showchar(22,2,'^',12);
//	oled_showchar(28,2,'C',12);
//	oled_shownum(40,2,hum,2,12);
//	oled_showchar(52,2,'%',12);
//}







/*----------------------------------------*/
/*----温度传感器文件 					  */
/*----版本：V1.0														*/
/*----作者：Viking 												*/
/*----时间：T20200416 											*/
/*----注：T20200416-HT66F2360-一帧数据为5ms,帧频率为200Hz													*/
/*----------------------------------------*/
#include "HT66F4560.H"
#include "ds18b20.h"
#include "oled.h"


#define OUT 0
#define IN  1
#define HIGH	1
#define LOW		0


//复位DS18B20
void DS18B20_Rst(void)	   
{                 
	DS18B20_IOC = OUT; //SET OUTPUT
  	DS18B20_IO  = LOW; //拉低DQ
  	GCC_DELAY(1200);   //480-700us
  	DS18B20_IO  = HIGH; //DQ=1 
	GCC_DELAY(30);     //15us
	
}
//等待DS18B20的回应
//返回1:未检测到DS18B20的存在
//返回0:存在
unsigned char DS18B20_Check(void) 	   
{   
	unsigned char retry=0;
	DS18B20_IOC = IN;//SET PG11 INPUT	 
	//_pepu4 = 1;
    while (DS18B20_IO && retry<200)
	{
		retry++;
		GCC_DELAY(1);
	};	 
	if(retry>=200)return 1;
	else retry=0;
    while (!DS18B20_IO && retry<240)
	{
		retry++;
		//GCC_DELAY(1);
	};
	if(retry>=240)return 1;	    
	return 0;
}
//从DS18B20读取一个位
//返回值：1/0
unsigned char DS18B20_Read_Bit(void) 			 // read one bit
{
  	unsigned char data;
	DS18B20_IOC = OUT;//SET PG11 OUTPUT
  	DS18B20_IO  = LOW; 
	GCC_DELAY(6);//拉低大于1us
//  DS18B20_IO = HIGH; //释放总线
	DS18B20_IOC = IN;//SET PG11 INPUT
	GCC_DELAY(20);//15us内读取总线数据
	if(DS18B20_IO)
		data = 1;
  	else 
  		data = 0;
  	return data;
}
//从DS18B20读取一个字节
//返回值：读到的数据
unsigned char DS18B20_Read_Byte(void)    // read one byte
{        
    unsigned char i,dat;
    dat = 0;
	for (i=0;i<8;i++) 
	{
//        j = DS18B20_Read_Bit();//合并8次数据
//        dat = (j << 7) | (dat >> 1);
		dat >>= 1;
		if(DS18B20_Read_Bit() == 1)
		{
			dat |= 0x80;
			
		}
		GCC_DELAY(150); //等待一共大于60us  //从DS18B20_Read_Bit函数移过来解决问题
    }		
				    
    return dat;
}
//写一个字节到DS18B20
//dat：要写入的字节
void DS18B20_Write_Byte(u8 dat)     
 {             
    unsigned char j;
    unsigned char testb;
	DS18B20_IOC = OUT;//SET PG11 OUTPUT;
    for (j=1;j<=8;j++) 
	{
        testb = dat & 0x01;//数据最低位
        dat >>= 1;//右移一位，更新最低位
        if (testb == 1) //最低位为1
        {
            DS18B20_IO = LOW;// Write 1
            GCC_DELAY(6);   //至少1us恢复时间                        
            DS18B20_IO = HIGH;
            GCC_DELAY(120);     //60us        
        }
        else 
        {
            DS18B20_IO = LOW;// Write 0
            GCC_DELAY(150);     //60us-120us        
            DS18B20_IO = HIGH;
            GCC_DELAY(6);                         
        }
    }
}
//开始温度转换
void DS18B20_Start(void)// ds1820 start convert
{   						               
    DS18B20_Rst();	  
    DS18B20_Check(); 
		 
    DS18B20_Write_Byte(0xcc);// skip rom，跳过ROM匹配
    DS18B20_Write_Byte(0x44);// convert，温度转换
} 

//从ds18b20得到温度值
//精度：0.1C
//返回值：温度值 （-550~1250） 
short DS18B20_Get_Temp()
{
    unsigned char temp;
    unsigned char TL,TH;
	short tem;
    DS18B20_Start();                    // ds1820 start convert
    DS18B20_Rst();
    DS18B20_Check();	 
    DS18B20_Write_Byte(0xcc);// skip rom
    DS18B20_Write_Byte(0xbe);// convert，读取RAM数据 
    TL = DS18B20_Read_Byte(); // LSB   
    TH = DS18B20_Read_Byte(); // MSB   
    _emi = 1;
    if(TH>7)
    {
        TH = ~TH;
        TL = ~TL; 
        temp = 0;//温度为负  
    }else temp = 1;//温度为正	  	  
    tem = TH; //获得高八位
    tem <<= 8;    
    tem += TL;//获得底八位
    tem = (double)tem * 62.5;//转换   
    
	if(temp)
		return tem; //返回温度值
	else 
		return -tem;    
}
//void DS18B20_Dispaly()
//{
//	oled_shownum(0,4,temp_ds / 1000,2,12);
//	oled_showstring(12,4,".",12);
//	oled_shownum(18,4,temp_ds % 1000,3,12);
//	oled_showstring(36,4,"^",12);
//	oled_showstring(42,4,"C",12);
//}




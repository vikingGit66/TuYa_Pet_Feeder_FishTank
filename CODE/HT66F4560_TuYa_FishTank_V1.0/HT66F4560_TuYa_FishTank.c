#include "HT66F4560.h"
#include "Drv_SysClock.h"
#include "Drv_Ram.h"
#include "Drv_WDT.h"
#include "Drv_Timers.h"
#include "Drv_USIM.h"


#include "oled.h"
#include "oled_ku.h"
#include "ds18b20.h"
#include "dht11.h"
#include "KeyScan.h"
#include "ds1302.h"

#include "TuYa_JDQ_KEY_LED.h"

#include "wifi.h"

volatile short DS18B20_Temp_Debug;

void main()
{
	// 判斷是否為上電復位或者非正常情況下的復位
	// 如果是上電復位，執行上電復位初始化，反之執行WDT溢出初始化
	if (_to == 0 || _pdf ==0)
	{
		// System
//		Drv_GPIOPowerOnInit();
		fun_TuYa_JDQ_LED_IO_Init();

		Drv_SysClockInit();
		Drv_RamInit();
		SET_WDT_DISABLE();
		
		Key_Init();
		
		//oled_init();
		//oled_showphoto(0, 0,128,8,LOGO_HOLTEK);
		//oled_clear();
		//oled_shownum(0,0,20,2,12);
		//oled_showchar(24,0,'-',12);
		//oled_showchar(42,0,'-',12);
		//oled_showchar(82,0,':',12);
		
		SET_TIMEBASE_1000MS(0);//1s定時器
		SET_TIMEBASE_ENABLE(0);
		
		SET_TIMEBASE_8MS(1);//按鍵掃描時基
		SET_TIMEBASE_ENABLE(1);
		
		//Debug
		_pfc2 = 0;	//LED1
		_pf2 = 1;
		Drv_UART0_Init();
		
		wifi_protocol_init();
		
		gbv_DHT_DS18B20_Is_5s_Start = 1;
		gbv_TuYa_Send_Data_Is_10s = 1;
		
		gbv_wifi_send_FeedTimers = 1;
		gu8v_FishFood_FeedTimers = 0;
		
		gbv_wifi_Send_JDQ_Water = 1;
		gbv_wifi_Send_LED1	 	= 1;
		gbv_wifi_Send_FeedState = 1;
	}
	else
	{
		// WDT溢出復位初始化
		GCC_CLRWDT();
	}
	//主循環
	while(1)
	{
		
		//DS18B20_Get_Temp();
		GCC_NOP();
		GCC_NOP();
		
		fun_KeyScan();
		fun_Key();
		fun_JDQ_FishFood_MotoIO();
		
		wifi_uart_service();
		all_data_update();
		
		
		if(gbv_DHT_DS18B20_Is_5s_Start)
		{
			gbv_DHT_DS18B20_Is_5s_Start = 0;
			
			DHT11_Read_Data();
			DS18B20_Temp = DS18B20_Get_Temp();
		}
		
		/*if(gbv_Time_Is_1s)
		{
			gbv_Time_Is_1s = 0;
			if(time_Last[year]!= time[year])
			{			
				time_Last[year]= time[year];
				oled_shownum(12,0,time[year],2,12);
			}
			if(time_Last[month]!= time[month])
			{
				time_Last[month]= time[month];
				oled_shownum(30,0,time[month],2,12);
			}
			if(time_Last[day]!= time[day])
			{
				time_Last[day]= time[day];
				oled_shownum(48,0,time[day],2,12);
			}
			if(time_Last[hour]!= time[hour])
			{
				time_Last[hour]= time[hour];
				oled_shownum(70,0,time[hour],2,12);
			}
			if(time_Last[min]!= time[min])
			{
				time_Last[min]= time[min];
				oled_shownum(88,0,time[min],2,12);
			}*/
			
			//oled_shownum(110,0,time[second],2,12);
			/*_acc = _usr;
			_txr_rxr = 0x5a;
			while(!_tidle);*/
			
			//DHT11_Read_Data();//temp_N  temp_Dio  hum_N
			
			//DS18B20_Temp_Debug = DS18B20_Get_Temp(); //28325:28.325攝氏度
			
			
		//}
	}
	
}
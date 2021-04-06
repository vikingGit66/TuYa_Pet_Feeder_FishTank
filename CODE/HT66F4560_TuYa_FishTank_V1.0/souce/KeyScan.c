
#include "HT66F4560.h"
#include "KeyScan.h"
#include "Drv_Timers.h"

#include "TuYa_JDQ_KEY_LED.h"

#include "wifi.h"

#define OUT 0
#define IN  1
#define UP		0
#define DOWN	1
#define ON	1
#define Off		0

volatile unsigned char KEY_State;
volatile bit gbv_KEY4_Is_long_Press;

void Key_Init()
{
	//輸入上拉
	KEY1_C = IN;
	KEY2_C = IN;
	KEY3_C = IN;
	KEY4_C = IN;
	
	KEY1_Pu	 = 1;
	KEY2_Pu	 = 1;
	KEY3_Pu	 = 1;
	KEY4_Pu	 = 1;
}

void fun_KeyScan()
{
	static unsigned int gu16v_KEY4_Wifi_SmartConfig = 0;
	if(gbv_KeyScan_Time_Is_8ms)
	{
		//KEY_State = KEY_None;
		static bit key_up = 1;
		gbv_KeyScan_Time_Is_8ms = 0;
		if(	key_up &&(KEY1 == UP ||KEY2 == UP || KEY3 == UP || KEY4 == UP))
		{
			key_up = 0;
			GCC_DELAY(20000);//10ms
			if(KEY1 == UP)	KEY_State = KEY1_Up;
			else if(KEY2 == UP)	KEY_State = KEY2_Up;
			else if(KEY3 == UP)	KEY_State = KEY3_Up;
			else if(KEY4 == UP)	KEY_State = KEY4_Up;
		}
		else if((KEY1 == DOWN && KEY2 == DOWN && KEY3 == DOWN && KEY4 == DOWN))
		{
			key_up = 1;
		}
		
		if(KEY4 == UP)
		{
			gu16v_KEY4_Wifi_SmartConfig ++;
			if(gu16v_KEY4_Wifi_SmartConfig == 3000 / 8)
			{
				gu16v_KEY4_Wifi_SmartConfig = 0;
				gbv_KEY4_Is_long_Press = 1;
			}
		}
		
	}
}
/*
KEY1: 水循環
KEY2: 投食
KEY3: LED
KEY4: 長按配網
*/
void fun_Key()
{
	//水循環
	if(KEY_State == KEY1_Up)
	{
		KEY_State = KEY_None;
		JDQ_Water = ~JDQ_Water;
		gbv_wifi_Send_JDQ_Water = 1;
	}
	
	//投食
	if(KEY_State == KEY2_Up)
	{
		KEY_State = KEY_None;
		
		if(JDQ_FishFood_MotoIO == Ending)
		{
			JDQ_FishFood = ON;
			//gbv_wifi_Send_FeedState = 1;
			//gu8v_FishFood_State = FishFood_State_Is_Feeding;
			//gbv_wifi_Send_JDQ_FishFood = 1;
		}
	}
	
	//LED
	if(KEY_State == KEY3_Up)
	{
		KEY_State = KEY_None;
		LED1 = ~LED1;
		gbv_wifi_Send_LED1 = 1;
		LED2 = ~LED2;
	}
	
	//smartconfig配網
	if(gbv_KEY4_Is_long_Press)
	{
		gbv_KEY4_Is_long_Press = 0;
		//TuYa_wifi
		mcu_set_wifi_mode(0);
	}
	/*if(KEY_State == KEY4_Up)
	{
		KEY_State = KEY_None;
		LED2 = ~LED2;
	}*/
}
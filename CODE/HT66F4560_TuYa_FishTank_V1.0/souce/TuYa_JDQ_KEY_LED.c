#include "HT66F4560.h"
#include "TuYa_JDQ_KEY_LED.h"
#include "Drv_Timers.h"

#include "dht11.h"
#include "ds18b20.h"

#include "wifi.h"

#define OUT 0
#define IN  1
#define ON	1
#define Off		0

volatile short DS18B20_Temp;

volatile bit gbv_wifi_Send_JDQ_Water;
volatile bit gbv_wifi_Send_JDQ_FishFood;
volatile bit gbv_wifi_Send_LED1;

volatile bit gbv_wifi_Send_FeedState;

volatile bit gbv_wifi_send_FeedTimers;

volatile unsigned char gu8v_FishFood_State;
volatile unsigned char gu8v_FishFood_State_Last;

volatile unsigned char gu8v_FishFood_FeedTimers;

void fun_TuYa_JDQ_LED_IO_Init()
{
	JDQ_WaterC		= 	OUT;
	JDQ_FishFoodC	= 	OUT;
	LED1C			= 	OUT;
	LED2C			= 	OUT;
	
	JDQ_Water		= 	Off;
	JDQ_FishFood	= 	Off;
	LED1			= 	Off;
	LED2			= 	Off;
		
	JDQ_FishFood_MotoIOC = IN;
	JDQ_FishFood_MotoIOPU = 1;
	
	gu8v_FishFood_State_Last = gu8v_FishFood_State;
	
	gu8v_FishFood_FeedTimers = 0;
}

void fun_JDQ_FishFood_MotoIO()
{
	if(JDQ_FishFood_MotoIO == Feeding)
	{
		if(gu8v_FishFood_State_Last == FishFood_State_Is_Ending)
		{
			GCC_DELAY(2);//100ms
			if(JDQ_FishFood_MotoIO == Feeding)
				gu8v_FishFood_State = FishFood_State_Is_Feeding;
		}
	}
	else if(JDQ_FishFood_MotoIO == Ending)
	{
		gu8v_FishFood_State = FishFood_State_Is_Ending;
		if(gu8v_FishFood_State_Last == FishFood_State_Is_Feeding)
		{
			GCC_DELAY(2);//100ms
			if(JDQ_FishFood_MotoIO == Ending)
				gu8v_FishFood_State = FishFood_State_Is_Ending;
		}
		
		/*if(JDQ_FishFood == ON)
		{
				
		}*/
		
	}
	
	
	if(gu8v_FishFood_State_Last != gu8v_FishFood_State)
	{
		gu8v_FishFood_State_Last = gu8v_FishFood_State;
		gbv_wifi_Send_FeedState = 1;
		if(JDQ_FishFood_MotoIO == Ending)
		{
			JDQ_FishFood = Off;
		}
		if(JDQ_FishFood_MotoIO == Ending)
		{
			gu8v_FishFood_FeedTimers ++;
			gbv_wifi_send_FeedTimers = 1;
			if(gu8v_FishFood_FeedTimers > 12)
			{
				gu8v_FishFood_FeedTimers = 1;
			}
		}
	}
	
}




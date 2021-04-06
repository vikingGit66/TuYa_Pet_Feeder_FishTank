#ifndef _TUYA_JDQ_KEY_LED_H
#define _TUYA_JDQ_KEY_LED_H

#define JDQ_Water		_pf2
#define JDQ_WaterC		_pfc2

#define JDQ_FishFood	_pf3
#define JDQ_FishFoodC	_pfc3

//PCB板接口
#define JDQ_FishFood_MotoIO 	_pc2
#define JDQ_FishFood_MotoIOC 	_pcc2
#define JDQ_FishFood_MotoIOPU	_pcpu2

//Debug 接口
//#define JDQ_FishFood_MotoIO 	_pd6
//#define JDQ_FishFood_MotoIOC 	_pdc6
//#define JDQ_FishFood_MotoIOPU	_pdpu6

//需要确认
#define Feeding 	1
#define Ending	 	0

#define LED1			_pc1
#define LED1C			_pcc1

#define LED2			_pf7
#define LED2C			_pfc7


void fun_TuYa_JDQ_LED_IO_Init();
void fun_Time_Is_DHT_DS18B20();
void fun_TuYa_Data_Send();
void fun_JDQ_FishFood_MotoIO();

extern volatile short DS18B20_Temp;

extern volatile bit gbv_wifi_Send_JDQ_Water;
extern volatile bit gbv_wifi_Send_JDQ_FishFood;
extern volatile bit gbv_wifi_Send_LED1;

extern volatile bit gbv_wifi_send_FeedTimers;

extern volatile bit gbv_wifi_Send_FeedState;

extern volatile unsigned char gu8v_FishFood_State;

extern volatile unsigned char gu8v_FishFood_FeedTimers;

//standby, feeding, done
#define FishFood_State_Is_Feeding 1
#define FishFood_State_Is_Ending 0

#endif


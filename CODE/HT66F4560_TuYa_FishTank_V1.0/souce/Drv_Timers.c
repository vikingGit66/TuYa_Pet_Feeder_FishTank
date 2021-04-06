
#include "HT66F4560.h"
#include "Drv_Timers.h"



volatile bit gbv_KeyScan_Time_Is_8ms;
volatile bit gbv_DHT_DS18B20_Is_5s_Start;
volatile bit gbv_TuYa_Send_Data_Is_10s;
volatile bit gbv_wifi_Send_Data_Is_300ms;
//@-------MuFunction0 中斷入口函數------------@
// PTM0 & PTM1 共用
// 復合中斷需要自行清除Request Flags
DEFINE_ISR(MuFunction0_ISR, 0x00c)
{
    if (_ptm0af)
    {
        _ptm0af = 0;
        // User Code
        _pa4 = ~_pa4;
    }
    else if (_ptm0pf)
    {
        _ptm0pf = 0;
        // User Code
    }
    if (_ptm1af)
    {
        _ptm1af = 0;
        // User Code
    }
    else if (_ptm1pf)
    {
        _ptm1pf = 0;
        // User Code
    }
}
//@-------MuFunction1 中斷入口函數-----------@
// STM & EEPROM 共用
DEFINE_ISR(MuFunction1_ISR, 0x010)
{

}

//@-------MuFunction2 中斷入口函數-----------@
// ATM P & A & B 共用
//DEFINE_ISR(MuFunction2_ISR, 0x00c)
//{
//
//}

volatile bit gbv_Time_Is_1s;
volatile bit gbv_Time_Is_8ms;


//@----------Timebase0 中斷入口函數-----------@
DEFINE_ISR(TIMEBASE0_ISR, 0x018)
{
	 // User Code
	 gbv_Time_Is_1s = 1;
	 
	 static unsigned char gu8v_Time_Is_10s = 0;
	 gu8v_Time_Is_10s ++;
	 if(gu8v_Time_Is_10s == 5)
	 {
	 	gu8v_Time_Is_10s = 0;
	 	gbv_TuYa_Send_Data_Is_10s = 1;
	 }
	 
	 static unsigned char gu8v_Time_Is_5s = 0;
	 gu8v_Time_Is_5s ++;
	 if(gu8v_Time_Is_5s == 5)
	 {
	 	gu8v_Time_Is_5s = 0;
	 	gbv_DHT_DS18B20_Is_5s_Start = 1;
	 }
	 
}
//@----------Timebase1 中斷入口函數-----------@
DEFINE_ISR(TIMEBASE1_ISR, 0x01c)
{
    // User Code
    gbv_KeyScan_Time_Is_8ms = 1;
    
    static unsigned char gu8v_Time_Is_300ms = 0;
	 gu8v_Time_Is_300ms ++;
	 if(gu8v_Time_Is_300ms == 38)
	 {
	 	gu8v_Time_Is_300ms = 0;
	 	gbv_wifi_Send_Data_Is_300ms = 1;
	 }
}
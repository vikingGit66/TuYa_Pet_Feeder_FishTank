#ifndef _DRV_TIMERS_H
#define _DRV_TIMERS_H
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 共用函數 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
/**
 * @brief timebase 週期設置
 * @attention 默認使用fs =fsub, LIRC/LXT
 * @warning n=0/1
 */
#define SET_TIMEBASE_8MS(n)		    { _pscr = 0x03; _tb##n##c = 0x00;}
#define SET_TIMEBASE_16MS(n)		{ _pscr = 0x03; _tb##n##c = 0x01;}
#define SET_TIMEBASE_32MS(n)		{ _pscr = 0x03; _tb##n##c = 0x02;}
#define SET_TIMEBASE_62MS(n)		{ _pscr = 0x03; _tb##n##c = 0x03;}
#define SET_TIMEBASE_124MS(n)	    { _pscr = 0x03; _tb##n##c = 0x04;}
#define SET_TIMEBASE_250MS(n)	    { _pscr = 0x03; _tb##n##c = 0x05;}
#define SET_TIMEBASE_500MS(n)	    { _pscr = 0x03; _tb##n##c = 0x06;}
#define SET_TIMEBASE_1000MS(n)	    { _pscr = 0x03; _tb##n##c = 0x07;}
#define SET_TIMEBASE_ENABLE(n)	    { _tb##n##f = 0x00; _tb##n##e = 0x01; _tb##n##on = 1;;_emi = 1;}
#define SET_TIMEBASE_DISABLE(n)	    { _tb##n##on = 0;}


// STM
#define	SET_STMA_ISR_ENABLE()		{ _stmaf = 0; _stmae =1;}
#define	SET_STMA_ISR_DISABLE()		{ _stmae = 0;}
#define SET_STMP_ISR_ENABLE()		{ _stmpf = 0; _stmpe =1;}
#define SET_STMP_ISR_DISABLE()		{ _stmpe = 0;}




// PTMn（N=0/1/2）
#define SET_PTMn_CLOCK(n,x)         { _ptm##n##c0 = x;} // x= enum TimerClock_t
#define SET_PTMn_MODE_TIMER(n)      { _ptm##n##c1 = 0xC1;}
#define SET_PTMn_MODE_PWM(n)        { _ptm##n##c1 = 0xA4;}

#define SET_PTMn_COUNT_A(n,x)       { _ptm##n##al = x%256;_ptm##n##ah = x/256;} // x < 1024
#define SET_PTMn_COUNT_P(n,x)       { _ptm##n##rpl = x%256;_ptm##n##rph = x/256;} // x < 1024

#define	SET_PTMnA_ISR_ENABLE(n)		{ _ptm##n##af = 0; _ptm##n##ae =1;}
#define	SET_PTMnA_ISR_DISABLE(n)	{ _ptm##n##ae = 0;}
#define SET_PTMnP_ISR_ENABLE(n)		{ _ptm##n##pf = 0; _ptm##n##pe =1;}
#define SET_PTMnP_ISR_DISABLE(n)	{ _ptm##n##pe = 0;}
#define SET_PTMn_DISABLE(n)         { _pt##n##on = 0;}
#define SET_PTMn_ENABLE(n)          { _pt##n##on = 1;}

/*! 計時/計數狀態控制*/
enum TimerCountCtr_t
{
    COUNTER_OFF,   //!<
    COUNTER_ON,    //!<
    COUNTER_PAUSE, //!<
};
/*! 計時/計數狀態控制*/
enum TimerClock_t
{
    TIMECLOCK_FSYS_4 = 0x00,       //!<
    TIMECLOCK_FSYS = 0x10,         //!<
    TIMECLOCK_FH_16 = 0x20,        //!<
    TIMECLOCK_FH_64 = 0x30,        //!<
    TIMECLOCK_FSUB = 0x40,         //!<
    TIMECLOCK_PTCK_RISING = 0x60,  //!<
    TIMECLOCK_PTCK_FALLING = 0x70, //!<
};


/**
 * @brief 復合終端使能和除能
 *
 * @note n=0/1/2
 */
#define SET_M_FUNCT_N_ENABLE(n)     { _mf##n##f = 0; _mf##n##e = 1;}
#define SET_M_FUNCT_N_DSIABLE(n)    { _mf##n##e = 0;}

#define SET_PTMn_COUNTER_OFF(n)     { _pt##n##on = 0;}
#define SET_PTMn_COUNTER_ON(n)      { _pt##n##on = 1; _pt##n##pau = 0;}
#define SET_PTMn_COUNTER_PAUSE(n)   { _pt##n##pau = 1;}

void Drv_PTMn_PWM_Init(unsigned char PTMn, enum TimerClock_t timeClock, unsigned int Count_A,unsigned int Count_P);
void Drv_PTMn_Timer_Init(unsigned char PTMn, enum TimerClock_t timeClock, unsigned int Count_A,unsigned int Count_P);
void Drv_PTMn_Ctr(unsigned char PTMn, enum TimerCountCtr_t Status);

extern volatile bit gbv_Time_Is_1s;
extern volatile bit gbv_KeyScan_Time_Is_8ms;
extern volatile bit gbv_DHT_DS18B20_Is_5s_Start;
extern volatile bit gbv_TuYa_Send_Data_Is_10s;
extern volatile bit gbv_wifi_Send_Data_Is_300ms;



#endif




#ifndef _DRV_WDT_H_
#define _DRV_WDT_H_
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 共用函數 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
/**
 * @brief WDT overflow 時間設置
 * @note WDT clock Source fs =fsub  WDT time =  2^18/fsub
 * example:(max time 周期最长2^18，Source fs = 32000)
 *
 */
#define SET_WDT_DISABLE()		    { _wdtc = 0xA8;}
#define SET_WDTTIME_8MS()		    { _wdtc = 0x50;}
#define SET_WDTTIME_32MS()		    { _wdtc = 0x51;}
#define SET_WDTTIME_125MS()		    { _wdtc = 0x52;}
#define SET_WDTTIME_500MS()		    { _wdtc = 0x53;}
#define SET_WDTTIME_1000MS()		{ _wdtc = 0x54;}
#define SET_WDTTIME_2000MS()		{ _wdtc = 0x55;}
#define SET_WDTTIME_4000MS()		{ _wdtc = 0x56;}
#define SET_WDTTIME_8000MS()		{ _wdtc = 0x57;}

// WDT 軟件復位
// 復位動作發生在tSRESET延遲時間後，且 RSTFC 的 _wrf 將置為1, _wrf只能通過程序清除
#define SET_WDT_RESET_MCU()         { _wdtc |= 0xF0;while(1);}  // WDTC register software reset flag _wrf = 1;

#endif



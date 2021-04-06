

#include "HT66F4560.h"
#include "Drv_SysClock.h"


/**
 * @brief 配置系統頻率
 * @detail 可選系統頻率 低速=LIRC/LXT  高速=HIRC_4M/HIRC_8M/HIRC_12M
 *
 * @note 注解
 * @attention 部分IC LXT功能 需要在 LXT2 Pin 加上拉10M到 VDD，詳細參考規格書 LXT 描述
 * @warning 在線Debug時,LXT無法使用，可先切換為LIRC，debugOK後在切換為LXT
 * @exception 若電路 HXT 晶振和 LXT 異常會造成程序在此死循環
 */
void Drv_SysClockInit()
{
    // *********系統時鐘設定********//
    
    #ifdef _HIRC_8M_        
        _hircc = 0x09;
        while (!_hircf);    // Wait HIRC Oscillator Stable
    #endif // _HIRC_8M_
    
    /*
    #ifdef _HXT_
    	_hxten = 1;
    	_fhs = 1;
//    	_hxtm = 1;          //HXT frequency >10MHz
		SET_PD6_OSC1();
		SET_PD7_OSC2();
		while(!_hxtf);
    #endif //_HXT_
    */
    #ifdef _LXT_
        _lxten = 1;
        _fss   = 1;
		_fsiden = 1;		// Enter Halt LXT Is Enable
		unsigned char i;
		for(i=0;i<10;i++)
		{
		#ifdef _HIRC_4M_
			GCC_DELAY(10);
		#endif // _HIRC_4M_
		#ifdef _HIRC_8M_
			GCC_DELAY(20);
		#endif // _HIRC_8M_
		#ifdef _HIRC_12M_
			GCC_DELAY(30);
		#endif // _HIRC_12M_
            SET_PC3_GPIO();
            SET_PC4_GPIO();
            _pcpu3 = 1;
			_pcpu4 = 1;
            SET_PC3_XT1();
            SET_PC4_XT2();
        }
        _clrwdt();
        while (!_lxtf);     // Wait LXT Oscillator Stable
    #endif // _LXT_
    #ifdef _LIRC_
        _fss   = 0;
        _lxten = 1;
		_fsiden = 1;		// Enter Halt LIRC Is Enable
    #endif // _LIRC_
}
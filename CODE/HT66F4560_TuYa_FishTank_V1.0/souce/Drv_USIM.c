
#include "HT66F4560.h"
#include "Drv_USIM.h"

#include "wifi.h"

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 共用變量 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


void Drv_UART0_Init()
{
	_bno  = 0;//0：8-bit 传输数据
	_pren = 0;//0：奇偶校验除能
	_prt  = 0;//0：偶校验
	_stops = 0;//0：有一位停止位
	_txbrk = 0;//0：没有暂停字要发送
	_brgh = 1;//0：低速波特率
	_brg = 51;//BR = fH / [16 (N+1)] =9600 ; N = 77 ->9615.38
	_adden = 0;//0：地址检测除能
	
	//先使能縂串口
	_uarten = 1;//1：UARTn 使能，TXn 和RXn 脚作为UARTn 功能引脚
	_txen = 1;//1：UARTn 发送使能
	_rxen = 1;//1：UARTn 接收使能
	
	
	
	_rie = 1;//1：接收中断使能
	
//	_tiie0 = 1;
//	_teie0 = 1;
	
	_uartf = 0;
	_uarte = 1;
	
	_emi = 1;
	// UART IO
	_pbs05 = 1;//10：TX
	_pbs04 = 0;
	
	_pas13 = 0;//01：RX
	_pas12 = 1;
	
	_ifs01 = 1;//RX:0：PA5
	_ifs00 = 0;
	
}

volatile unsigned char data_temp;
DEFINE_ISR(USIM0_ISR, 0x034)
{
	// 奇偶校验出错
	// if (_perr0)
	// {
	// 	_acc = _usr;
	// 	_acc = _txr_rxr;
	// }
	// 錯誤處理
	if (_nf | _ferr | _oerr)	//  噪声干扰错误 | 帧错误 | 溢出错误
	{
		_acc = _usr;
		_acc = _txr_rxr;
	}
	// 发送数据
	if (_txif)
	{
		
	}
	// 接收数据
	if (_rxif)
	{
		// 塗鴉UART接收数据//2020/11/12
		data_temp = _txr_rxr;
		uart_receive_input(data_temp);
	}
}

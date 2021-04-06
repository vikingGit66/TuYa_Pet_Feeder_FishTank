#ifndef _DRV_USIM_H_
#define _DRV_USIM_H_

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 共用變量 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#define  UART_LENGTH_TX	110	// 協議中最大的長度
#define  UART_LENGTH_RX	10	// 協議中最大的長度

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 共用函數 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void Drv_UART0_Init();     // 初始化

#endif
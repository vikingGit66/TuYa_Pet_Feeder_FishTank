
#ifndef _KEY_SCAN_H
#define _KEY_SCAN_H


#define	KEY1       		_pa7	
#define	KEY1_C       	_pac7	
#define	KEY1_Pu       	_papu7	

#define	KEY2       		_pb3	
#define	KEY2_C       	_pbc3	
#define	KEY2_Pu       	_pbpu3

#define	KEY3       		_pb6
#define	KEY3_C       	_pbc6	
#define	KEY3_Pu       	_pbpu6

#define	KEY4       		_pa3	
#define	KEY4_C       	_pac3	
#define	KEY4_Pu       	_papu3

#define KEY_None 	0
#define KEY1_Up		1
#define KEY2_Up		2
#define KEY3_Up		3
#define KEY4_Up		4


void Key_Init();
void fun_KeyScan();
void fun_Key();


extern volatile unsigned char KEY_State;

#endif




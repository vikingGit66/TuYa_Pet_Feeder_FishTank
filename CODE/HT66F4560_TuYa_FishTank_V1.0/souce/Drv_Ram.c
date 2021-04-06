
#include "HT66F4560.h"
#include "Drv_Ram.h"

/**
 * @brief RAM初始化
 * @detail 將所有RAM初始為0
 *
 * @note 適用RAM大於256byte IP
 * @attention 注意
 * @warning 警告
 * @exception 异常
 */
#define RAM_BANK 2
void Drv_RamInit()
{
	_mp1h = 0;
	_mp1l = 0x80;
	while(_mp1h < RAM_BANK)
	{
		for(_tblp = 0x00;_tblp < 128;_tblp++)
		{
			_iar1 = 0;
			_mp1l++;
		}
		_mp1l = 0x80;
		_mp1h++;
	}
}

#include "HT67F489.h"
#include "init_ht67f489.h"
#include "Clock_Run.h"
#include "KeyScan.h"
#include "EEPROM.h"
#include "define.h"
#include "UART.h"
#include "LCD.h"
#include "Menu.h"
#include "Feed.h"
#include "sound_isd1820.h"
#include "Motor.h"
u8 feed_going = 0; //执行喂食标志位			=1执行喂食（调用feed_run）

//执行喂食：按键手动  定时
u8 feed_run(struct feed_record * info)
{
	u8 weight = 0;
	u8 i = ISD1820_REC_TIME + 1;
	u8 ret = 0; 				//转动次数

	sheep_flag = 0;
	lcd_timeout = 0;

	if(info->quantity != 0)
	{
		if(info->music != 3)
		{
			sound_play();

			while(i)
			{
				GCC_CLRWDT();
				Delay_ms(1000);
				i--;
			}
		}
	}
	weight = info->quantity;

	//启动电机
	info->quantity = motor(weight, &ret);
	return ret; //转动次数
}


//检测是否有喂食计划
inline void feed_scan(struct feed_record * feed)
{
	u8 i;

	for(i = 1; i < FEED_MAX_NUM + 1; i++)
	{
		//扇区大小512，但每个扇区只能使用前120字节保存喂食记录，所以需要计算出每个条目保存在eeprom的地址
		feed->hour = 10 * e2prom_read(1 + 5 * i) +e2prom_read(2 + 5 * i);
		feed->minute = 10 * e2prom_read(3 + 5 * i) +e2prom_read(4 + 5 * i);
		feed->quantity = e2prom_read(5 + 5 * i);

		//UART_SendChar(feed->hour);
		if((feed->hour == rtc_date.hour) && (feed->minute == rtc_date.minute))
		{
			/*	SendString("****goto feed****\n");*/ //debug 3.13

			//feed_run(feed);
			rtc_lcd();
			feed->music = 1;
			sheep_flag = 0;
			feed_going = 1;
			time2_task = 1;
			break;
		}
	}
}



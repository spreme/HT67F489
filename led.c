
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
#include "Led.h"
#include "Motor.h"


u8 feed_error = 0; //记录返回喂食转动次数
u8 task_delay_error = 100;
u8 task_run_motor = 1;

u8 feed_detect_again = 0;


void pwr_task(void)
{
	RECODE_LED = ~RECODE_LED;		//红灯闪烁
	
//	if(error_time == 0)				//只第一次执行
		PWR_LED = LED_OFF;			//关闭绿灯
	
//	error_time = 1;					//第一次执行标志位
	
//	if(PWR_LED == LED_ON)			//闪烁中遇到其他任务绿灯亮了，退出错误
//		task_run_led = 0;			//错误任务终结
	
}


void error_task(void)
{
	if(feed_error)
	{
		task_run_led = 1;
		led_flag = 4;
	}
	else
	{
		task_run_led = 0;
		led_flag = 0;
	}

	//判断红外对管是否一直被阻挡（gpio引脚电平0或1）
	//	if (IR_DET) {
	//		feed_error |= ERROR_IR;
	//	} else {
	//		feed_error &= ~ERROR_IR;
	//	}
}



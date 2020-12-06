#include "HT67F489.h"
#include "init_ht67f489.h"
#include "Clock_Run.h"
#include "KeyScan.h"
#include "EEPROM.h"
#include "define.h"
#include "UART.h"
#include "LCD.h"


volatile u8 lcd_glint =0;			//LCD闪烁（冒号）
volatile int lcd_timeout =0;		//计时
//u8 lcd_timeout_pwr =0;
u8 task_run_led = 0;			//LED运行错误任务
u8 task_delay_led = 100;		//错误闪烁led任务	

volatile u8 feed_detect = 0;	//定时喂食时间检测，每分钟检测一次（每分钟变为1）
struct rtc_time rtc_date;
void rtc_init(void)
{
	rtc_date.hour = 0;
	rtc_date.minute = 0;
	rtc_date.second = 0;
}

#if 0
//inline void Clock_Run()
//{
//	
//  rtc_date.second++;
//  if(rtc_date.second >59)
//  { 
//  	rtc_date.minute++;
//  	rtc_date.second=0;
//  	feed_detect = 1;	//定时喂食时间检测，每分钟检测一次
//	if(rtc_date.minute >59)
//	{ 
//	  rtc_date.hour++;	    
//      rtc_date.minute=0;     
//	     if(rtc_date.hour >23)
//	     {
//	  	      
//	     rtc_date.hour=0;
//	          
//		 }
//	
//    }	
//  }
//}

//inline void glint_task(void)
//{
//	lcd_glint++;
//	if (lcd_glint >= 80) {
//		lcd_glint = 0;
//	}
//}

//inline void timeout_task(void)
//{
//	lcd_timeout++;
//	if (lcd_timeout >= 8100) {//40s
//		lcd_timeout = 0;
//	}
//}
#endif

void time_save()			//保存时间
{
	e2prom_write(31,rtc_date.hour);
	e2prom_write(32,rtc_date.minute);	

}


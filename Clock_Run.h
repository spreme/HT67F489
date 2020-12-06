#ifndef __CLOCK_RUN_H__
#define __CLOCK_RUN_H__

extern uchar rtc_flag ;

extern volatile u8 lcd_glint;
extern volatile int lcd_timeout ;




extern volatile u8 feed_detect ;	//定时喂食时间检测，每分钟检测一次
//void Clock_Run();
//void glint_task(void);
//void timeout_task(void);
void time_save();			//保存时间
void BUZZER_inlt(void);


void rtc_init(void);

struct rtc_time {
	

	volatile uchar hour;
	volatile uchar minute;
	volatile uchar second;

};

extern struct rtc_time rtc_date;

#endif
//====================================================//
//				  选用芯片：HT67F489				  //
//					  
//====================================================//
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
#include "voltage.h"		//（原）
//===========================时钟初始化函数=========================================//
//char watch =2+0x30;
char key_up_flag = 0; 				//时钟显示标志位			1：显示实时时钟		0：不显示
char col_staus = 1; 				//时间点跳动标志
char meal_flag = 0; 				//喂食计划菜单标志（0：没有进入				1~4:1到4的喂食计划）
char key_lock = 1; 					//按键锁定标志位			1：锁定		0：开锁
u8 sheep_flag = 0; 					//睡眠模式标志位（没用）
u8 buzzer_time = 0;
u8 res = 0;
u8 vol_flag = 0; 					//外电标志位
u8 buzzer_detect = 0; 				//低电压时每分钟蜂鸣器响一下
u8 time_save_flag = 0;				//一小时保存一次时间
u8 time_save_flag_1 = 0;				//休眠标志位,1:代表休眠 0：代表醒着
u8 error_time = 0;					//错误次数（有错误红灯亮，结束灭）
u8 led_flag = 0;					//灯状态标志位        0：绿灯常亮	1：绿灯慢闪          2：绿灯灭 3：红灯常亮 4：红灯慢闪 5：红灯灭 6:全灭


void BUZZER_inlt(void)
{
	BUZZER = 1;
	Delay_ms(100);
	BUZZER = 0;
}


u8 time2_task = 0; 				//检测时间节点跳动标志位


void main()
{


#if 0 //（原）

	GCC_CLRWDT();
	init_Timerset();
	LCD_init();
	UART_init();

	AD_init();
	init_SyS();
#endif

	while(!_hto);

	GCC_CLRWDT();				//看门狗清0
	init_SyS(); 				//系统初始化
	init_Timerset();			//定时器中断功能配置项
	LCD_init(); 				//lcd屏幕初始化

	/* UART_init();*/
	AD_init();


	init_Timer();
	init_Timer_isc0();
	init_Timer1();
	//init_Timer2();

	/*	init_Timer3();*/
	GPIO_INIT();

	kaiji_init();
	rtc_init(); 				//实时时钟初始化
	e2prom_init();				//读写存储器初始化
	rtc_date.hour = e2prom_read(31);
	rtc_date.minute = e2prom_read(32);
	/*SendString("V190303->801e-3.3V\n");  */ //debug 3.13
	struct feed_record feed;
	char key_value_1 = 0;
	u8 rst_flag_0 = 0;      
	PWR_LED = LED_OFF ;		//lcd屏幕背景不亮
	while(1)
	{
		if(res == 0)
		{
			GCC_CLRWDT();
		}

		if(key_up_flag)
		{
			rtc_lcd();			//显示时间
		}

		if(voltage_low)
		{

			if(buzzer_detect) 		//低电压时每分钟蜂鸣器响一下  1：响
			{
				buzzer_detect = 0; 	//复位0
				BUZZER_inlt();		//蜂鸣器响
			}

		}
		
		if(time_save_flag)				//
		{
			time_save_flag = 0;
			time_save();	
		}

		if(res == 0)
			key_value_1 = key_scan();		//按键检测

		//按键锁定的情况下
		if(key_lock)
		{
			if(key_value_1 == KEY_SET_L)
			{


				BUZZER_inlt();
				kaiji_mode();

			}


			if(key_value_1 == KEY_UP_L)
			{
				if(rst_flag_0 == 0)
				{
					rst_flag_0 = 1;

					/*	SendString("+++++res++++\n");	*/
					e2prom_write(2, 255);
					ISD1820_REC = 1;
					Delay_ms(600);
					ISD1820_REC = 0;
					ISD1820_REC_TIME = 0;
					res = 1;
				}
			}



		}

		//按键解锁后			 
		else if(key_lock == 0)
		{

			switch(key_value_1)
			{
				case KEY_SET_L: 					//解锁按键			//设置
					{
						key_up_flag = 0; 			//不显示实时的时钟
						BUZZER_inlt();

						if(meal_flag <5 && meal_flag > 0) //喂食计划5个菜单
						{
							meal_on; 					//打开菜单
							set_meal(meal_flag); 		//设置菜单
						}
						else
						{
							meal_off; //关闭菜单
							set_time(); //设置时间

						}
					}
					break;

				case KEY_REC_L: 					//录音
					RECODE_LED = LED_ON; 			//红色指示灯
					PWR_LED = LED_OFF;
					led_flag = 3;					//红灯常亮
					time2_task = 1; 				//开启检测时间节点跳动
					ISD1820_REC_TIME = 0; 			//录音时长清0
					REC_TIME_flag = 1; 				//录音标志位（=1 开启中断，录音时长计时）
					sound_rec();
					REC_TIME_flag = 0;
					time2_task = 0;
					RECODE_LED = LED_OFF; 			//红色指示灯
					PWR_LED = LED_ON;
					led_flag = 0;
					/*	 UART_SendChar(ISD1820_REC_TIME);*/
					break;

				case KEY_SET: 						//解锁后，不在设置模式下，短按设置键无功能	
					GCC_NOP(); 						//（原）
					break;

				case KEY_ESC: 						//手动喂食
					time2_task = 1;
					BUZZER_inlt(); 					//蜂鸣器灯闪烁
					feed.quantity = 1; 				//喂食份数：1
					feed.music = 3; 				// =3不播放录音
					feed_going = 1; 				//执行喂食标志位：执行
					break;

				case KEY_REC:	 					//放音
					BUZZER_inlt(); 					//蜂鸣器
//					RECODE_LED = LED_ON; 			//红色指示灯	
//					Delay_ms(500);
//					RECODE_LED = LED_OFF; 			//红色指示灯
					PWR_LED = LED_ON;
					RECODE_LED = LED_OFF;
					led_flag = 0;
					sound_play(); 					//播放录音
					break;

				case KEY_UP:
					Delay_ms(100);
					meal_flag++;
					BUZZER_inlt();

					if(meal_flag > 4) meal_flag = 0;

					break;

				case KEY_DOWN:
					Delay_ms(100);
					meal_flag--;
					BUZZER_inlt();

					if(meal_flag < 0) meal_flag = 4;

					break;
			}


			if(meal_flag < 5 && meal_flag > 0)
			{
				get_meal(meal_flag);

			}
			else
			{
				frist_menu();	//主菜单
			}

			menu_lcd(); 		//菜单显示

		}

		if(lcd_timeout > sheep_time && time_save_flag_1 == 0) 		//40秒休眠
		{
			time_save();					//保存时间
//			task_run_led = 0;
//			led_flag = 0;
			feed_error = 0;
			sleep_mode();					//睡眠
		}

#if 0

		//	 if(sheep_flag ==1)//睡眠		//debug 3.13
		//		{
		//			  _halt();
		//		}				
#endif

		if(lcd_timeout == meal_time) 			//30秒	不操作退出到主菜单页面
		{
			meal_flag = 0;
//			time_save();
		}

		//每分钟扫描一次eeprom，判断使用有定时喂食需要处理
		if(feed_detect)
		{
			// _adoff=0;//打开ad电源
			feed_detect = 0;

			feed_scan(&feed);					//检测是否有喂食计划

			if(key_lock == 0)					//睡眠标志位（1：锁定）
			{
				time_save();
			}

			if(feed_going == 0) 				//没有到喂食计划
			{
				if(DC_DET == 0) voltage_lcd();	 //ADC
			}

			// _adoff=1;//打开ad电源
		}

		if(feed_going)
		{
			feed_error = feed_run(&feed);
			time_save();
			feed_going = 0;

		}

		if(feed_going == 0)
		{
			if(vol_flag != DC_DET)
			{

				vol_flag = DC_DET;

				if(DC_DET)
				{
					power_clr;
					power_0;
					power_1;
					power_2;
					power_3;
					power_4;
					voltage_low = 0;

				}
				else
				{
					voltage_lcd(); 				//ADC
				}

				
			}

		}

		if(col_staus)
		{
			if(rtc_date.second % 2 == 0) 		//时间点跳动
			{
				col_on;
			}
			else
			{
				col_off;
			}
		}


	}

}


/********************定时器0*********************************/
void __attribute((interrupt(0x0c))) Interrupt_tm0()
{
	
	_t0af = 0;					//TM0 比较器A 匹配中断请求标志位,0：无请求
	_t0ae = 1;					//TM0 比较器A 匹配中断控制位,1：使能


	lcd_glint++;

	if(lcd_glint >= 80)
	{
		lcd_glint = 0;
	}

	lcd_timeout++;

	if(lcd_timeout >= 8100) 		//40s
	{
		lcd_timeout = 0;			//lcd睡眠计时
	}

	if(key_lock == 0)									//开锁状态下
	{
		if(task_run_led && led_flag == 4)				//遇到错误事件，红灯慢闪
		{
			task_delay_led--;							//闪烁时间

			if(task_delay_led == 0)						//闪烁一次时间到了
			{
				pwr_task();								//闪烁函数

				task_delay_led = task_delay_error;		//重新赋值闪烁时间
			}
		}
		
		else if(led_flag == 3)		//红灯常亮
		{
			RECODE_LED = LED_ON;				//红灯开启
			PWR_LED = LED_OFF;					//绿灯关闭
//			error_time = 0;						//清零第一次错误标志
		}	
		
		else if(led_flag == 0)		//绿灯常亮
		{
			RECODE_LED = LED_OFF;				//红灯关闭
			PWR_LED = LED_ON;					//绿灯开启
//			error_time = 0; 					//清零第一次错误标志
		}	
		
		else if(led_flag == 6)		//全灭
		{
			RECODE_LED = LED_OFF;				//红灯关闭
			PWR_LED = LED_OFF;					//绿灯开启
//			error_time = 0; 					//清零第一次错误标志
		}	
		
//		if(MOTOR_EN == 1)
//			PWR_LED = LED_ON;
	}

	if(time2_task)
	{
		if(rtc_date.second % 2 == 0) 		//时间点跳动
		{
			col_on;
		}
		else
		{
			col_off;
		}
	}

}




/********************定时器2*********************************/
//void __attribute((interrupt(0x14))) Interrupt_tm2()
//{

//	_t2af = 0;					//TM2 比较器A 匹配中断请求标志位,0：无请求
//	_t2ae = 1;					//TM2 比较器A 匹配中断控制位,1：使能

//	if(BUZZER_FLAG)
//	{
//		BUZZER = ~BUZZER;
//	}
//}


///********************定时器3*********************************/
//void __attribute((interrupt(0x18))) Interrupt_tm3()//200ns
//{
//
//	_t3af=0;			 //TM3 比较器A 匹配中断请求标志位,0：无请求
//	_t3ae=1;			 //TM3 比较器A 匹配中断控制位,1：使能
//	if(time2_task)
//	{
//			if(rtc_date.second %2 ==0)	 //时间点跳动
//			 {
//				col_on;
//			 }else{
//			   col_off;	
//			 }
//	
//		
//	}
//
// 
//
//}
void __attribute((interrupt(0x2c))) Interrupt_ISC0()
{

	_tb0f = 0;						//总中断开

	rtc_date.second++;
	
	if(rtc_date.second > 59)
	{
		buzzer_detect = 1;				//低电压时每分钟蜂鸣器响一下，一分钟检测一次	
		rtc_date.minute++;
		rtc_date.second = 0;
		feed_detect = 1;			//定时喂食时间检测，每分钟检测一次

		if(rtc_date.minute > 59)
		{
			time_save_flag = 1;
			rtc_date.hour++;
			rtc_date.minute = 0;

			if(rtc_date.hour > 23)
			{
				rtc_date.hour = 0;
			}
		}
	}

	if(REC_TIME_flag == 1)
	{
		ISD1820_REC_TIME++;
	}

}

//UART中断				//（原）
//void __attribute((interrupt(0x20))) Interrupt_UART()
//{
//
//	if(_rxif==1){
//	rx_com[rx_pos]=_txr_rxr;
//	if(++rx_pos==6) {
//	rx_pos=0;	
//	  uart_flag=uart_flag|0x80;
//	  }
//	}
//
//}
void __attribute((interrupt(0x04))) Interrupt_INT0()
{
	key_int = 1;
}


void __attribute((interrupt(0x08))) Interrupt_INT1()
{
	key_int_1 = 1;
}


void __attribute((interrupt(0x24))) Interrupt_INT2()
{
	key_int_2 = 1;
}


void __attribute((interrupt(0x28))) Interrupt_INT3()
{
	key_int_3 = 1;
}



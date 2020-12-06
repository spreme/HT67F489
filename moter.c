
#include "HT67F489.h"
#include "init_ht67f489.h"
#include "Clock_Run.h"
#include "KeyScan.h"
#include "EEPROM.h"
#include "define.h"
#include "UART.h"
#include "LCD.h"
#include "Menu.h"
#include "motor.h"
#include "Led.h"

u8 food_out = 0;
u16 food_timeout = 500; //2s

u8 food_count = 0;


int motor_run(void)
{
	int timeout = 600;			//用于判断电机超时
	int i = 0;
	int key_cont = 0;

	lcd_timeout = 0;

	//启动电机
	MOTOR_EN = 1;



	//先让电机转过一定角度，退出到位开关压着的状态，低->高
#if 1
	key_cont = 0;
	i = 600;

	while(i)
	{
		Delay_ms(10);
		GCC_CLRWDT();


		if(MOTOR_DET)
		{
			key_cont++;

			if(key_cont > 30)
			{
				break;
			}

//			break;	（我）	
		}

		if(i < 20) //超时处理
		{
			timeout = 0;
			break;
		}

		i--;

	}

#else

	Delay_ms(1000);
#endif

	//等待电机中断(下降沿触发)到来，中断到来后判断中断引脚电平是否为低(并有延时去抖)
	//低表示限位开关还被电机的旋转机构压着，这时电机停止转动
	lcd_timeout = 0;

	while(timeout)
	{
		GCC_CLRWDT();

		if(MOTOR_DET == 0)
		{

			key_cont = 0;
			i = 20;
			Delay_ms(10);		//延时去抖

			while(i)
			{
				Delay_ms(10);	//延时去抖

				if(MOTOR_DET == 0)
				{
					key_cont++;
				}

				i--;
			}

			if(key_cont > 6)
			{
				//					delay_ms(10);	//让出食机构可以准确到位
				break;
			}

		}
		Delay_ms(10);			//（我）
		timeout--;

	}

	return timeout;
}


u8 motor(u8 count, u8 * err_type)
{

	int feed_cont = count;		//用于判断电机转动次数，每转动一次，喂食一份（大概10g）
	int timeout = MOTO_TIMEOUT; //用于判断电机超时

	/*	u8 errs_flag = 0;
	  u8 errs = 0;*/
	task_run_led = 0;
	led_flag = 0;

	task_run_motor = 1;

	food_out = 0;

	*err_type = 0;				//清空错误码


	while(feed_cont > 0)
	{
		GCC_CLRWDT();			//喂狗
		lcd_timeout = 0;

		timeout = motor_run();

		//电机超时，电机没转或到位开关探测错误(到位开关没中断)
		if(timeout == 0)
		{
//			SendString("===== DET ERROR 1 =====\r\n");
			task_run_led = 1;
			led_flag = 4;
			goto err;
		}
		feed_cont--;

	}


err:
	MOTOR_EN = 0;
	time2_task = 0;
	task_run_motor = 0;
	lcd_timeout = 0;

#if 0
	/*if((err_type >0) || (errs_flag ==1))
	{
	 
	 BUZZER =BUZZER_ON;
	 Delay_ms(1000);
	 BUZZER =BUZZER_ON;
	 Delay_ms(1000);
	 
	}*/

	/*	PWR_LED = LED_ON;*/
	//LED_IR = 0;
#endif
	return (feed_cont);
}



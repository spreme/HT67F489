#include "HT67F489.h"
#include "init_ht67f489.h"
#include "Clock_Run.h"
#include "KeyScan.h"
#include "EEPROM.h"
#include "define.h"
#include "UART.h"
#include "LCD.h"
#include "Menu.h"


u8 key_int = 0;
u8 key_int_1 = 0;
u8 key_int_2 = 0;
u8 key_int_3 = 0;

int key_value_count = 0;


u8 key_scan(void)
{
	u8 key_value = 0;

	key_value_count = 0;

	if(!Key_Down)
	{
		sheep_flag = 0; 		//睡眠模式标志位
		lcd_timeout = 0;

		while(lcd_timeout < 900)
		{
			GCC_CLRWDT();
			Delay_ms(10);

			key_value_count++;

			if(key_value_count > 5)
			{
				key_value_count = 0;
				key_int_1 = 0;

				//判断按键是否长按			
				//	if(key_lock)
				{
					key_value = KEY_DOWN;
					/*SendString("****KEY_DOWNL****\n");*/ //debug 3.13
				}
				return key_value;
			}
		}
	}

	else if(!Key_UP)
	{
		sheep_flag = 0; 	//睡眠模式标志位
		lcd_timeout = 0;

		while(lcd_timeout < 900)
		{
			GCC_CLRWDT();
			Delay_ms(10);

			if(key_lock == 0)
			{
				if(key_value_count > 5)
				{
					key_int_3 = 0;
					{
						if(!Key_UP)
						{
							key_value = KEY_UP;
						}
					}
					key_value_count = 0;
					return key_value;
				}

				key_value_count++;
			}

			if(key_lock)
			{
				if(key_value_count > 230)			//判断按键是否长按
				{
					key_value_count = 0;
					key_value = KEY_UP_L;
					return key_value;

				}

				if(Key_UP)
				{
					if(key_value_count <= 230)
					{
						//判断按键是否长按			
						key_value = KEY_UP;
						return key_value;
					}
				}

				key_value_count++;
			}
		}
	}
	else if(key_int && !Key_Set)
	{
		key_int = 0;
		sheep_flag = 0; 		//睡眠模式标志位
		lcd_timeout = 0;

		while(lcd_timeout < 900)
		{
			GCC_CLRWDT();
			Delay_ms(10);

			if(Key_Set)
			{
				if(key_value_count <= 230)		//判断按键是否短按
				{							
					key_value = KEY_SET;
					return key_value;
				}
			}

			key_value_count++;

			if(key_value_count > 230)			//判断按键是否长按
			{		
				key_value = KEY_SET_L;
				return key_value;
			}
		}
	}

	else if(!Key_Play)
	{
		{
			sheep_flag = 0; 	//睡眠模式标志位
			lcd_timeout = 0;
			Delay_ms(10);

			if(Key_Play)
			{
				key_value = KEY_ESC;
				return key_value;
			}
		}
	}

	else if(!Key_Record)
	{
		/*key_int_2=0;*/
		sheep_flag = 0; 		//睡眠模式标志位
		lcd_timeout = 0;

		while(lcd_timeout < 900)
		{
			GCC_CLRWDT();
			sheep_flag = 0; 	//睡眠模式标志位
			lcd_timeout = 0;
			Delay_ms(10);

			if(Key_Record)
			{
				if(key_value_count <= 230)
				{
					key_value = KEY_REC;
					return key_value;
				}
			}

			key_value_count++;

			if(key_value_count > 230)			//判断按键是否长按
			{
				key_value = KEY_REC_L;
				return key_value;
			}
		}
	}

	return 0;
}



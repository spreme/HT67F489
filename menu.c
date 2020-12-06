
#include "HT67F489.h"
#include "init_ht67f489.h"
#include "Clock_Run.h"
#include "KeyScan.h"
#include "EEPROM.h"
#include "define.h"
#include "UART.h"
#include "LCD.h"
#include "Menu.h"
#include "Motor.h"
#include "voltage.h"			//（原）

u8 eeprom_time[4] =
{
	0
};


u8 eeprom_feed[5] =
{
	0
};


void lcd_num_5(u8 num)
{
	switch(num)
	{
		case 1:
			lcd_5_clr;
			lcd_5_1;
			break;

		case 2:
			lcd_5_clr;
			lcd_5_2;
			break;

		case 3:
			lcd_5_clr;
			lcd_5_3;
			break;

		case 4:
			lcd_5_clr;
			lcd_5_4;
			break;

		case 5:
			lcd_5_clr;
			lcd_5_5;
			break;

		case 6:
			lcd_5_clr;
			;
			lcd_5_6;
			break;

		case 7:
			lcd_5_clr;
			lcd_5_7;
			break;

		case 8:
			lcd_5_clr;
			lcd_5_8;
			break;

		case 9:
			lcd_5_clr;
			lcd_5_9;
			break;

		default:
			lcd_5_clr;
			lcd_5_0;
			break;
	}

}


void lcd_num(u8 num)
{
	switch(num)
	{
		case 1:
			lcd_4_clr;
			lcd_4_1;
			break;

		case 2:
			lcd_4_clr;
			lcd_4_2;
			break;

		case 3:
			lcd_4_clr;
			lcd_4_3;
			break;

		case 4:
			lcd_4_clr;
			lcd_4_4;
			break;

		case 5:
			lcd_4_clr;
			lcd_4_5;
			break;

		case 6:
			lcd_4_clr;
			lcd_4_6;
			break;

		case 7:
			lcd_4_clr;
			lcd_4_7;
			break;

		case 8:
			lcd_4_clr;
			lcd_4_8;
			break;

		case 9:
			lcd_4_clr;
			lcd_4_9;
			break;

		default:
			lcd_4_clr;
			lcd_4_0;
			break;
	}

}


void lcd_num_3(u8 num)
{
	switch(num)
	{
		case 1:
			lcd_3_clr;
			lcd_3_1;
			break;

		case 2:
			lcd_3_clr;
			lcd_3_2;
			break;

		case 3:
			lcd_3_clr;
			lcd_3_3;
			break;

		case 4:
			lcd_3_clr;
			lcd_3_4;
			break;

		case 5:
			lcd_3_clr;
			lcd_3_5;
			break;

		default:
			lcd_3_clr;
			lcd_3_0;
			break;
	}

}


void lcd_num2_2(u8 num)
{
	switch(num)
	{
		case 1:
			lcd_2_clr;
			lcd_2_1;
			break;

		case 2:
			lcd_2_clr;
			lcd_2_2;
			break;

		case 3:
			lcd_2_clr;
			lcd_2_3;
			break;

		case 4:
			lcd_2_clr;
			lcd_2_4;
			break;

		case 5:
			lcd_2_clr;
			lcd_2_5;
			break;

		case 6:
			lcd_2_clr;
			lcd_2_6;
			break;

		case 7:
			lcd_2_clr;
			lcd_2_7;
			break;

		case 8:
			lcd_2_clr;
			lcd_2_8;
			break;

		case 9:
			lcd_2_clr;
			lcd_2_9;
			break;

		default:
			lcd_2_clr;
			lcd_2_0;
			break;
	}

}


void lcd_num_1(u8 num)
{
	switch(num)
	{
		case 1:
			lcd_1_clr;
			lcd_1_1;
			break;

		case 2:
			lcd_1_clr;
			lcd_1_2;
			break;

		default:
			lcd_1_clr;
			lcd_1_0;
			break;
	}

}


void lcd_selcet(u8 addr, u8 num)
{
	switch(addr)
	{
		case 1:
			lcd_num_1(num);
			break;

		case 2:
			lcd_num2_2(num);
			break;

		case 3:
			lcd_num_3(num);
			break;

		case 5:
			lcd_num_5(num);
			break;

		default:
			lcd_num(num);
			break;
	}


}


void lcd_selcet_off(u8 addr)
{
	switch(addr)
	{
		case 1:
			lcd_1_clr;
			break;

		case 2:
			lcd_2_clr;
			break;

		case 3:
			lcd_3_clr;
			break;

		case 5:
			lcd_5_clr;
			break;

		default:
			lcd_4_clr;
			break;
	}


}



char set_time(void)
{
	//	u8 ret ;
	u8 minute_h;

	col_staus = 0;
	col_on;
	eeprom_time[0] = rtc_date.hour / 10;
	eeprom_time[1] = rtc_date.hour % 10;
	eeprom_time[2] = rtc_date.minute / 10;
	eeprom_time[3] = rtc_date.minute % 10;

	/*lcd_timeout=0;	*/
	while(lcd_timeout <= 1500)
	{
		GCC_CLRWDT();			//喂狗*/

		//		ret = set_val_time(1,  0, 2);//设置时间
		set_val_time(1, 0, 2);	//设置时间

		if(eeprom_time[0] >= 2)
		{
			minute_h = 3;

		}
		else
		{
			minute_h = 9;
		}

		//		ret = set_val_time(2,  0, minute_h);
		//		ret = set_val_time(3,  0, 5);
		//		ret = set_val_time(4,  0, 9);
		set_val_time(2, 0, minute_h);
		set_val_time(3, 0, 5);
		set_val_time(4, 0, 9);

		rtc_date.hour = eeprom_time[0] *10 + eeprom_time[1];
		rtc_date.minute = eeprom_time[2] *10 + eeprom_time[3];


		col_staus = 1;
		break;

	}
	time_save();

	return 0;
}


//（原）
char set_val(uchar addr, char min, char max, char meal) //设置定时喂食任务
{
	u8 key_value_3 = 0;
	u8 blink_flag = 0;
	int val = e2prom_read(addr + 5 * meal);

	eeprom_feed[addr - 1] = val;

	/*lcd_timeout =0;*/
	while(lcd_timeout <= 1500)
	{

		GCC_CLRWDT();			//喂狗*/
		key_value_3 = key_scan();

		if(key_value_3)
		{
			BUZZER_inlt();

			switch(key_value_3)
			{
				case KEY_SET:
					Delay_ms(100);
					eeprom_feed[(addr - 1)] = val;
					lcd_selcet(addr, val);
					Delay_ms(100);
					goto back;
					break;

				case KEY_DOWN:
					Delay_ms(100);
					val--;
					blink_flag = 1;
					lcd_glint = 40;

					if(val < min)
					{
						val = max;
					}

					eeprom_feed[addr - 1] = val;
					break;

				case KEY_UP:
					{
						Delay_ms(100);
						val++;
						blink_flag = 1;
						lcd_glint = 40;

						if(val > max)
						{
							val = min;

						}

						eeprom_feed[addr - 1] = val;

					}
					break;
			}
		}


		if(addr == 1)
		{
			if((val >= 2) && (e2prom_read(2 + 5 * meal) > 3))
			{

				lcd_selcet(addr + 1, 0);
				eeprom_feed[addr] = 0;
				e2prom_write(2 + 5 * meal, eeprom_feed[1]);
			}

		}


		if(lcd_glint >= 40)
		{
			lcd_selcet(addr, val);

		}
		else
		{
			if(blink_flag == 0)
			{
				lcd_selcet_off(addr);
			}
		}
//		time_save();

		blink_flag = 0;
	}


back:
	return 0;
}


char set_val_time(char addr, char min, char max)
{


	u8 key_value = 0;
	u8 blink_flag = 0;




	int val_time = eeprom_time[addr - 1];

	/*lcd_timeout=0;*/
	while(lcd_timeout <= 1500)
	{ //8second

		GCC_CLRWDT();			//喂狗*/
		key_value = key_scan();

		if(key_value)
		{

			BUZZER_inlt();

			switch(key_value)
			{
				case KEY_SET:
					eeprom_time[addr - 1] = val_time;
					lcd_selcet(addr, val_time);
					goto back_time;
					Delay_ms(100);
					break;

				case KEY_DOWN:
					{
						Delay_ms(100);
						blink_flag = 1;
						lcd_glint = 40;
						val_time--;

						if(val_time < min) val_time = max;

						eeprom_time[addr - 1] = val_time;
					}
					break;

				case KEY_UP:
					{
						Delay_ms(100);
						blink_flag = 1;
						lcd_glint = 40;
						val_time++;

						if(val_time > max)
						{
							val_time = min;

						}

						eeprom_time[addr - 1] = val_time;
					}
					break;
			}
		}


		if(addr == 1)
		{
			if((eeprom_time[0] >= 2) && (eeprom_time[1] > 3))
			{

				eeprom_time[1] = 0;
				lcd_2_clr;
				lcd_2_0;

			}

		}



		if(lcd_glint >= 40)
		{
			lcd_selcet(addr, val_time);
		}
		else
		{
			/*if(blink_flag =1)	*/ //debug	 

			if(blink_flag == 0)
			{
				lcd_selcet_off(addr);
			}
		}
//		time_save();

		blink_flag = 0; 		//debug  
	}


back_time:
	rtc_date.second = 0;
	return 0;
}




char set_meal(u8 num)
{
	u8 i;						//（原）
	char ret;
	char minute_h;

	portion_on;
	meal_on;

	//lcd_5_0;
	lcd_num_5(e2prom_read(5 + 5 * num));
	lcd_timeout = 0;

	//	while (lcd_timeout <=1500)
	{
		GCC_CLRWDT();
		ret = set_val(1, 0, 2, num);

		if(eeprom_feed[0] >= 2)
		{
			minute_h = 3;


		}
		else
		{
			minute_h = 9;
		}

		set_val(2, 0, minute_h, num);

		set_val(3, 0, 5, num);

		set_val(4, 0, 9, num);

		set_val(5, 0, 9, num);

		e2prom_write(1 + 5 * num, eeprom_feed[0]);
		e2prom_write(2 + 5 * num, eeprom_feed[1]);
		e2prom_write(3 + 5 * num, eeprom_feed[2]);
		e2prom_write(4 + 5 * num, eeprom_feed[3]);
		e2prom_write(5 + 5 * num, eeprom_feed[4]);
		/*memset(eeprom_feed,0,sizeof(eeprom_feed));*/ //debug

		for(i = 0; i < 5; i++)
		{
			eeprom_feed[i] = 0;
		}


		/*	portion_off;
			meal_off;
			lcd_5_clr;*/
		//				break;
	}
	return ret;
}



void get_meal(u8 num)
{
	char hour_h = e2prom_read(1 + 5 * num);
	char hour_l = e2prom_read(2 + 5 * num);
	char minute_h = e2prom_read(3 + 5 * num);
	char minute_l = e2prom_read(4 + 5 * num);
	char count = e2prom_read(5 + 5 * num);

	key_up_flag = 0;
	col_staus = 0;
	col_on;
	lcd_selcet(1, hour_h);
	lcd_selcet(2, hour_l);
	lcd_selcet(3, minute_h);
	lcd_selcet(4, minute_l);
	lcd_selcet(5, count);
}



void menu_lcd()
{
	if(meal_flag >= 0)
	{
		switch(meal_flag)
		{
			case 1:
				lcd_num_off;
				meal_on;
				portion_on;
				lcd_1;
				break;

			case 2:
				lcd_num_off;
				portion_on;
				meal_on;
				lcd_2;
				break;

			case 3:
				lcd_num_off;
				portion_on;
				meal_on;
				lcd_3;
				break;

			case 4:
				lcd_num_off;
				portion_on;
				meal_on;
				lcd_4;
				break;

			default:
				lcd_num_off;
				break;
		}
	}


}


void sleep_mode()
{
	_lxtlp = 1; 				//debug 3.13
	key_lock = 1;
	meal_off;
	portion_off;
	lcd_5_clr;
	col_staus = 1;
	key_up_flag = 1;
	time_save_flag_1 = 1;

	//	BL_EN = 0; //lcd屏 			//（原）
	RECODE_LED = LED_OFF;		//红色指示灯灭
	/*	_t1cp	=0; //lcd屏除能*/ //DEBUG 3.13
	_t1on = 0;					//DEBUG 3.13
	_t1cp = 0;
	BL_EN = 0;					//lcd屏 

	meal_flag = 0;

	lock_clr;
	lock_off;
	lcd_num_off;

	//RECODE_LED = 1;//红色指示灯灭
	PWR_LED = LED_OFF;			//绿色	
	_adoff = 1; 				//关掉ad电源
	_halt();					//进入睡眠
	PWR_LED = LED_OFF;			//绿色 
	RECODE_LED = LED_OFF;		//红色指示灯灭
}


void frist_menu() //主菜单
{
	meal_off;
	portion_off;
	lcd_5_clr;
	col_staus = 1;
	key_up_flag = 1;
}


void kaiji_mode()
{

//	RECODE_LED = LED_OFF;		//红色指示灯灭
//	PWR_LED = 0;				//kai
	BL_EN = 1;					//lcd屏
	time_save();
	time_save_flag_1 = 0;

	lock_clr;
	lock_on;
	key_lock = 0;
	lcd_timeout = 0;
	_t1cp = 1;					//DEBUG 3.13
	_t1on = 1;					//DEBUG 3.13
	
//	_tm1al = 0xff;				//固定背光			TM1 CCRA 低字节寄存器
//	_tm1ah = 0x00;				//TM1 CCRA 高字节寄存器			255 	25%

	
	_tm1al = 0x00;				//固定背光			TM1 CCRA 低字节寄存器
	_tm1ah = 0x02;				//TM1 CCRA 高字节寄存器			512 	50%
	
//	_tm1al = 0x00;				//固定背光			TM1 CCRA 低字节寄存器
//	_tm1ah = 0x03;				//TM1 CCRA 高字节寄存器			768 	75%

//	_tm1al = 0b11111111;				//固定背光			TM1 CCRA 低字节寄存器
//	_tm1ah = 0b00000011;				//TM1 CCRA 高字节寄存器			1023	100%


}


void kaiji_init()
{
	/*	  res==0;	*/			  //
	res = 0;					//debug
	MOTOR_EN = 0;
	PWR_LED = 1;
	key_lock = 1;

	key_up_flag = 1;
	lcd_fill_sr();
	Delay_ms(1000);
	LCD_clrscreen();
	lcd_4_0;
	lcd_3_0;
	lcd_2_0;
	lcd_1_0;
	lock_clr;
	lock_off;
	_t2cp = 0;

	if(DC_DET)
	{
		power_clr;
		power_0;
		power_1;
		power_2;
		power_3;
		power_4;
		/*	SendString("V1=DC_DET\n");	*/ //debug 3.13				
	}
	else
	{
		voltage_lcd();
		/*	SendString("V2\n"); */ //debug 3.13	
	} //ADC
}


void GPIO_INIT()
{

	GPIOF_INIT(GPIO_Pin_6 | GPIO_Pin_7, GPIO_Mode_INT, RESET);

	GPIOE_INIT(GPIO_Pin_4 | GPIO_Pin_6, GPIO_Mode_OUT, SET);		//（我）

	/*GPIOC_INIT(GPIO_Pin_All,GPIO_Mode_INT,RESET);*/
	GPIOC_INIT(GPIO_Pin_6 | GPIO_Pin_5, GPIO_Mode_OUT, RESET);

	/* GPIOC_INIT( GPIO_Pin_7 ,GPIO_Mode_INT,RESET);*/
	GPIOB_INIT(GPIO_Pin_2 | GPIO_Pin_3, GPIO_Mode_OUT, RESET);

	GPIOB_INIT(GPIO_Pin_0 | GPIO_Pin_4, GPIO_Mode_INT, RESET);

	GPIOA_INIT(GPIO_Pin_7, GPIO_Mode_OUT, RESET);
	GPIOA_INIT(GPIO_Pin_0 | GPIO_Pin_2 | GPIO_Pin_6, GPIO_Mode_INT, RESET);

	PWR_LED = 1;
	LED_B = 0;
	LED_G = 0;
	LED_R = 0;

//	RECODE_LED = 0;//红色指示灯（我）
	_pc |= 0x80;				//引脚电平
	_pcc |= 0x80;				//0：输出
	_pcpu |= 0x00;				//1 上拉使能
	_pc |= 0x80;				//引脚
}











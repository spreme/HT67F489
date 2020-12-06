#include "HT67F489.h"
#include "init_ht67f489.h"
#include "Clock_Run.h"
#include "KeyScan.h"
#include "EEPROM.h"
#include "define.h"
#include "UART.h"
#include "LCD.h"
#include "Menu.h"
#include "sound_isd1820.h"
u8 ISD1820_REC_TIME =0;		//要播放录音的时间
u8 REC_TIME_flag =0;		//录音标志位（=1 开启中断，录音时长计时）
void sound_rec(void)
{   
	
	u8 key_value_4 =0 ;
   
	ISD1820_REC =1;			//录音
	lcd_timeout=0;

	while (lcd_timeout <=2000) 		//10second
	{
        
        GCC_CLRWDT(); //喂狗*/
		key_value_4 = key_scan();
		if (key_value_4) 
		{
			
	         sheep_flag =0;//睡眠模式标志位
  	         lcd_timeout =0;
			switch (key_value_4) 
			{
			    
				case KEY_REC:
														     
				 
					goto ISD1820_time;
				
					break ;
								
			}
		}
	}
ISD1820_time:	
	
	ISD1820_REC =0;
   
}


void sound_play(void)
{ 
	 ISD1820_PLAYE =1;
	 Delay_ms(1000);
	 ISD1820_PLAYE =0;
}


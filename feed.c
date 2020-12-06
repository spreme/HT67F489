
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
u8 feed_going = 0; //ִ��ιʳ��־λ			=1ִ��ιʳ������feed_run��

//ִ��ιʳ�������ֶ�  ��ʱ
u8 feed_run(struct feed_record * info)
{
	u8 weight = 0;
	u8 i = ISD1820_REC_TIME + 1;
	u8 ret = 0; 				//ת������

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

	//�������
	info->quantity = motor(weight, &ret);
	return ret; //ת������
}


//����Ƿ���ιʳ�ƻ�
inline void feed_scan(struct feed_record * feed)
{
	u8 i;

	for(i = 1; i < FEED_MAX_NUM + 1; i++)
	{
		//������С512����ÿ������ֻ��ʹ��ǰ120�ֽڱ���ιʳ��¼��������Ҫ�����ÿ����Ŀ������eeprom�ĵ�ַ
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



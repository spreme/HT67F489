//====================================================//
//				  ѡ��оƬ��HT67F489				  //
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
#include "voltage.h"		//��ԭ��
//===========================ʱ�ӳ�ʼ������=========================================//
//char watch =2+0x30;
char key_up_flag = 0; 				//ʱ����ʾ��־λ			1����ʾʵʱʱ��		0������ʾ
char col_staus = 1; 				//ʱ���������־
char meal_flag = 0; 				//ιʳ�ƻ��˵���־��0��û�н���				1~4:1��4��ιʳ�ƻ���
char key_lock = 1; 					//����������־λ			1������		0������
u8 sheep_flag = 0; 					//˯��ģʽ��־λ��û�ã�
u8 buzzer_time = 0;
u8 res = 0;
u8 vol_flag = 0; 					//����־λ
u8 buzzer_detect = 0; 				//�͵�ѹʱÿ���ӷ�������һ��
u8 time_save_flag = 0;				//һСʱ����һ��ʱ��
u8 time_save_flag_1 = 0;				//���߱�־λ,1:�������� 0����������
u8 error_time = 0;					//����������д���������������
u8 led_flag = 0;					//��״̬��־λ        0���̵Ƴ���	1���̵�����          2���̵��� 3����Ƴ��� 4��������� 5������� 6:ȫ��


void BUZZER_inlt(void)
{
	BUZZER = 1;
	Delay_ms(100);
	BUZZER = 0;
}


u8 time2_task = 0; 				//���ʱ��ڵ�������־λ


void main()
{


#if 0 //��ԭ��

	GCC_CLRWDT();
	init_Timerset();
	LCD_init();
	UART_init();

	AD_init();
	init_SyS();
#endif

	while(!_hto);

	GCC_CLRWDT();				//���Ź���0
	init_SyS(); 				//ϵͳ��ʼ��
	init_Timerset();			//��ʱ���жϹ���������
	LCD_init(); 				//lcd��Ļ��ʼ��

	/* UART_init();*/
	AD_init();


	init_Timer();
	init_Timer_isc0();
	init_Timer1();
	//init_Timer2();

	/*	init_Timer3();*/
	GPIO_INIT();

	kaiji_init();
	rtc_init(); 				//ʵʱʱ�ӳ�ʼ��
	e2prom_init();				//��д�洢����ʼ��
	rtc_date.hour = e2prom_read(31);
	rtc_date.minute = e2prom_read(32);
	/*SendString("V190303->801e-3.3V\n");  */ //debug 3.13
	struct feed_record feed;
	char key_value_1 = 0;
	u8 rst_flag_0 = 0;      
	PWR_LED = LED_OFF ;		//lcd��Ļ��������
	while(1)
	{
		if(res == 0)
		{
			GCC_CLRWDT();
		}

		if(key_up_flag)
		{
			rtc_lcd();			//��ʾʱ��
		}

		if(voltage_low)
		{

			if(buzzer_detect) 		//�͵�ѹʱÿ���ӷ�������һ��  1����
			{
				buzzer_detect = 0; 	//��λ0
				BUZZER_inlt();		//��������
			}

		}
		
		if(time_save_flag)				//
		{
			time_save_flag = 0;
			time_save();	
		}

		if(res == 0)
			key_value_1 = key_scan();		//�������

		//���������������
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

		//����������			 
		else if(key_lock == 0)
		{

			switch(key_value_1)
			{
				case KEY_SET_L: 					//��������			//����
					{
						key_up_flag = 0; 			//����ʾʵʱ��ʱ��
						BUZZER_inlt();

						if(meal_flag <5 && meal_flag > 0) //ιʳ�ƻ�5���˵�
						{
							meal_on; 					//�򿪲˵�
							set_meal(meal_flag); 		//���ò˵�
						}
						else
						{
							meal_off; //�رղ˵�
							set_time(); //����ʱ��

						}
					}
					break;

				case KEY_REC_L: 					//¼��
					RECODE_LED = LED_ON; 			//��ɫָʾ��
					PWR_LED = LED_OFF;
					led_flag = 3;					//��Ƴ���
					time2_task = 1; 				//�������ʱ��ڵ�����
					ISD1820_REC_TIME = 0; 			//¼��ʱ����0
					REC_TIME_flag = 1; 				//¼����־λ��=1 �����жϣ�¼��ʱ����ʱ��
					sound_rec();
					REC_TIME_flag = 0;
					time2_task = 0;
					RECODE_LED = LED_OFF; 			//��ɫָʾ��
					PWR_LED = LED_ON;
					led_flag = 0;
					/*	 UART_SendChar(ISD1820_REC_TIME);*/
					break;

				case KEY_SET: 						//�����󣬲�������ģʽ�£��̰����ü��޹���	
					GCC_NOP(); 						//��ԭ��
					break;

				case KEY_ESC: 						//�ֶ�ιʳ
					time2_task = 1;
					BUZZER_inlt(); 					//����������˸
					feed.quantity = 1; 				//ιʳ������1
					feed.music = 3; 				// =3������¼��
					feed_going = 1; 				//ִ��ιʳ��־λ��ִ��
					break;

				case KEY_REC:	 					//����
					BUZZER_inlt(); 					//������
//					RECODE_LED = LED_ON; 			//��ɫָʾ��	
//					Delay_ms(500);
//					RECODE_LED = LED_OFF; 			//��ɫָʾ��
					PWR_LED = LED_ON;
					RECODE_LED = LED_OFF;
					led_flag = 0;
					sound_play(); 					//����¼��
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
				frist_menu();	//���˵�
			}

			menu_lcd(); 		//�˵���ʾ

		}

		if(lcd_timeout > sheep_time && time_save_flag_1 == 0) 		//40������
		{
			time_save();					//����ʱ��
//			task_run_led = 0;
//			led_flag = 0;
			feed_error = 0;
			sleep_mode();					//˯��
		}

#if 0

		//	 if(sheep_flag ==1)//˯��		//debug 3.13
		//		{
		//			  _halt();
		//		}				
#endif

		if(lcd_timeout == meal_time) 			//30��	�������˳������˵�ҳ��
		{
			meal_flag = 0;
//			time_save();
		}

		//ÿ����ɨ��һ��eeprom���ж�ʹ���ж�ʱιʳ��Ҫ����
		if(feed_detect)
		{
			// _adoff=0;//��ad��Դ
			feed_detect = 0;

			feed_scan(&feed);					//����Ƿ���ιʳ�ƻ�

			if(key_lock == 0)					//˯�߱�־λ��1��������
			{
				time_save();
			}

			if(feed_going == 0) 				//û�е�ιʳ�ƻ�
			{
				if(DC_DET == 0) voltage_lcd();	 //ADC
			}

			// _adoff=1;//��ad��Դ
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
			if(rtc_date.second % 2 == 0) 		//ʱ�������
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


/********************��ʱ��0*********************************/
void __attribute((interrupt(0x0c))) Interrupt_tm0()
{
	
	_t0af = 0;					//TM0 �Ƚ���A ƥ���ж������־λ,0��������
	_t0ae = 1;					//TM0 �Ƚ���A ƥ���жϿ���λ,1��ʹ��


	lcd_glint++;

	if(lcd_glint >= 80)
	{
		lcd_glint = 0;
	}

	lcd_timeout++;

	if(lcd_timeout >= 8100) 		//40s
	{
		lcd_timeout = 0;			//lcd˯�߼�ʱ
	}

	if(key_lock == 0)									//����״̬��
	{
		if(task_run_led && led_flag == 4)				//���������¼����������
		{
			task_delay_led--;							//��˸ʱ��

			if(task_delay_led == 0)						//��˸һ��ʱ�䵽��
			{
				pwr_task();								//��˸����

				task_delay_led = task_delay_error;		//���¸�ֵ��˸ʱ��
			}
		}
		
		else if(led_flag == 3)		//��Ƴ���
		{
			RECODE_LED = LED_ON;				//��ƿ���
			PWR_LED = LED_OFF;					//�̵ƹر�
//			error_time = 0;						//�����һ�δ����־
		}	
		
		else if(led_flag == 0)		//�̵Ƴ���
		{
			RECODE_LED = LED_OFF;				//��ƹر�
			PWR_LED = LED_ON;					//�̵ƿ���
//			error_time = 0; 					//�����һ�δ����־
		}	
		
		else if(led_flag == 6)		//ȫ��
		{
			RECODE_LED = LED_OFF;				//��ƹر�
			PWR_LED = LED_OFF;					//�̵ƿ���
//			error_time = 0; 					//�����һ�δ����־
		}	
		
//		if(MOTOR_EN == 1)
//			PWR_LED = LED_ON;
	}

	if(time2_task)
	{
		if(rtc_date.second % 2 == 0) 		//ʱ�������
		{
			col_on;
		}
		else
		{
			col_off;
		}
	}

}




/********************��ʱ��2*********************************/
//void __attribute((interrupt(0x14))) Interrupt_tm2()
//{

//	_t2af = 0;					//TM2 �Ƚ���A ƥ���ж������־λ,0��������
//	_t2ae = 1;					//TM2 �Ƚ���A ƥ���жϿ���λ,1��ʹ��

//	if(BUZZER_FLAG)
//	{
//		BUZZER = ~BUZZER;
//	}
//}


///********************��ʱ��3*********************************/
//void __attribute((interrupt(0x18))) Interrupt_tm3()//200ns
//{
//
//	_t3af=0;			 //TM3 �Ƚ���A ƥ���ж������־λ,0��������
//	_t3ae=1;			 //TM3 �Ƚ���A ƥ���жϿ���λ,1��ʹ��
//	if(time2_task)
//	{
//			if(rtc_date.second %2 ==0)	 //ʱ�������
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

	_tb0f = 0;						//���жϿ�

	rtc_date.second++;
	
	if(rtc_date.second > 59)
	{
		buzzer_detect = 1;				//�͵�ѹʱÿ���ӷ�������һ�£�һ���Ӽ��һ��	
		rtc_date.minute++;
		rtc_date.second = 0;
		feed_detect = 1;			//��ʱιʳʱ���⣬ÿ���Ӽ��һ��

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

//UART�ж�				//��ԭ��
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



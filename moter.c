
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
	int timeout = 600;			//�����жϵ����ʱ
	int i = 0;
	int key_cont = 0;

	lcd_timeout = 0;

	//�������
	MOTOR_EN = 1;



	//���õ��ת��һ���Ƕȣ��˳���λ����ѹ�ŵ�״̬����->��
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

//			break;	���ң�	
		}

		if(i < 20) //��ʱ����
		{
			timeout = 0;
			break;
		}

		i--;

	}

#else

	Delay_ms(1000);
#endif

	//�ȴ�����ж�(�½��ش���)�������жϵ������ж��ж����ŵ�ƽ�Ƿ�Ϊ��(������ʱȥ��)
	//�ͱ�ʾ��λ���ػ����������ת����ѹ�ţ���ʱ���ֹͣת��
	lcd_timeout = 0;

	while(timeout)
	{
		GCC_CLRWDT();

		if(MOTOR_DET == 0)
		{

			key_cont = 0;
			i = 20;
			Delay_ms(10);		//��ʱȥ��

			while(i)
			{
				Delay_ms(10);	//��ʱȥ��

				if(MOTOR_DET == 0)
				{
					key_cont++;
				}

				i--;
			}

			if(key_cont > 6)
			{
				//					delay_ms(10);	//�ó�ʳ��������׼ȷ��λ
				break;
			}

		}
		Delay_ms(10);			//���ң�
		timeout--;

	}

	return timeout;
}


u8 motor(u8 count, u8 * err_type)
{

	int feed_cont = count;		//�����жϵ��ת��������ÿת��һ�Σ�ιʳһ�ݣ����10g��
	int timeout = MOTO_TIMEOUT; //�����жϵ����ʱ

	/*	u8 errs_flag = 0;
	  u8 errs = 0;*/
	task_run_led = 0;
	led_flag = 0;

	task_run_motor = 1;

	food_out = 0;

	*err_type = 0;				//��մ�����


	while(feed_cont > 0)
	{
		GCC_CLRWDT();			//ι��
		lcd_timeout = 0;

		timeout = motor_run();

		//�����ʱ�����ûת��λ����̽�����(��λ����û�ж�)
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


